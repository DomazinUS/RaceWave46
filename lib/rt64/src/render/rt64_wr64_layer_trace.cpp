// Wave Race 64 diagnostic render-layer trace and opt-in live Composer. The
// Composer returns local renderer overrides and never mutates workload data.

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_wr64_layer_trace.h"

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gbi/rt64_f3d.h"
#include "hle/rt64_workload.h"

namespace RT64::WR64LayerTrace {
    namespace {
        std::atomic_uint64_t lastNonzeroWorkloadFrame{0};
        std::atomic_uint64_t lastMatchedWorkloadFrame{0};

        constexpr uint64_t FNVOffset = 14695981039346656037ULL;
        constexpr uint64_t FNVPrime = 1099511628211ULL;

        template <typename T>
        uint64_t hashValue(uint64_t hash, const T &value) {
            const uint8_t *bytes = reinterpret_cast<const uint8_t *>(&value);
            for (size_t i = 0; i < sizeof(value); i++) {
                hash = (hash ^ bytes[i]) * FNVPrime;
            }
            return hash;
        }

        std::string hex64(uint64_t value) {
            std::ostringstream stream;
            stream << std::uppercase << std::hex << std::setw(16) << std::setfill('0') << value;
            return stream.str();
        }

        std::string rectString(const FixedRect &rect) {
            std::ostringstream stream;
            stream << rect.ulx << ':' << rect.uly << ':' << rect.lrx << ':' << rect.lry;
            return stream.str();
        }

        std::string trim(const std::string &value) {
            size_t first = 0;
            while ((first < value.size()) && std::isspace(static_cast<unsigned char>(value[first]))) first++;
            size_t last = value.size();
            while ((last > first) && std::isspace(static_cast<unsigned char>(value[last - 1]))) last--;
            return value.substr(first, last - first);
        }

        bool parseBool(const std::string &value) {
            const std::string normalized = trim(value);
            return (normalized == "1") || (normalized == "true") || (normalized == "yes") ||
                (normalized == "on");
        }

        uint64_t parseHex64(const std::string &value) {
            std::string normalized = trim(value);
            if ((normalized.size() >= 2) && (normalized[0] == '0') &&
                ((normalized[1] == 'x') || (normalized[1] == 'X'))) {
                normalized.erase(0, 2);
            }
            if (normalized.empty()) return 0;
            try {
                return std::stoull(normalized, nullptr, 16);
            }
            catch (...) {
                return 0;
            }
        }

        uint32_t parseHex32(const std::string &value) {
            return static_cast<uint32_t>(parseHex64(value));
        }

        int32_t toFixedQuarterPixel(float pixels) {
            return static_cast<int32_t>(std::lround(pixels * 4.0f));
        }

        bool parseFloatList(const std::string &value, float *output, size_t count) {
            std::istringstream stream(value);
            std::string item;
            for (size_t i = 0; i < count; i++) {
                if (!std::getline(stream, item, ',')) return false;
                try {
                    output[i] = std::stof(trim(item));
                }
                catch (...) {
                    return false;
                }
            }
            return !std::getline(stream, item, ',');
        }

        const char *projectionTypeName(Projection::Type type) {
            switch (type) {
            case Projection::Type::None: return "none";
            case Projection::Type::Perspective: return "perspective";
            case Projection::Type::Orthographic: return "orthographic";
            case Projection::Type::Rectangle: return "rectangle";
            case Projection::Type::Triangle: return "triangle";
            default: return "unknown";
            }
        }

        bool rectCovers(const FixedRect &candidate, const FixedRect &reference) {
            if (candidate.isNull() || reference.isNull()) {
                return false;
            }
            constexpr int32_t tolerance = 8;
            return (candidate.ulx <= (reference.ulx + tolerance)) &&
                (candidate.uly <= (reference.uly + tolerance)) &&
                (candidate.lrx >= (reference.lrx - tolerance)) &&
                (candidate.lry >= (reference.lry - tolerance));
        }

        uint32_t countBucket(uint32_t count) {
            if (count == 0) return 0;
            if (count == 1) return 1;
            if (count <= 4) return 2;
            if (count <= 16) return 3;
            if (count <= 64) return 4;
            return 5;
        }

        template <typename T>
        void sortUnique(std::vector<T> &values) {
            std::sort(values.begin(), values.end());
            values.erase(std::unique(values.begin(), values.end()), values.end());
        }

        std::string joinHex(const std::vector<uint64_t> &values, size_t limit = SIZE_MAX) {
            std::ostringstream stream;
            const size_t count = std::min(values.size(), limit);
            for (size_t i = 0; i < count; i++) {
                if (i > 0) stream << ';';
                stream << hex64(values[i]);
            }
            if (count < values.size()) stream << ";...+" << (values.size() - count);
            return stream.str();
        }

