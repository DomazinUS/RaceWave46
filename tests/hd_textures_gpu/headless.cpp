// Headless production TextureCache integration. No window, swapchain, or game.
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <thread>
#include "xxHash/xxh3.h"
#include "gbi/rt64_f3d.h"
#include "plume_d3d12.h"
#include "render/rt64_texture_cache.h"
#include "common/rt64_tmem_hasher.h"
#include "common/rt64_filesystem_zip.h"
#include "ddspp/ddspp.h"

using namespace RT64;
using namespace plume;
namespace fs = std::filesystem;
size_t checks = 0;
void require(bool condition, const char *message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
std::vector<uint8_t> bytes(const fs::path &path) {
    std::ifstream input(path, std::ios::binary);
    require(bool(input), "Fixture input missing");
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}
struct Sample {
    std::string hashText, path;
    uint64_t hash;
    uint32_t width, height, tlut;
    LoadTile tile;
    std::vector<uint8_t> tmem, dds, original;
    ddspp::Descriptor descriptor{};
};
Sample nativeSample(const fs::path &dump, const std::string &hashText) {
    Sample s;
    s.hashText = hashText;
    s.hash = ReplacementDatabase::stringToHash(hashText);
    auto tileBytes = bytes(dump / (hashText + ".v5.tile.json"));
    json j = json::parse(tileBytes);
    s.width = j.at("width"); s.height = j.at("height");
    s.tile = j.at("tile").get<LoadTile>();
    const auto tlut = j.at("tlut").get<std::string>();
    s.tlut = tlut == "None" ? 0 : tlut == "RGBA16" ? G_TT_RGBA16 : G_TT_IA16;
    s.tmem = bytes(dump / (hashText + ".v5.tmem"));
    require(s.tmem.size() == 4096, "Native TMEM must be 4096 bytes");
    require(TMEMHasher::hash(s.tmem.data(), s.tile, s.width, s.height, s.tlut, 5) == s.hash,
        "Recomputed production TMEM v5 hash differs from dump filename");
    return s;
}
Texture *use(TextureCache &cache, const Sample &s, bool replacement, bool expectedHalfShift = true) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(20);
    uint32_t index = 0; interop::float2 scale; interop::float3 dimensions;
    bool replaced = false, mipmaps = false, shifted = false;
    for (;;) {
        bool found = cache.useTexture(s.hash, 1, index, scale, dimensions, replaced, mipmaps, shifted);
        if (found && replaced == replacement) break;
        require(std::chrono::steady_clock::now() < deadline, "Texture replacement state timed out");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    require(scale.x == (replacement ? 4.0f : 1.0f) && scale.y == (replacement ? 4.0f : 1.0f),
        "Texture scaling differs from expected native/4x dimensions");
    require(dimensions.x == s.width * scale.x && dimensions.y == s.height * scale.y,
        "Texture dimensions do not match replacement scale");
    require(shifted == (replacement && expectedHalfShift), "Half-texel shift differs from expected setting");
    std::unique_lock lock(cache.textureMapMutex);
    Texture *selected = replacement ? cache.textureMap.textureReplacements[index] : cache.textureMap.textures[index];
    require(selected != nullptr && selected->texture != nullptr, "Selected GPU texture is null");
    return selected;
}
std::vector<uint8_t> readback(RenderWorker &worker, Texture *texture, uint32_t mip = 0) {
    const uint32_t w = std::max(texture->width >> mip, 1U), h = std::max(texture->height >> mip, 1U);
    const uint32_t block = RenderFormatBlockWidth(texture->format), unit = RenderFormatSize(texture->format);
    const uint32_t pitch = ((w + block - 1) / block) * unit;
    const uint32_t aligned = (pitch + 255) & ~255U, rows = (h + block - 1) / block;
    auto buffer = worker.device->createBuffer(RenderBufferDesc::ReadbackBuffer(aligned * rows));
    worker.commandList->begin();
    worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(texture->texture.get(), RenderTextureLayout::COPY_SOURCE));
    // Native readback avoids Plume's destination-texture sample-position helper:
    // the readback destination is a buffer. Production upload is unchanged.
    auto *nativeTexture = static_cast<D3D12Texture *>(texture->texture.get());
    D3D12_TEXTURE_COPY_LOCATION dst{};
    dst.pResource = static_cast<D3D12Buffer *>(buffer.get())->d3d;
    dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    auto desc = nativeTexture->d3d->GetDesc();
    static_cast<D3D12Device *>(worker.device)->d3d->GetCopyableFootprints(&desc, mip, 1, 0, &dst.PlacedFootprint, nullptr, nullptr, nullptr);
    D3D12_TEXTURE_COPY_LOCATION src{};
    src.pResource = nativeTexture->d3d; src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX; src.SubresourceIndex = mip;
    static_cast<D3D12CommandList *>(worker.commandList.get())->d3d->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(texture->texture.get(), RenderTextureLayout::SHADER_READ));
    worker.commandList->end(); worker.execute(); worker.wait();
    const auto *mapped = static_cast<const uint8_t *>(buffer->map());
    require(mapped != nullptr, "GPU readback map failed");
    std::vector<uint8_t> result(pitch * rows);
    for (uint32_t r = 0; r < rows; ++r) std::memcpy(result.data() + r * pitch, mapped + r * aligned, pitch);
    buffer->unmap();
    return result;
}
void verifyDDS(RenderWorker &reader, Texture *texture, const Sample &s) {
    require(texture->mipmaps == s.descriptor.numMips, "DDS mip count changed during upload");
    require((s.descriptor.format == ddspp::BC1_UNORM && texture->format == RenderFormat::BC1_UNORM) ||
        (s.descriptor.format == ddspp::BC3_UNORM && texture->format == RenderFormat::BC3_UNORM), "DDS format changed during upload");
    for (uint32_t mip = 0; mip < texture->mipmaps; ++mip) {
        auto pixels = readback(reader, texture, mip);
        const size_t offset = s.descriptor.headerSize + ddspp::get_offset(s.descriptor, mip, 0);
        require(offset + pixels.size() <= s.dds.size(), "DDS payload bounds exceeded");
        require(std::equal(pixels.begin(), pixels.end(), s.dds.begin() + offset), "GPU compressed payload differs from original DDS");
    }
    std::printf("PASS: %s %s, %ux%u -> %ux%u, %u mip(s), GPU payload byte-exact\n", s.hashText.c_str(),
        s.descriptor.format == ddspp::BC1_UNORM ? "BC1" : "BC3", s.width, s.height, texture->width, texture->height, texture->mipmaps);
    std::fflush(stdout);
}
int main(int argc, char **argv) {
    try {
        require(argc == 3 || argc == 4, "Usage: headless.exe pack.rtz native_dump_directory [static_reference_pack.rtz]");
        const bool dynamic = argc == 4;
        fs::path pack = fs::absolute(argv[1]), dump = fs::absolute(argv[2]);
        auto archive = FileSystemZip::create(pack, "");
        require(archive != nullptr, "Production RT64 archive loader rejected pack");
        std::vector<uint8_t> dbBytes;
        require(archive->load(ReplacementDatabaseFilename, dbBytes), "rt64.json missing from archive");
        auto inputJson = json::parse(dbBytes);
        auto reference = dynamic ? FileSystemZip::create(fs::absolute(argv[3]), "") : nullptr;
        if (dynamic) {
            require(inputJson.at("textures").empty(), "Dynamic fixture must have zero static native mappings");
            require(inputJson.at("configuration").at("wr64DolphinCompatible") == true, "Dynamic opt-in missing");
            require(reference != nullptr && reference->load(ReplacementDatabaseFilename, dbBytes), "Static reference database unavailable");
        }
        auto database = json::parse(dbBytes).get<ReplacementDatabase>();
        std::vector<Sample> samples;
        const bool hasDerived = std::any_of(database.textures.begin(), database.textures.end(), [](const auto &entry) { return entry.path.find("derived/") == 0; });
        bool bc1 = false, bc3 = false, ci8 = false, derived = false;
        for (const auto &entry : database.textures) {
            std::vector<uint8_t> dds;
            require(archive->load(entry.path, dds), "Mapped DDS missing from archive");
            ddspp::Descriptor descriptor;
            require(ddspp::decode_header(dds.data(), descriptor) == ddspp::Success, "Mapped DDS header invalid");
            bool paletteEntry = entry.path.size() >= 6 && entry.path.substr(entry.path.size() - 6) == "_9.dds";
            bool derivedEntry = entry.path.find("derived/") == 0;
            bool select = (descriptor.format == ddspp::BC1_UNORM ? !bc1 : descriptor.format == ddspp::BC3_UNORM ? !bc3 : false) || (dynamic && paletteEntry && !ci8) || (derivedEntry && !derived);
            if (!select) continue;
            auto s = nativeSample(dump, entry.hashes.rt64);
            s.path = entry.path; s.dds = std::move(dds); s.descriptor = descriptor;
            samples.push_back(std::move(s));
            if (descriptor.format == ddspp::BC1_UNORM) bc1 = true; else bc3 = true;
            if (paletteEntry) ci8 = true;
            if (derivedEntry) derived = true;
            if (bc1 && bc3 && (!dynamic || ci8) && (!hasDerived || derived)) break;
        }
        require(bc1 && bc3, "Pack must provide native mapped BC1 and BC3 samples");
        require(!dynamic || ci8, "Dynamic fixture needs a real CI8 palette sample");
        require(!hasDerived || derived, "Expanded static fixture must exercise a cropped DDS");
        Sample fallback;
        bool foundFallback = false;
        for (const auto &entry : fs::directory_iterator(dump)) {
            auto name = entry.path().filename().string();
            if (name.size() != 24 || name.substr(16) != ".v5.tmem") continue;
            auto h = name.substr(0, 16);
            if (!database.getReplacement(h).isEmpty()) continue;
            fallback = nativeSample(dump, h); foundFallback = true; break;
        }
        require(foundFallback, "Need an unmapped native fallback sample");
        D3D12Interface rhi;
        require(rhi.isValid(), "D3D12 interface unavailable");
        auto device = rhi.createDevice("");
        require(device != nullptr, "D3D12 device unavailable");
        std::printf("Headless D3D12: %s\n", device->getDescription().name.c_str()); std::fflush(stdout);
        ShaderLibrary shaders(false, true);
        shaders.setupCommonShaders(&rhi, device.get());
        std::puts("Production shaders ready"); std::fflush(stdout);
        RenderWorker upload(device.get(), "HD texture native decode", RenderCommandListType::DIRECT);
        RenderWorker copy(device.get(), "HD texture copy", RenderCommandListType::COPY);
        RenderWorker reader(device.get(), "HD texture readback", RenderCommandListType::DIRECT);
        TextureCache cache(&upload, &copy, 2, &shaders);
        std::puts("Production cache ready"); std::fflush(stdout);
        cache.setReplacementPoolMaxSize(64 * 1024 * 1024);
        std::vector<Sample *> allSamples;
        for (auto &s : samples) allSamples.push_back(&s);
        allSamples.push_back(&fallback);
        for (const auto *s : allSamples) {
            cache.queueGPUUploadTMEM(s->hash, 1, s->tmem.data(), int(s->tmem.size()), s->width, s->height, s->tlut, s->tile, true);
        }
        cache.waitForGPUUploads();
        std::puts("Native TMEM uploads ready"); std::fflush(stdout);
        for (auto *s : allSamples) s->original = readback(reader, use(cache, *s, false));
        for (int cycle = 0; cycle < 2; ++cycle) {
            require(cache.loadReplacementDirectories({ReplacementDirectory(pack)}), "Production TextureCache rejected RTZ pack");
            for (const auto &s : samples) verifyDDS(reader, use(cache, s, true), s);
            require(readback(reader, use(cache, fallback, false)) == fallback.original, "Unmapped fallback changed when pack enabled");
            if (dynamic) {
                auto &d = cache.textureMap.replacementMap.fileSystemDolphinCaches.at(0);
                require(d.enabled && d.index.size() == 2266, "All 2266 source names must be indexed in production");
                require(d.resolvedPaths.size() == samples.size(), "Positive dynamic cache must contain all matched native samples");
                require(d.missingHashes.count(fallback.hash) == 1, "Unmapped native miss must be negatively cached");
                const auto positiveCount = d.resolvedPaths.size(), missingCount = d.missingHashes.size();
                for (int repeat = 0; repeat < 3; ++repeat) {
                    for (const auto *s : allSamples) {
                        std::vector<ReplacementResolvedPath> resolved;
                        cache.addResolvedPaths(s->hash, s->width, s->height, s->tlut, s->tile, s->tmem, true, resolved);
                        require(resolved.size() == (s == &fallback ? 0 : 1), "Repeated cached lookup changed match result");
                    }
                }
                require(d.resolvedPaths.size() == positiveCount && d.missingHashes.size() == missingCount, "Repeated lookups must reuse positive/negative cache entries");
                std::puts("PASS: zero static mappings; full index, CI8 palette, positive and negative caches validated");
            }
            cache.waitForAllStreamThreads(false);
            cache.waitForGPUUploads();
            cache.clearReplacementDirectories();
            require(cache.textureMap.replacementMap.fileSystemDolphinCaches.empty(), "Clear must discard dynamic caches");
            for (const auto *s : allSamples) {
                require(readback(reader, use(cache, *s, false)) == s->original, "Native fallback pixels changed after disabling pack");
            }
            std::printf("PASS: enable/clear cycle %d, original RGBA pixels restored; unmapped native fallback unchanged\n", cycle + 1); std::fflush(stdout);
        }
        if (dynamic) {
            const auto &s = samples.front();
            const auto overrideDir = pack.parent_path() / "static-override";
            const auto sameFsDir = pack.parent_path() / "same-fs-static-override";
            const auto verifyPriority = [&](const std::vector<ReplacementDirectory> &directories, const char *path, bool shifted) {
                require(cache.loadReplacementDirectories(directories), "Priority fixture pack load failed");
                // Waiting for useTexture's published result also completes the reload resolution batch.
                verifyDDS(reader, use(cache, s, true, shifted), s);
                std::vector<ReplacementResolvedPath> resolved;
                cache.addResolvedPaths(s.hash, s.width, s.height, s.tlut, s.tile, s.tmem, true, resolved);
                require(resolved.size() == 1 && resolved.front().relativePath == path, "Filesystem/static replacement priority is wrong");
                require(resolved.front().fileSystemIndex == directories.size() - 1, "Highest priority filesystem must win");
                require((resolved.front().resolvedShift == ReplacementShift::Half) == shifted, "Static override shift was ignored");
                cache.waitForAllStreamThreads(false); cache.waitForGPUUploads(); cache.clearReplacementDirectories();
            };
            verifyPriority({ReplacementDirectory(overrideDir), ReplacementDirectory(pack)}, s.path.c_str(), true);
            verifyPriority({ReplacementDirectory(pack), ReplacementDirectory(overrideDir)}, "fixture-override.dds", false);
            verifyPriority({ReplacementDirectory(sameFsDir)}, "fixture-override.dds", false);
            std::puts("PASS: higher-priority dynamic/static packs and same-filesystem explicit override precedence");
        }
        require(SUCCEEDED(static_cast<D3D12Device *>(device.get())->d3d->GetDeviceRemovedReason()), "GPU device removed");
        std::printf("PASS: %zu checks. Production archive/database/hash/decode/upload/use and enable/clear/restore validated headlessly.\n", checks);
        return 0;
    } catch (const std::exception &e) { std::fprintf(stderr, "FAIL: %s\n", e.what()); return 1; }
}