        struct PassEvidence {
            uint64_t signature = 0;
            const char *role = "unknown";
            uint32_t calls = 0;
            uint32_t triangles = 0;
            uint32_t textured = 0;
            uint32_t fill = 0;
            uint32_t copy = 0;
            uint32_t depth = 0;
            uint32_t fullCoverage = 0;
            std::vector<uint64_t> textures;
            std::vector<uint64_t> combiners;
            std::vector<uint64_t> otherModes;
            std::string callRects;
        };

        PassEvidence classifyPass(const Workload &workload, const FramebufferPair &fbPair,
            const Projection &projection)
        {
            PassEvidence result;
            result.calls = projection.gameCallCount;
            std::ostringstream callRects;

            for (uint32_t callIndex = 0; callIndex < projection.gameCallCount; callIndex++) {
                const DrawCall &call = projection.gameCalls[callIndex].callDesc;
                result.triangles += call.triangleCount;
                result.textured += (call.textureOn != 0) ? 1U : 0U;
                result.fill += (call.otherMode.cycleType() == G_CYC_FILL) ? 1U : 0U;
                result.copy += (call.otherMode.cycleType() == G_CYC_COPY) ? 1U : 0U;
                result.depth += (call.otherMode.zCmp() || call.otherMode.zUpd()) ? 1U : 0U;
                result.fullCoverage += rectCovers(call.rect, fbPair.scissorRect) ? 1U : 0U;
                result.combiners.push_back((uint64_t(call.colorCombiner.L) << 32) | call.colorCombiner.H);
                result.otherModes.push_back((uint64_t(call.otherMode.L) << 32) | call.otherMode.H);
                if (callIndex > 0) callRects << ';';
                callRects << rectString(call.rect);

                const uint32_t tileEnd = std::min<uint32_t>(call.tileIndex + call.tileCount,
                    uint32_t(workload.drawData.callTiles.size()));
                for (uint32_t tileIndex = call.tileIndex; tileIndex < tileEnd; tileIndex++) {
                    result.textures.push_back(workload.drawData.callTiles[tileIndex].tmemHashOrID);
                }
            }

            sortUnique(result.textures);
            sortUnique(result.combiners);
            sortUnique(result.otherModes);
            result.callRects = callRects.str();

            switch (projection.type) {
            case Projection::Type::Perspective: result.role = "perspective-3d"; break;
            case Projection::Type::Orthographic: result.role = "orthographic-overlay"; break;
            case Projection::Type::Rectangle:
                if ((result.calls > 0) && (result.fullCoverage == result.calls)) {
                    result.role = (result.textured > 0) ? "full-coverage-background" : "full-coverage-effect";
                }
                else {
                    result.role = "rectangle-ui";
                }
                break;
            case Projection::Type::Triangle: result.role = "raw-triangle"; break;
            default: result.role = "unknown"; break;
            }

            uint64_t signature = FNVOffset;
            const uint32_t type = uint32_t(projection.type);
            signature = hashValue(signature, type);
            signature = hashValue(signature, countBucket(result.calls));
            signature = hashValue(signature, countBucket(result.triangles));
            signature = hashValue(signature, countBucket(uint32_t(result.textures.size())));
            signature = hashValue(signature, result.textured > 0);
            signature = hashValue(signature, result.fill > 0);
            signature = hashValue(signature, result.copy > 0);
            signature = hashValue(signature, result.depth > 0);
            signature = hashValue(signature, (result.calls > 0) && (result.fullCoverage == result.calls));

            // Texture/state identity is valuable for 2D layers. Perspective texture
            // animation is deliberately excluded to keep 3D scene identity stable.
            if (projection.type != Projection::Type::Perspective) {
                for (uint64_t texture : result.textures) signature = hashValue(signature, texture);
                for (uint64_t combiner : result.combiners) signature = hashValue(signature, combiner);
                for (uint64_t otherMode : result.otherModes) signature = hashValue(signature, otherMode);
            }
            result.signature = signature;
            return result;
        }

        struct PairObservation {
            uint32_t pair = 0;
            uint64_t signature = 0;
            std::string sourceDimensions;
            std::string targetDimensions;
            std::string passIds;
        };

        class TraceState {
        public:
            bool initialized = false;
            bool enabled = false;
            std::ofstream passes;
            std::ofstream layouts;
            std::ofstream copies;
            std::unordered_map<uint64_t, uint32_t> passIds;
            uint32_t nextPassId = 1;
            uint64_t pendingFrame = 0;
            bool hasPendingFrame = false;
            uint64_t previousFrameSignature = 0;
            bool hasPreviousFrameSignature = false;
            uint64_t transitionSequence = 0;
            std::vector<PairObservation> pendingPairs;

            void initialize() {
                if (initialized) return;
                initialized = true;
                const char *setting = std::getenv("WR64_LAYER_TRACE");
                enabled = (setting != nullptr) && (setting[0] != '\0') && (setting[0] != '0');
                if (!enabled) return;

                const std::string prefix = (std::string(setting) == "1") ? "wr64-layer-trace" : setting;
                passes.open(prefix + "-passes.csv", std::ios::out | std::ios::trunc);
                layouts.open(prefix + "-layouts.csv", std::ios::out | std::ios::trunc);
                copies.open(prefix + "-copies.csv", std::ios::out | std::ios::trunc);
                if (!passes.is_open() || !layouts.is_open() || !copies.is_open()) {
                    std::cerr << "[rt64] unable to open WR64 layer trace output\n";
                    enabled = false;
                    return;
                }

                passes << "pass_id,signature,role,projection_type,calls,triangles,textured,fill,copy,depth,"
                    "full_coverage,projection_scissor,call_rects,texture_hashes,combiner_modes,other_modes\n";
                layouts << "transition_sequence,submission_frame,frame_signature,pair_count,"
                    "source_dimensions,target_dimensions,pair_layouts,ordered_pass_ids\n";
                copies << "submission_frame,pair,event,phase,projection,call,tile,copy_id,address,"
                    "source_dimensions,target_dimensions,projection_type,call_rect,scissor,"
                    "copy_dimensions,copy_region,copy_format\n";
                std::cout << "[rt64] WR64 layer trace enabled: " << prefix
                    << "-passes.csv, " << prefix << "-layouts.csv, and " << prefix
                    << "-copies.csv (diagnostic only)\n";
            }

            uint32_t recordPass(const Projection &projection, const PassEvidence &evidence) {
                auto existing = passIds.find(evidence.signature);
                if (existing != passIds.end()) return existing->second;

                const uint32_t passId = nextPassId++;
                passIds.emplace(evidence.signature, passId);
                passes << passId << ',' << hex64(evidence.signature) << ',' << evidence.role << ','
                    << projectionTypeName(projection.type) << ',' << evidence.calls << ','
                    << evidence.triangles << ',' << evidence.textured << ',' << evidence.fill << ','
                    << evidence.copy << ',' << evidence.depth << ',' << evidence.fullCoverage << ','
                    << rectString(projection.scissorRect) << ",\"" << evidence.callRects << "\",\""
                    << joinHex(evidence.textures, 48) << "\",\"" << joinHex(evidence.combiners)
                    << "\",\"" << joinHex(evidence.otherModes) << "\"\n";
                passes.flush();
                return passId;
            }

            void recordCopyProducer(uint64_t frame, uint32_t pair, const char *phase,
                const FramebufferOperation &operation, uint32_t framebufferWidth,
                uint32_t framebufferHeight, uint32_t targetWidth, uint32_t targetHeight)
            {
                if (operation.type != FramebufferOperation::Type::CreateTileCopy) return;
                const FramebufferTile &tile = operation.createTileCopy.fbTile;
                copies << frame << ',' << pair << ",producer," << phase << ",-1,-1,-1,"
                    << operation.createTileCopy.id << ',' << operation.createTileCopy.address << ','
                    << framebufferWidth << 'x' << framebufferHeight << ',' << targetWidth << 'x'
                    << targetHeight << ",none,,," << (tile.right - tile.left) << 'x'
                    << (tile.bottom - tile.top) << ',' << tile.left << ':' << tile.top << ':'
                    << tile.right << ':' << tile.bottom << ',' << uint32_t(tile.fmt) << ':'
                    << uint32_t(tile.siz) << '\n';
            }

            void recordCopyConsumer(uint64_t frame, uint32_t pair, uint32_t projectionIndex,
                uint32_t callIndex, uint32_t tileIndex, const Projection &projection,
                const DrawCall &call, const DrawCallTile &tile, uint32_t framebufferWidth,
                uint32_t framebufferHeight, uint32_t targetWidth, uint32_t targetHeight)
            {
                if (!tile.tileCopyUsed) return;
                copies << frame << ',' << pair << ",consumer,draw," << projectionIndex << ','
                    << callIndex << ',' << tileIndex << ',' << tile.tmemHashOrID << ",0,"
                    << framebufferWidth << 'x' << framebufferHeight << ',' << targetWidth << 'x'
                    << targetHeight << ',' << projectionTypeName(projection.type) << ','
                    << rectString(call.rect) << ',' << rectString(projection.scissorRect) << ','
                    << tile.tileCopyWidth << 'x' << tile.tileCopyHeight << ",,\n";
            }

            void finishPendingFrame() {
                if (!hasPendingFrame || pendingPairs.empty()) return;
                uint64_t frameSignature = FNVOffset;
                std::ostringstream sourceDimensions, targetDimensions, pairLayouts, passIds;
                for (size_t i = 0; i < pendingPairs.size(); i++) {
                    const PairObservation &pair = pendingPairs[i];
                    frameSignature = hashValue(frameSignature, pair.signature);
                    if (i > 0) {
                        sourceDimensions << ';'; targetDimensions << ';'; pairLayouts << ';'; passIds << '|';
                    }
                    sourceDimensions << pair.sourceDimensions;
                    targetDimensions << pair.targetDimensions;
                    pairLayouts << pair.pair << ':' << hex64(pair.signature);
                    passIds << pair.passIds;
                }
                if (!hasPreviousFrameSignature || (frameSignature != previousFrameSignature)) {
                    layouts << transitionSequence++ << ',' << pendingFrame << ',' << hex64(frameSignature)
                        << ',' << pendingPairs.size() << ",\"" << sourceDimensions.str() << "\",\""
                        << targetDimensions.str() << "\",\"" << pairLayouts.str() << "\",\""
                        << passIds.str() << "\"\n";
                    layouts.flush();
                }
                previousFrameSignature = frameSignature;
                hasPreviousFrameSignature = true;
                pendingPairs.clear();
            }
        };

        TraceState &traceState() {
            static TraceState state;
            return state;
        }

        struct ComposerConfig {
            uint64_t captureId = 0;
            uint64_t selectedSignature = 0;
            std::unordered_set<uint64_t> selectedSignatures;
            uint32_t highlightColor = 0;
            bool suppress = false;
            int32_t rectTranslateX = 0;
            int32_t rectTranslateY = 0;
            int32_t rectLeft = 0;
            int32_t rectTop = 0;
            int32_t rectRight = 0;
            int32_t rectBottom = 0;
            int32_t scissorTranslateX = 0;
            int32_t scissorTranslateY = 0;
            int32_t scissorLeft = 0;
            int32_t scissorTop = 0;
            int32_t scissorRight = 0;
            int32_t scissorBottom = 0;
            int32_t viewportLeft = 0;
            int32_t viewportTop = 0;
            int32_t viewportRight = 0;
            int32_t viewportBottom = 0;
        };

        uint64_t composerCallSignature(const Workload &workload, uint32_t framebufferPairIndex,
            uint32_t projectionIndex, uint32_t callIndex, const Projection &projection,
            const GameCall &call)
        {
            const DrawCall &draw = call.callDesc;
            uint64_t signature = FNVOffset;
            const uint32_t projectionType = uint32_t(projection.type);
            const int32_t rectWidth = draw.rect.width(true, true);
            const int32_t rectHeight = draw.rect.height(true, true);
            signature = hashValue(signature, framebufferPairIndex);
            signature = hashValue(signature, projectionIndex);
            signature = hashValue(signature, callIndex);
            signature = hashValue(signature, projectionType);
            signature = hashValue(signature, draw.triangleCount);
            signature = hashValue(signature, rectWidth);
            signature = hashValue(signature, rectHeight);
            signature = hashValue(signature, draw.tileCount);
            signature = hashValue(signature, draw.textureOn);
            signature = hashValue(signature, draw.colorCombiner.H);
            signature = hashValue(signature, draw.colorCombiner.L);
            signature = hashValue(signature, draw.otherMode.H);
            signature = hashValue(signature, draw.otherMode.L);
            const uint32_t tileEnd = std::min<uint32_t>(draw.tileIndex + draw.tileCount,
                uint32_t(workload.drawData.callTiles.size()));
            for (uint32_t tileIndex = draw.tileIndex; tileIndex < tileEnd; tileIndex++) {
                const DrawCallTile &tile = workload.drawData.callTiles[tileIndex];
                signature = hashValue(signature, tile.tmemHashOrID);
                signature = hashValue(signature, tile.sampleWidth);
                signature = hashValue(signature, tile.sampleHeight);
            }
            return signature;
        }

        class ComposerState {
        public:
            bool initialized = false;
            bool enabled = false;
            std::string configPath;
            std::ofstream candidates;
            std::ofstream events;
            std::ofstream startupCandidates;
            std::unordered_set<uint64_t> observedSignatures;
            std::unordered_set<uint64_t> observedStartupCalls;
            std::unordered_set<uint64_t> rollingSignatures;
            std::vector<std::string> rollingRows;
            uint64_t rollingFrame = UINT64_MAX;
            uint64_t captureFrame = UINT64_MAX;
            uint64_t activeCaptureId = 0;
            uint64_t startupFrameLimit = 0;
            uint64_t lastReloadFrame = UINT64_MAX;
            uint64_t configHash = 0;
            bool hasConfigHash = false;
            ComposerConfig config;

            void initialize() {
                if (initialized) return;
                initialized = true;
                const char *setting = std::getenv("WR64_COMPOSER");
                enabled = (setting != nullptr) && (setting[0] != '\0') && (setting[0] != '0');
                if (!enabled) return;

                configPath = (std::string(setting) == "1") ? "wr64-composer.cfg" : setting;
                const size_t separator = configPath.find_last_of("/\\");
                const std::string directory = (separator == std::string::npos) ? std::string() :
                    configPath.substr(0, separator + 1);
                if (const char *startupSetting = std::getenv("WR64_COMPOSER_STARTUP_TRACE")) {
                    try {
                        startupFrameLimit = std::stoull(startupSetting, nullptr, 10);
                    }
                    catch (...) {
                        startupFrameLimit = 0;
                    }
                }
                candidates.open(directory + "wr64-composer-candidates.csv", std::ios::out | std::ios::trunc);
                events.open(directory + "wr64-composer-events.log", std::ios::out | std::ios::trunc);
                if (!candidates.is_open() || !events.is_open()) {
                    std::cerr << "[rt64] WR64 Composer could not open diagnostic output beside "
                        << configPath << '\n';
                    enabled = false;
                    return;
                }

                candidates << "capture_id,signature,frame,pair,projection,call,uid,projection_type,"
                    "source_dimensions,target_dimensions,rect,scissor,triangles,texture_on,"
                    "texture_hashes,combiner,other_mode,prim_color,task_sequence,task_address,"
                    "task_context_ra,root_display_list,ucode,ucode_data\n";
                candidates.flush();
                if (startupFrameLimit != 0) {
                    startupCandidates.open(directory + "wr64-composer-startup.csv", std::ios::out | std::ios::trunc);
                    if (startupCandidates.is_open()) {
                        startupCandidates << "signature,frame,pair,projection,call,uid,projection_type,"
                            "source_dimensions,target_dimensions,rect,scissor,triangles,texture_on,"
                            "texture_hashes,combiner,other_mode,prim_color,task_sequence,task_address,"
                            "task_context_ra,root_display_list,ucode,ucode_data\n";
                        startupCandidates.flush();
                    }
                }
                events << "WR64 Composer started; config=" << configPath << '\n';
                events.flush();
                std::cout << "[rt64] WR64 Composer enabled: " << configPath << std::endl;
            }

            void reload(uint64_t frame) {
                initialize();
                if (!enabled || (lastReloadFrame == frame)) return;
                lastReloadFrame = frame;

                std::ifstream input(configPath, std::ios::in | std::ios::binary);
                if (!input.is_open()) return;
                const std::string contents((std::istreambuf_iterator<char>(input)),
                    std::istreambuf_iterator<char>());
                uint64_t newHash = FNVOffset;
                for (char byte : contents) newHash = (newHash ^ uint8_t(byte)) * FNVPrime;
                if (hasConfigHash && (newHash == configHash)) return;

                ComposerConfig next;
                std::istringstream lines(contents);
                std::string line;
                while (std::getline(lines, line)) {
                    const size_t comment = line.find('#');
                    if (comment != std::string::npos) line.erase(comment);
                    const size_t equals = line.find('=');
                    if (equals == std::string::npos) continue;
                    const std::string key = trim(line.substr(0, equals));
                    const std::string value = trim(line.substr(equals + 1));
                    if (key == "capture_id") {
                        try {
                            next.captureId = std::stoull(value, nullptr, 10);
                        }
                        catch (...) {
                            next.captureId = 0;
                        }
                    }
                    else if (key == "selected_signature") next.selectedSignature = parseHex64(value);
                    else if (key == "selected_signatures") {
                        std::istringstream signatures(value);
                        std::string signature;
                        while (std::getline(signatures, signature, ',')) {
                            const uint64_t parsed = parseHex64(trim(signature));
                            if (parsed != 0) next.selectedSignatures.emplace(parsed);
                        }
                    }
                    else if (key == "tint_rgba") next.highlightColor = parseHex32(value);
                    else if (key == "suppress") next.suppress = parseBool(value);
                    else if (key == "rect_translate") {
                        float values[2];
                        if (parseFloatList(value, values, 2)) {
                            next.rectTranslateX = toFixedQuarterPixel(values[0]);
                            next.rectTranslateY = toFixedQuarterPixel(values[1]);
                        }
                    }
                    else if (key == "rect_edges") {
                        float values[4];
                        if (parseFloatList(value, values, 4)) {
                            next.rectLeft = toFixedQuarterPixel(values[0]);
                            next.rectTop = toFixedQuarterPixel(values[1]);
                            next.rectRight = toFixedQuarterPixel(values[2]);
                            next.rectBottom = toFixedQuarterPixel(values[3]);
                        }
                    }
                    else if (key == "scissor_translate") {
                        float values[2];
                        if (parseFloatList(value, values, 2)) {
                            next.scissorTranslateX = toFixedQuarterPixel(values[0]);
                            next.scissorTranslateY = toFixedQuarterPixel(values[1]);
                        }
                    }
                    else if (key == "scissor_edges") {
                        float values[4];
                        if (parseFloatList(value, values, 4)) {
                            next.scissorLeft = toFixedQuarterPixel(values[0]);
                            next.scissorTop = toFixedQuarterPixel(values[1]);
                            next.scissorRight = toFixedQuarterPixel(values[2]);
                            next.scissorBottom = toFixedQuarterPixel(values[3]);
                        }
                    }
                    else if (key == "viewport_edges") {
                        float values[4];
                        if (parseFloatList(value, values, 4)) {
                            next.viewportLeft = toFixedQuarterPixel(values[0]);
                            next.viewportTop = toFixedQuarterPixel(values[1]);
                            next.viewportRight = toFixedQuarterPixel(values[2]);
                            next.viewportBottom = toFixedQuarterPixel(values[3]);
                        }
                    }
                }

                // A persisted capture ID is not a new capture request when the
                // process first reads the profile. Only a live ID transition
                // may export the last completely observed frame.
                const bool beginCapture = hasConfigHash && (next.captureId != 0) &&
                    (next.captureId != config.captureId);
                config = next;
                if (beginCapture) {
                    activeCaptureId = next.captureId;
                    observedSignatures.clear();
                    captureFrame = UINT64_MAX;
                    for (const std::string &row : rollingRows) {
                        candidates << activeCaptureId << ',' << row;
                    }
                    candidates.flush();
                }
                configHash = newHash;
                hasConfigHash = true;
                events << "frame=" << frame << " reload capture_id=" << config.captureId
                    << " capture_frame=" << (beginCapture ? std::to_string(rollingFrame) : "none")
                    << " capture_rows=" << (beginCapture ? rollingRows.size() : 0)
                    << " selected=" << hex64(config.selectedSignature)
                    << " tint=" << hex64(config.highlightColor) << " suppress=" << config.suppress
                    << " rect_translate=" << config.rectTranslateX << ':' << config.rectTranslateY
                    << " rect_edges=" << config.rectLeft << ':' << config.rectTop << ':'
                    << config.rectRight << ':' << config.rectBottom
                    << " scissor_translate=" << config.scissorTranslateX << ':' << config.scissorTranslateY
                    << " scissor_edges=" << config.scissorLeft << ':' << config.scissorTop << ':'
                    << config.scissorRight << ':' << config.scissorBottom
                    << " viewport_edges=" << config.viewportLeft << ':' << config.viewportTop << ':'
                    << config.viewportRight << ':' << config.viewportBottom << '\n';
                events.flush();
                std::cout << "[rt64] WR64 Composer reloaded: selected="
                    << hex64(config.selectedSignature) << std::endl;
            }

            void observeCall(uint64_t signature, const Workload &workload,
                uint32_t framebufferPairIndex, uint32_t projectionIndex, uint32_t callIndex,
                const Projection &projection, const GameCall &call,
                uint32_t framebufferWidth, uint32_t framebufferHeight,
                uint32_t targetWidth, uint32_t targetHeight)
            {
                if (!enabled) return;
                const DrawCall &draw = call.callDesc;
                std::vector<uint64_t> textures;
                const uint32_t tileEnd = std::min<uint32_t>(draw.tileIndex + draw.tileCount,
                    uint32_t(workload.drawData.callTiles.size()));
                for (uint32_t tileIndex = draw.tileIndex; tileIndex < tileEnd; tileIndex++) {
                    textures.push_back(workload.drawData.callTiles[tileIndex].tmemHashOrID);
                }
                const uint64_t combiner = (uint64_t(draw.colorCombiner.L) << 32) | draw.colorCombiner.H;
                const uint64_t otherMode = (uint64_t(draw.otherMode.L) << 32) | draw.otherMode.H;
                std::ostringstream row;
                row << hex64(signature) << ',' << workload.submissionFrame << ','
                    << framebufferPairIndex << ',' << projectionIndex << ',' << callIndex << ','
                    << draw.uid << ',' << projectionTypeName(projection.type) << ','
                    << framebufferWidth << 'x' << framebufferHeight << ',' << targetWidth << 'x'
                    << targetHeight << ',' << rectString(draw.rect) << ',' << rectString(draw.scissorRect)
                    << ',' << draw.triangleCount << ',' << uint32_t(draw.textureOn) << ",\""
                    << joinHex(textures) << "\"," << hex64(combiner) << ',' << hex64(otherMode)
                    << ',' << draw.rdpParams.primColor.x << ':' << draw.rdpParams.primColor.y << ':'
                    << draw.rdpParams.primColor.z << ':' << draw.rdpParams.primColor.w << ','
                    << draw.wr64TaskSequence << ',' << hex64(draw.wr64TaskAddress) << ','
                    << hex64(draw.wr64TaskContextRa) << ',' << hex64(draw.wr64RootDisplayList) << ','
                    << hex64(draw.wr64Ucode) << ',' << hex64(draw.wr64UcodeData) << '\n';
                const std::string rowText = row.str();

                if (rollingFrame != workload.submissionFrame) {
                    rollingFrame = workload.submissionFrame;
                    rollingRows.clear();
                    rollingSignatures.clear();
                }
                if (rollingSignatures.emplace(signature).second) {
                    rollingRows.emplace_back(rowText);
                }
                if (startupCandidates.is_open() && (workload.submissionFrame != 0) &&
                    (workload.submissionFrame <= startupFrameLimit)) {
                    uint64_t startupKey = signature;
                    startupKey = (startupKey ^ workload.submissionFrame) * FNVPrime;
                    if (observedStartupCalls.emplace(startupKey).second) {
                        startupCandidates << rowText;
                        startupCandidates.flush();
                    }
                }
            }
        };

        ComposerState &composerState() {
            static ComposerState state;
            return state;
        }
    }

    uint64_t composerCallIdentity(const Workload &workload,
        uint32_t framebufferPairIndex, uint32_t projectionIndex, uint32_t callIndex,
        const Projection &projection, const GameCall &call)
    {
        return composerCallSignature(workload, framebufferPairIndex,
            projectionIndex, callIndex, projection, call);
    }

    void observeFramebuffer(const Workload &workload, uint32_t framebufferPairIndex,
        uint32_t framebufferWidth, uint32_t framebufferHeight,
        uint32_t targetWidth, uint32_t targetHeight)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        TraceState &state = traceState();
        state.initialize();
        if (!state.enabled || (framebufferPairIndex >= workload.fbPairs.size())) return;

        if (state.hasPendingFrame && (workload.submissionFrame != state.pendingFrame)) {
            state.finishPendingFrame();
        }
        if (!state.hasPendingFrame || (workload.submissionFrame != state.pendingFrame)) {
            state.hasPendingFrame = true;
            state.pendingFrame = workload.submissionFrame;
        }

        const FramebufferPair &fbPair = workload.fbPairs[framebufferPairIndex];
        for (const FramebufferOperation &operation : fbPair.startFbOperations) {
            state.recordCopyProducer(workload.submissionFrame, framebufferPairIndex, "start",
                operation, framebufferWidth, framebufferHeight, targetWidth, targetHeight);
        }
        for (const FramebufferOperation &operation : fbPair.endFbOperations) {
            state.recordCopyProducer(workload.submissionFrame, framebufferPairIndex, "end",
                operation, framebufferWidth, framebufferHeight, targetWidth, targetHeight);
        }
        uint64_t pairSignature = FNVOffset;
        pairSignature = hashValue(pairSignature, fbPair.colorImage.fmt);
        pairSignature = hashValue(pairSignature, fbPair.colorImage.siz);
        pairSignature = hashValue(pairSignature, fbPair.colorImage.width);
        pairSignature = hashValue(pairSignature, fbPair.projectionCount);
        pairSignature = hashValue(pairSignature, fbPair.depthRead);
        pairSignature = hashValue(pairSignature, fbPair.depthWrite);
        pairSignature = hashValue(pairSignature, fbPair.fillRectOnly);
        pairSignature = hashValue(pairSignature, fbPair.flushReason);

        std::ostringstream orderedPassIds;
        for (uint32_t projectionIndex = 0; projectionIndex < fbPair.projectionCount; projectionIndex++) {
            const Projection &projection = fbPair.projections[projectionIndex];
            const PassEvidence evidence = classifyPass(workload, fbPair, projection);
            const uint32_t passId = state.recordPass(projection, evidence);
            for (uint32_t callIndex = 0; callIndex < projection.gameCallCount; callIndex++) {
                const DrawCall &call = projection.gameCalls[callIndex].callDesc;
                const uint32_t tileEnd = std::min<uint32_t>(
                    call.tileIndex + call.tileCount, uint32_t(workload.drawData.callTiles.size()));
                for (uint32_t tileIndex = call.tileIndex; tileIndex < tileEnd; tileIndex++) {
                    state.recordCopyConsumer(workload.submissionFrame, framebufferPairIndex,
                        projectionIndex, callIndex, tileIndex, projection, call,
                        workload.drawData.callTiles[tileIndex], framebufferWidth,
                        framebufferHeight, targetWidth, targetHeight);
                }
            }
            pairSignature = hashValue(pairSignature, evidence.signature);
            if (projectionIndex > 0) orderedPassIds << ';';
            orderedPassIds << passId;
        }

        PairObservation observation;
        observation.pair = framebufferPairIndex;
        observation.signature = pairSignature;
        observation.sourceDimensions = std::to_string(framebufferWidth) + 'x' + std::to_string(framebufferHeight);
        observation.targetDimensions = std::to_string(targetWidth) + 'x' + std::to_string(targetHeight);
        observation.passIds = orderedPassIds.str();
        state.pendingPairs.emplace_back(std::move(observation));
        state.copies.flush();
    }

    ComposerOverride composerCallOverride(const Workload &workload,
        uint32_t framebufferPairIndex, uint32_t projectionIndex, uint32_t callIndex,
        const Projection &projection, const GameCall &call,
        uint32_t framebufferWidth, uint32_t framebufferHeight,
        uint32_t targetWidth, uint32_t targetHeight)
    {
        ComposerOverride result;

        // The signature is consumed unconditionally by the callers - the ortho
        // viewport fixes in the framebuffer renderer select their target calls by
        // it - so it has to be produced whether or not the composer is enabled. It
        // is a pure function of its arguments and touches no shared state, so it
        // needs no lock.
        result.signature = composerCallSignature(workload, framebufferPairIndex,
            projectionIndex, callIndex, projection, call);
        if (!WR64_DIAGNOSTIC_ENABLED) return result;

        // This runs once per draw call on the framebuffer path. Taking a process
        // global mutex here when the composer is switched off, which is the shipping
        // configuration, serialized every draw call against the workload thread for
        // no reason at all. Read the environment through a latched local static so
        // the disabled path is a single predictable branch.
        static const bool composerEnvEnabled = []() {
            const char *setting = std::getenv("WR64_COMPOSER");
            return (setting != nullptr) && (setting[0] != '\0') && (setting[0] != '0');
        }();
        if (!composerEnvEnabled) return result;

        // Framebuffer work can be prepared concurrently. ComposerState owns
        // mutable capture containers, streams, and profile state, so every
        // public observation/override transaction must be serialized.
        static std::mutex composerMutex;
        const std::lock_guard<std::mutex> lock(composerMutex);

        ComposerState &state = composerState();
        state.reload(workload.submissionFrame);
        // initialize() can still clear this if it failed to open its output files.
        if (!state.enabled) return result;

        state.observeCall(result.signature, workload, framebufferPairIndex, projectionIndex,
            callIndex, projection, call, framebufferWidth, framebufferHeight, targetWidth,
            targetHeight);
        if (workload.submissionFrame != 0) {
            lastNonzeroWorkloadFrame.store(workload.submissionFrame, std::memory_order_release);
        }
        const bool matchesLegacy = (state.config.selectedSignature != 0) &&
            (result.signature == state.config.selectedSignature);
        const bool matchesGroup = state.config.selectedSignatures.find(result.signature) !=
            state.config.selectedSignatures.end();
        if (!matchesLegacy && !matchesGroup) {
            return result;
        }

        result.matched = true;
        if (workload.submissionFrame != 0) {
            lastMatchedWorkloadFrame.store(workload.submissionFrame, std::memory_order_release);
        }
        result.suppress = state.config.suppress;
        result.highlightColor = state.config.highlightColor;
        result.rectTranslateX = state.config.rectTranslateX;
        result.rectTranslateY = state.config.rectTranslateY;
        result.rectLeft = state.config.rectLeft;
        result.rectTop = state.config.rectTop;
        result.rectRight = state.config.rectRight;
        result.rectBottom = state.config.rectBottom;
        result.scissorTranslateX = state.config.scissorTranslateX;
        result.scissorTranslateY = state.config.scissorTranslateY;
        result.scissorLeft = state.config.scissorLeft;
        result.scissorTop = state.config.scissorTop;
        result.scissorRight = state.config.scissorRight;
        result.scissorBottom = state.config.scissorBottom;
        result.viewportLeft = state.config.viewportLeft;
        result.viewportTop = state.config.viewportTop;
        result.viewportRight = state.config.viewportRight;
        result.viewportBottom = state.config.viewportBottom;
        return result;
    }

    uint64_t composerLastNonzeroWorkloadFrame() {
        if (!WR64_DIAGNOSTIC_ENABLED) return 0;
        return lastNonzeroWorkloadFrame.load(std::memory_order_acquire);
    }

    uint64_t composerLastMatchedWorkloadFrame() {
        if (!WR64_DIAGNOSTIC_ENABLED) return 0;
        return lastMatchedWorkloadFrame.load(std::memory_order_acquire);
    }
}
