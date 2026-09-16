#include "wr64_diagnostic_policy.h"
#include "wr64_composer_window.hpp"

#ifdef WR64_ENABLE_RT64

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "render/rt64_wr64_layer_trace.h"

namespace wr64::composer {
namespace {

constexpr wchar_t kClassName[] = L"WR64ComposerWindow";
constexpr wchar_t kTitle[] = L"Wave Race 64 - Layer Composer";

enum ControlId : int {
    IdCandidates = 100,
    IdCapture,
    IdReload,
    IdFreeze,
    IdSort,
    IdFilter,
    IdExport,
    IdApply,
    IdClear,
    IdSuppress,
    IdTint,
    IdRectX,
    IdRectY,
    IdRectL,
    IdRectT,
    IdRectR,
    IdRectB,
    IdScissorX,
    IdScissorY,
    IdScissorL,
    IdScissorT,
    IdScissorR,
    IdScissorB,
    IdViewportL,
    IdViewportT,
    IdViewportR,
    IdViewportB,
};

struct Candidate {
    std::string signature;
    std::string details;
    std::string groupKey;
    std::array<int32_t, 4> rect{};
};

struct CandidateGroup {
    std::vector<size_t> members;
    std::string summary;
    std::string details;
    std::string groupKey;
    std::array<int32_t, 4> bounds{};
    size_t originalIndex = 0;
    size_t stateFamily = 0;
    std::vector<size_t> renderPeers;
    std::vector<size_t> overlaps;
};

struct Profile {
    uint64_t captureId = 0;
    std::string signature = "0000000000000000";
    std::vector<std::string> signatures;
    std::string tint = "FF00FFFF";
    bool suppress = false;
    std::array<std::string, 2> rectTranslate{"0", "0"};
    std::array<std::string, 4> rectEdges{"0", "0", "0", "0"};
    std::array<std::string, 2> scissorTranslate{"0", "0"};
    std::array<std::string, 4> scissorEdges{"0", "0", "0", "0"};
    std::array<std::string, 4> viewportEdges{"0", "0", "0", "0"};
};

struct WindowState {
    HWND gameWindow = nullptr;
    HWND window = nullptr;
    HWND capture = nullptr;
    HWND reload = nullptr;
    HWND freeze = nullptr;
    HWND header = nullptr;
    HWND summary = nullptr;
    HWND sortLabel = nullptr;
    HWND sort = nullptr;
    HWND filterLabel = nullptr;
    HWND filter = nullptr;
    HWND candidates = nullptr;
    HWND details = nullptr;
    HWND diagnosticLabel = nullptr;
    HWND suppress = nullptr;
    HWND tint = nullptr;
    HWND rectTranslateLabel = nullptr;
    HWND rectEdgesLabel = nullptr;
    HWND scissorTranslateLabel = nullptr;
    HWND scissorEdgesLabel = nullptr;
    HWND viewportEdgesLabel = nullptr;
    HWND apply = nullptr;
    HWND clear = nullptr;
    HWND exportSelection = nullptr;
    HWND footer = nullptr;
    std::array<HWND, 2> rectTranslate{};
    std::array<HWND, 4> rectEdges{};
    std::array<HWND, 2> scissorTranslate{};
    std::array<HWND, 4> scissorEdges{};
    std::array<HWND, 4> viewportEdges{};
    HFONT font = nullptr;
    std::filesystem::path profilePath;
    std::filesystem::path candidatePath;
    std::filesystem::path selectionPath;
    std::vector<Candidate> rows;
    std::vector<CandidateGroup> groups;
    std::vector<size_t> displayOrder;
    std::unordered_set<size_t> selectedGroups;
    Profile profile;
    std::atomic_bool captureKeyboard{false};
    int sortMode = 0;
    int filterMode = 0;
    uint64_t loadedCaptureId = 0;
};

WindowState state;
std::atomic_bool gameFrozen{false};
std::atomic_bool renderRequestPending{false};
std::atomic_bool renderRequestNeedsMatch{false};
std::atomic_uint64_t renderRequestBaseline{0};
std::atomic_uint32_t renderRequestBudget{0};
std::mutex freezeMutex;
std::condition_variable freezeCondition;

std::string trim(std::string value) {
    const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char c) {
        return std::isspace(c) != 0;
    });
    const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char c) {
        return std::isspace(c) != 0;
    }).base();
    return (first < last) ? std::string(first, last) : std::string();
}

std::vector<std::string> splitList(const std::string& value, size_t expected) {
    std::vector<std::string> result;
    std::istringstream input(value);
    std::string item;
    while (std::getline(input, item, ',')) {
        result.push_back(trim(item));
    }
    while (result.size() < expected) result.push_back("0");
    result.resize(expected);
    return result;
}

std::vector<std::string> splitCsv(const std::string& line) {
    std::vector<std::string> result;
    std::string field;
    bool quoted = false;
    for (size_t i = 0; i < line.size(); i++) {
        const char c = line[i];
        if (c == '"') {
            if (quoted && (i + 1 < line.size()) && (line[i + 1] == '"')) {
                field.push_back('"');
                i++;
            }
            else {
                quoted = !quoted;
            }
        }
        else if ((c == ',') && !quoted) {
            result.push_back(field);
            field.clear();
        }
        else {
            field.push_back(c);
        }
    }
    result.push_back(field);
    return result;
}

bool parseRect(const std::string& value, std::array<int32_t, 4>& rect) {
    std::istringstream input(value);
    std::string field;
    try {
        for (size_t i = 0; i < rect.size(); i++) {
            if (!std::getline(input, field, ':')) return false;
            rect[i] = std::stoi(trim(field));
        }
        if (std::getline(input, field, ':')) return false;
    }
    catch (...) {
        return false;
    }
    return true;
}

bool rectanglesConnect(const std::array<int32_t, 4>& a,
    const std::array<int32_t, 4>& b)
{
    constexpr int32_t tolerance = 4; // RDP coordinates are quarter-pixels.
    return (a[0] <= (b[2] + tolerance)) && (b[0] <= (a[2] + tolerance)) &&
        (a[1] <= (b[3] + tolerance)) && (b[1] <= (a[3] + tolerance));
}

std::string joinStrings(const std::vector<std::string>& values) {
    std::ostringstream output;
    for (size_t i = 0; i < values.size(); i++) {
        if (i != 0) output << ',';
        output << values[i];
    }
    return output.str();
}

void readProfile() {
    Profile next;
    std::ifstream input(state.profilePath);
    std::string line;
    while (std::getline(input, line)) {
        const size_t comment = line.find('#');
        if (comment != std::string::npos) line.erase(comment);
        const size_t equals = line.find('=');
        if (equals == std::string::npos) continue;
        const std::string key = trim(line.substr(0, equals));
        const std::string value = trim(line.substr(equals + 1));
        try {
            if (key == "capture_id") next.captureId = std::stoull(value);
        }
        catch (...) {
            next.captureId = 0;
        }
        if (key == "selected_signature") next.signature = value;
        else if (key == "selected_signatures") {
            std::istringstream signatures(value);
            std::string signature;
            while (std::getline(signatures, signature, ',')) {
                signature = trim(signature);
                if (!signature.empty()) next.signatures.push_back(signature);
            }
        }
        else if (key == "tint_rgba") next.tint = value;
        else if (key == "suppress") next.suppress = (value == "1") || (value == "true");
        else if (key == "rect_translate") {
            const auto values = splitList(value, 2);
            std::copy(values.begin(), values.end(), next.rectTranslate.begin());
        }
        else if (key == "rect_edges") {
            const auto values = splitList(value, 4);
            std::copy(values.begin(), values.end(), next.rectEdges.begin());
        }
        else if (key == "scissor_translate") {
            const auto values = splitList(value, 2);
            std::copy(values.begin(), values.end(), next.scissorTranslate.begin());
        }
        else if (key == "scissor_edges") {
            const auto values = splitList(value, 4);
            std::copy(values.begin(), values.end(), next.scissorEdges.begin());
        }
        else if (key == "viewport_edges") {
            const auto values = splitList(value, 4);
            std::copy(values.begin(), values.end(), next.viewportEdges.begin());
        }
    }
    if (next.signatures.empty() && (next.signature != "0000000000000000")) {
        next.signatures.push_back(next.signature);
    }
    state.profile = next;
}

std::string getText(HWND control) {
    const int length = GetWindowTextLengthA(control);
    std::string value(static_cast<size_t>(length) + 1, '\0');
    if (length > 0) GetWindowTextA(control, value.data(), length + 1);
    value.resize(static_cast<size_t>(length));
    return value;
}

void setText(HWND control, const std::string& value) {
    SetWindowTextA(control, value.c_str());
}

void loadControls() {
    setText(state.tint, state.profile.tint);
    SendMessageW(state.suppress, BM_SETCHECK,
        state.profile.suppress ? BST_CHECKED : BST_UNCHECKED, 0);
    for (size_t i = 0; i < 2; i++) {
        setText(state.rectTranslate[i], state.profile.rectTranslate[i]);
        setText(state.scissorTranslate[i], state.profile.scissorTranslate[i]);
    }
    for (size_t i = 0; i < 4; i++) {
        setText(state.rectEdges[i], state.profile.rectEdges[i]);
        setText(state.scissorEdges[i], state.profile.scissorEdges[i]);
        setText(state.viewportEdges[i], state.profile.viewportEdges[i]);
    }
}

void readControls() {
    state.profile.tint = trim(getText(state.tint));
    state.profile.suppress = SendMessageW(state.suppress, BM_GETCHECK, 0, 0) == BST_CHECKED;
    for (size_t i = 0; i < 2; i++) {
        state.profile.rectTranslate[i] = trim(getText(state.rectTranslate[i]));
        state.profile.scissorTranslate[i] = trim(getText(state.scissorTranslate[i]));
    }
    for (size_t i = 0; i < 4; i++) {
        state.profile.rectEdges[i] = trim(getText(state.rectEdges[i]));
        state.profile.scissorEdges[i] = trim(getText(state.scissorEdges[i]));
        state.profile.viewportEdges[i] = trim(getText(state.viewportEdges[i]));
    }
}

template <size_t N>
std::string join(const std::array<std::string, N>& values) {
    std::ostringstream output;
    for (size_t i = 0; i < N; i++) {
        if (i != 0) output << ',';
        output << (values[i].empty() ? "0" : values[i]);
    }
    return output.str();
}

void requestRenderPulse() {
    if (!gameFrozen.load(std::memory_order_acquire)) return;
    const bool needsMatch = !state.profile.signatures.empty() ||
        (state.profile.signature != "0000000000000000");
    const uint64_t baseline = needsMatch
        ? RT64::WR64LayerTrace::composerLastMatchedWorkloadFrame()
        : RT64::WR64LayerTrace::composerLastNonzeroWorkloadFrame();
    renderRequestNeedsMatch.store(needsMatch, std::memory_order_release);
    renderRequestBaseline.store(baseline, std::memory_order_release);
    renderRequestBudget.store(6, std::memory_order_release);
    renderRequestPending.store(true, std::memory_order_release);
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
        "[composer-freeze] workload refresh requested; baseline=%llu mode=%s budget=6\n",
        static_cast<unsigned long long>(baseline), needsMatch ? "matched" : "any"));
    freezeCondition.notify_all();
}

bool writeProfile() {
    const std::filesystem::path temporary = state.profilePath.wstring() + L".composer.tmp";
    std::ofstream output(temporary, std::ios::out | std::ios::trunc);
    if (!output.is_open()) return false;
    output << "# Written atomically by the WR64 Layer Composer pop-out.\n"
        << "capture_id=" << state.profile.captureId << "\n"
        << "selected_signature=" << state.profile.signature << "\n"
        << "selected_signatures=" << joinStrings(state.profile.signatures) << "\n"
        << "tint_rgba=" << (state.profile.tint.empty() ? "0" : state.profile.tint) << "\n"
        << "suppress=" << (state.profile.suppress ? 1 : 0) << "\n"
        << "rect_translate=" << join(state.profile.rectTranslate) << "\n"
        << "scissor_translate=" << join(state.profile.scissorTranslate) << "\n"
        << "rect_edges=" << join(state.profile.rectEdges) << "\n"
        << "scissor_edges=" << join(state.profile.scissorEdges) << "\n"
        << "viewport_edges=" << join(state.profile.viewportEdges) << "\n";
    output.close();
    const bool replaced = MoveFileExW(temporary.c_str(), state.profilePath.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
    if (replaced) requestRenderPulse();
    return replaced;
}

void setStatus(const std::string& message) {
    setText(state.details, message);
}

void setGameFrozen(bool frozen) {
    gameFrozen.store(frozen, std::memory_order_release);
    renderRequestPending.store(false, std::memory_order_release);
    renderRequestNeedsMatch.store(false, std::memory_order_release);
    renderRequestBudget.store(0, std::memory_order_release);
    if (!frozen) freezeCondition.notify_all();

    if (state.freeze != nullptr) {
        SetWindowTextW(state.freeze, frozen ? L"Resume game" : L"Freeze game");
    }
    setStatus(frozen
        ? "GAME HELD. Capture, selection, and edits render one refresh frame, then automatically hold again."
        : "Game resumed.");
}

int64_t groupArea(const CandidateGroup& group) {
    return int64_t(std::max<int32_t>(0, group.bounds[2] - group.bounds[0])) *
        int64_t(std::max<int32_t>(0, group.bounds[3] - group.bounds[1]));
}

bool boundsOverlap(const CandidateGroup& a, const CandidateGroup& b) {
    return (a.bounds[0] < b.bounds[2]) && (b.bounds[0] < a.bounds[2]) &&
        (a.bounds[1] < b.bounds[3]) && (b.bounds[1] < a.bounds[3]);
}

std::string layerNumbers(const std::vector<size_t>& indices) {
    if (indices.empty()) return "none";
    std::ostringstream output;
    const size_t shown = std::min<size_t>(indices.size(), 12);
    for (size_t i = 0; i < shown; i++) {
        if (i != 0) output << ", ";
        output << 'L' << (state.groups[indices[i]].originalIndex + 1);
    }
    if (indices.size() > shown) output << " ... (" << indices.size() << " total)";
    return output.str();
}

std::string groupDetails(size_t groupIndex) {
    const CandidateGroup& group = state.groups[groupIndex];
    std::ostringstream output;
    output << group.details
        << "\r\nRender-state family: R" << group.stateFamily
        << "\r\nSame-state peers: " << layerNumbers(group.renderPeers)
        << "\r\nOverlapping layers: " << layerNumbers(group.overlaps)
        << "\r\nArea (quarter-pixel units): " << groupArea(group);
    return output.str();
}

bool groupMatchesFilter(size_t groupIndex) {
    const CandidateGroup& group = state.groups[groupIndex];
    switch (state.filterMode) {
    case 1:
        return state.selectedGroups.find(groupIndex) != state.selectedGroups.end();
    case 2:
        return group.members.size() > 1;
    case 3:
        if (state.selectedGroups.find(groupIndex) != state.selectedGroups.end()) return true;
        for (size_t selected : state.selectedGroups) {
            if (state.groups[selected].groupKey == group.groupKey) return true;
        }
        return false;
    case 4:
        if (state.selectedGroups.find(groupIndex) != state.selectedGroups.end()) return true;
        for (size_t selected : state.selectedGroups) {
            const auto& overlaps = state.groups[selected].overlaps;
            if (std::find(overlaps.begin(), overlaps.end(), groupIndex) != overlaps.end()) return true;
        }
        return false;
    default:
        return true;
    }
}

std::string selectionReport() {
    std::vector<size_t> selected(state.selectedGroups.begin(), state.selectedGroups.end());
    std::sort(selected.begin(), selected.end(), [](size_t a, size_t b) {
        return state.groups[a].originalIndex < state.groups[b].originalIndex;
    });
    std::unordered_set<std::string> uniqueSignatures;
    std::array<int32_t, 4> combined{};
    bool hasBounds = false;
    size_t drawCount = 0;
    for (size_t index : selected) {
        const CandidateGroup& group = state.groups[index];
        drawCount += group.members.size();
        if (!hasBounds) {
            combined = group.bounds;
            hasBounds = true;
        }
        else {
            combined[0] = std::min(combined[0], group.bounds[0]);
            combined[1] = std::min(combined[1], group.bounds[1]);
            combined[2] = std::max(combined[2], group.bounds[2]);
            combined[3] = std::max(combined[3], group.bounds[3]);
        }
        for (size_t member : group.members) uniqueSignatures.emplace(state.rows[member].signature);
    }

    std::ostringstream output;
    output << "WR64 Composer selection report\n"
        << "capture_id=" << state.loadedCaptureId << "\n"
        << "logical_layers=" << selected.size() << "\n"
        << "member_draws=" << drawCount << "\n"
        << "unique_signatures=" << uniqueSignatures.size() << "\n";
    if (hasBounds) {
        output << "combined_bounds=" << combined[0] << ':' << combined[1] << ':'
            << combined[2] << ':' << combined[3] << "\n";
    }
    output << "selected_layers=" << layerNumbers(selected) << "\n\n";
    for (size_t index : selected) {
        const CandidateGroup& group = state.groups[index];
        output << "[L" << (group.originalIndex + 1) << "]\n"
            << "draws=" << group.members.size() << "\n"
            << "bounds=" << group.bounds[0] << ':' << group.bounds[1] << ':'
            << group.bounds[2] << ':' << group.bounds[3] << "\n"
            << "render_state_family=R" << group.stateFamily << "\n"
            << "same_state_peers=" << layerNumbers(group.renderPeers) << "\n"
            << "overlapping_layers=" << layerNumbers(group.overlaps) << "\n"
            << "signatures=";
        for (size_t i = 0; i < group.members.size(); i++) {
            if (i != 0) output << ',';
            output << state.rows[group.members[i]].signature;
        }
        output << "\n" << state.rows[group.members.front()].details << "\n\n";
    }
    return output.str();
}

bool copyToClipboard(const std::string& text) {
    if (!OpenClipboard(state.window)) return false;
    EmptyClipboard();
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (memory == nullptr) {
        CloseClipboard();
        return false;
    }
    void* destination = GlobalLock(memory);
    std::memcpy(destination, text.c_str(), text.size() + 1);
    GlobalUnlock(memory);
    if (SetClipboardData(CF_TEXT, memory) == nullptr) {
        GlobalFree(memory);
        CloseClipboard();
        return false;
    }
    CloseClipboard();
    return true;
}

void exportSelectionReport() {
    if (state.selectedGroups.empty()) {
        setStatus("Select one or more logical layers before exporting a handoff report.");
        return;
    }
    const std::string report = selectionReport();
    std::ofstream output(state.selectionPath, std::ios::out | std::ios::trunc);
    if (!output.is_open()) {
        setStatus("ERROR: could not write the Composer selection report.");
        return;
    }
    output << report;
    output.close();
    const bool copied = copyToClipboard(report);
    setStatus("Selection submitted locally to:\r\n" + state.selectionPath.string() +
        (copied ? "\r\n\r\nThe same report was copied to the clipboard. Tell Codex: submitted."
                : "\r\n\r\nClipboard copy failed, but the report file is complete. Tell Codex: submitted."));
}

void applyCurrentSelection() {
    const LRESULT count = SendMessageW(state.candidates, LB_GETSELCOUNT, 0, 0);
    state.selectedGroups.clear();
    if (count > 0) {
        std::vector<int> indices(static_cast<size_t>(count));
        SendMessageW(state.candidates, LB_GETSELITEMS, static_cast<WPARAM>(indices.size()),
            reinterpret_cast<LPARAM>(indices.data()));
        for (int visibleIndex : indices) {
            if ((visibleIndex >= 0) && (static_cast<size_t>(visibleIndex) < state.displayOrder.size())) {
                state.selectedGroups.emplace(state.displayOrder[static_cast<size_t>(visibleIndex)]);
            }
        }
    }

    state.profile.signatures.clear();
    std::unordered_set<std::string> seen;
    for (size_t groupIndex : state.selectedGroups) {
        for (size_t member : state.groups[groupIndex].members) {
            const std::string& signature = state.rows[member].signature;
            if (seen.emplace(signature).second) state.profile.signatures.push_back(signature);
        }
    }
    state.profile.signature = state.profile.signatures.empty()
        ? "0000000000000000" : state.profile.signatures.front();
    state.profile.tint = "FF00FFFF";
    state.profile.suppress = false;
    loadControls();
    writeProfile();

    if (state.selectedGroups.empty()) {
        setStatus("No logical layers selected. Renderer override cleared.");
    }
    else if (state.selectedGroups.size() == 1) {
        const size_t groupIndex = *state.selectedGroups.begin();
        setStatus(groupDetails(groupIndex) + "\r\n\r\nSelected and highlighted magenta.");
    }
    else {
        setStatus(selectionReport() + "\r\nAll selected logical layers are highlighted magenta and share live adjustments.");
    }
}

void refreshGroupList() {
    state.displayOrder.resize(state.groups.size());
    for (size_t i = 0; i < state.displayOrder.size(); i++) state.displayOrder[i] = i;
    state.displayOrder.erase(std::remove_if(state.displayOrder.begin(), state.displayOrder.end(),
        [](size_t index) { return !groupMatchesFilter(index); }), state.displayOrder.end());
    std::stable_sort(state.displayOrder.begin(), state.displayOrder.end(), [](size_t ai, size_t bi) {
        const CandidateGroup& a = state.groups[ai];
        const CandidateGroup& b = state.groups[bi];
        switch (state.sortMode) {
        case 1:
            if (a.members.size() != b.members.size()) return a.members.size() > b.members.size();
            break;
        case 2:
            if (a.bounds[1] != b.bounds[1]) return a.bounds[1] < b.bounds[1];
            if (a.bounds[0] != b.bounds[0]) return a.bounds[0] < b.bounds[0];
            break;
        case 3:
            if (groupArea(a) != groupArea(b)) return groupArea(a) > groupArea(b);
            break;
        case 4:
            if (a.stateFamily != b.stateFamily) return a.stateFamily < b.stateFamily;
            break;
        default:
            break;
        }
        return a.originalIndex < b.originalIndex;
    });

    SendMessageW(state.candidates, LB_RESETCONTENT, 0, 0);
    size_t multiDraw = 0;
    for (size_t groupIndex : state.displayOrder) {
        const CandidateGroup& group = state.groups[groupIndex];
        if (group.members.size() > 1) multiDraw++;
        std::ostringstream row;
        row << 'L' << (group.originalIndex + 1) << " | draws=" << group.members.size()
            << " | bounds=" << group.bounds[0] << ':' << group.bounds[1] << ':'
            << group.bounds[2] << ':' << group.bounds[3]
            << " | size=" << (group.bounds[2] - group.bounds[0]) << 'x'
            << (group.bounds[3] - group.bounds[1]) << " | R" << group.stateFamily
            << " | peers=" << group.renderPeers.size() << " | overlaps=" << group.overlaps.size();
        const std::string text = row.str();
        const LRESULT rowIndex = SendMessageA(state.candidates, LB_ADDSTRING, 0,
            reinterpret_cast<LPARAM>(text.c_str()));
        if (state.selectedGroups.find(groupIndex) != state.selectedGroups.end()) {
            SendMessageW(state.candidates, LB_SETSEL, TRUE, rowIndex);
        }
    }
    std::ostringstream information;
    information << "Capture " << state.loadedCaptureId << "  |  " << state.rows.size()
        << " draws -> " << state.groups.size() << " logical layers  |  " << multiDraw
        << " tiled/multi-draw  |  visible " << state.displayOrder.size()
        << "  |  selected " << state.selectedGroups.size()
        << "  |  Ctrl/Shift selects multiple layers";
    setText(state.summary, information.str());
}

void applyProfile() {
    readControls();
    if (writeProfile()) {
        setStatus("Applied live. The renderer will reload this profile on the next submitted frame.");
    }
    else {
        setStatus("ERROR: could not atomically replace the Composer profile.");
    }
}

void reloadCandidates() {
    state.rows.clear();
    state.groups.clear();
    state.selectedGroups.clear();
    SendMessageW(state.candidates, LB_RESETCONTENT, 0, 0);
    std::ifstream input(state.candidatePath);
    std::string header;
    std::getline(input, header);
    std::string line;
    uint64_t latestCaptureId = 0;
    while (std::getline(input, line)) {
        const auto fields = splitCsv(line);
        if (fields.size() < 18) continue;
        uint64_t candidateCaptureId = 0;
        try {
            candidateCaptureId = std::stoull(fields[0]);
        }
        catch (...) {
            continue;
        }
        if (candidateCaptureId < latestCaptureId) continue;
        if (candidateCaptureId > latestCaptureId) {
            latestCaptureId = candidateCaptureId;
            state.rows.clear();
        }
        Candidate candidate;
        candidate.signature = fields[1];
        if (!parseRect(fields[10], candidate.rect)) continue;
        std::ostringstream groupKey;
        groupKey << fields[3] << '|' << fields[4] << '|' << fields[7] << '|'
            << fields[8] << '|' << fields[9] << '|' << fields[13] << '|'
            << fields[14] << '|' << fields[15] << '|' << fields[16] << '|' << fields[17];
        candidate.groupKey = groupKey.str();
        std::ostringstream details;
        details << "Signature: " << fields[1] << "\r\n"
            << "Capture/frame: " << fields[0] << " / " << fields[2] << "\r\n"
            << "Pair/projection/call/UID: " << fields[3] << " / " << fields[4] << " / "
            << fields[5] << " / " << fields[6] << "\r\n"
            << "Projection: " << fields[7] << "\r\n"
            << "Source -> target: " << fields[8] << " -> " << fields[9] << "\r\n"
            << "Rectangle: " << fields[10] << "\r\n"
            << "Scissor: " << fields[11] << "\r\n"
            << "Triangles / texture: " << fields[12] << " / " << fields[13] << "\r\n"
            << "Texture hashes: " << fields[14] << "\r\n"
            << "Combiner: " << fields[15] << "\r\nOther mode: " << fields[16]
            << "\r\nPrimitive color: " << fields[17];
        if (fields.size() >= 24) {
            details << "\r\nTask sequence: " << fields[18]
                << "\r\nTask address: " << fields[19]
                << "\r\nTask context RA: " << fields[20]
                << "\r\nRoot display list: " << fields[21]
                << "\r\nMicrocode: " << fields[22]
                << "\r\nMicrocode data: " << fields[23];
        }
        candidate.details = details.str();
        state.rows.push_back(std::move(candidate));
    }

    std::vector<bool> assigned(state.rows.size(), false);
    for (size_t seed = 0; seed < state.rows.size(); seed++) {
        if (assigned[seed]) continue;
        CandidateGroup group;
        group.members.push_back(seed);
        group.bounds = state.rows[seed].rect;
        assigned[seed] = true;
        for (size_t cursor = 0; cursor < group.members.size(); cursor++) {
            const Candidate& current = state.rows[group.members[cursor]];
            for (size_t other = 0; other < state.rows.size(); other++) {
                if (assigned[other] || (current.groupKey != state.rows[other].groupKey) ||
                    !rectanglesConnect(current.rect, state.rows[other].rect)) continue;
                assigned[other] = true;
                group.members.push_back(other);
                const auto& rect = state.rows[other].rect;
                group.bounds[0] = std::min(group.bounds[0], rect[0]);
                group.bounds[1] = std::min(group.bounds[1], rect[1]);
                group.bounds[2] = std::max(group.bounds[2], rect[2]);
                group.bounds[3] = std::max(group.bounds[3], rect[3]);
            }
        }
        const Candidate& first = state.rows[group.members.front()];
        group.originalIndex = state.groups.size();
        group.groupKey = first.groupKey;
        std::ostringstream details;
        details << "Logical layer: " << (state.groups.size() + 1) << "\r\n"
            << "Member draws: " << group.members.size() << "\r\n"
            << "Combined bounds: " << group.bounds[0] << ':' << group.bounds[1] << ':'
            << group.bounds[2] << ':' << group.bounds[3] << "\r\n\r\n"
            << first.details;
        group.details = details.str();
        state.groups.push_back(std::move(group));
    }

    std::unordered_map<std::string, size_t> families;
    size_t nextFamily = 1;
    for (CandidateGroup& group : state.groups) {
        const auto [it, inserted] = families.emplace(group.groupKey, nextFamily);
        group.stateFamily = it->second;
        if (inserted) nextFamily++;
    }
    for (size_t i = 0; i < state.groups.size(); i++) {
        for (size_t j = 0; j < state.groups.size(); j++) {
            if (i == j) continue;
            if (state.groups[i].groupKey == state.groups[j].groupKey) {
                state.groups[i].renderPeers.push_back(j);
            }
            if (boundsOverlap(state.groups[i], state.groups[j])) {
                state.groups[i].overlaps.push_back(j);
            }
        }
    }
    state.loadedCaptureId = latestCaptureId;
    std::unordered_set<std::string> profileSignatures(
        state.profile.signatures.begin(), state.profile.signatures.end());
    for (size_t groupIndex = 0; groupIndex < state.groups.size(); groupIndex++) {
        for (size_t member : state.groups[groupIndex].members) {
            if (profileSignatures.find(state.rows[member].signature) != profileSignatures.end()) {
                state.selectedGroups.emplace(groupIndex);
                break;
            }
        }
    }
    refreshGroupList();
    std::ostringstream status;
    status << "Capture " << latestCaptureId << ": loaded " << state.rows.size()
        << " draws as " << state.groups.size()
        << " logical layers. Select a layer to highlight all connected tiles magenta.";
    setStatus(status.str());
}

HWND addControl(const wchar_t* type, const wchar_t* text, DWORD style, int id,
    int x, int y, int width, int height)
{
    HWND control = CreateWindowExW(0, type, text, WS_CHILD | WS_VISIBLE | style,
        x, y, width, height, state.window, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
        GetModuleHandleW(nullptr), nullptr);
    SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(state.font), TRUE);
    return control;
}

HWND addLabel(const wchar_t* text, int x, int y, int width, int height) {
    return addControl(L"STATIC", text, SS_LEFT, 0, x, y, width, height);
}

HWND addEdit(int id, int x, int y, int width = 58) {
    return addControl(L"EDIT", L"0", WS_BORDER | ES_AUTOHSCROLL, id, x, y, width, 24);
}

void createControls() {
    state.font = CreateFontW(-16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

    state.header = addLabel(L"Logical layers (connected RDP draws from one captured frame)", 12, 10, 440, 22);
    state.capture = addControl(L"BUTTON", L"Capture frame", BS_PUSHBUTTON,
        IdCapture, 460, 8, 116, 28);
    state.reload = addControl(L"BUTTON", L"Reload list", BS_PUSHBUTTON,
        IdReload, 582, 8, 104, 28);
    state.freeze = addControl(L"BUTTON", L"Freeze game", BS_PUSHBUTTON,
        IdFreeze, 692, 8, 112, 28);
    state.summary = addLabel(L"Capture summary", 12, 43, 430, 22);
    state.sortLabel = addLabel(L"Arrange/group:", 450, 43, 100, 22);
    state.sort = addControl(L"COMBOBOX", L"", CBS_DROPDOWNLIST | WS_VSCROLL,
        IdSort, 552, 40, 184, 160);
    SendMessageW(state.sort, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Original layer order"));
    SendMessageW(state.sort, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Draw count (largest first)"));
    SendMessageW(state.sort, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Bounds (top-left order)"));
    SendMessageW(state.sort, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Bounds area (largest first)"));
    SendMessageW(state.sort, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Render-state family"));
    SendMessageW(state.sort, CB_SETCURSEL, 0, 0);
    state.filterLabel = addLabel(L"Display filter:", 12, 70, 90, 22);
    state.filter = addControl(L"COMBOBOX", L"", CBS_DROPDOWNLIST | WS_VSCROLL,
        IdFilter, 104, 67, 220, 160);
    SendMessageW(state.filter, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"All logical layers"));
    SendMessageW(state.filter, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Selected layers only"));
    SendMessageW(state.filter, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Tiled / multi-draw only"));
    SendMessageW(state.filter, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Same-state family as selection"));
    SendMessageW(state.filter, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"Overlapping the selection"));
    SendMessageW(state.filter, CB_SETCURSEL, 0, 0);
    state.candidates = addControl(L"LISTBOX", L"", WS_BORDER | WS_VSCROLL | WS_HSCROLL |
        LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_EXTENDEDSEL, IdCandidates, 12, 98, 674, 547);
    state.details = addControl(L"EDIT", L"Capture a frame, then select a draw.",
        WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL, 0, 700, 42, 292, 166);

    state.diagnosticLabel = addLabel(L"Diagnostic", 700, 220, 292, 22);
    state.tint = addControl(L"EDIT", L"FF00FFFF", WS_BORDER | ES_AUTOHSCROLL,
        IdTint, 700, 246, 128, 24);
    state.suppress = addControl(L"BUTTON", L"Suppress selected draw", BS_AUTOCHECKBOX,
        IdSuppress, 838, 246, 154, 24);

    state.rectTranslateLabel = addLabel(L"Rectangle translate X / Y", 700, 284, 220, 22);
    state.rectTranslate[0] = addEdit(IdRectX, 700, 309);
    state.rectTranslate[1] = addEdit(IdRectY, 764, 309);
    state.rectEdgesLabel = addLabel(L"Rectangle edges L / T / R / B", 700, 343, 250, 22);
    for (int i = 0; i < 4; i++) state.rectEdges[i] = addEdit(IdRectL + i, 700 + i * 64, 368);

    state.scissorTranslateLabel = addLabel(L"Scissor translate X / Y", 700, 402, 220, 22);
    state.scissorTranslate[0] = addEdit(IdScissorX, 700, 427);
    state.scissorTranslate[1] = addEdit(IdScissorY, 764, 427);
    state.scissorEdgesLabel = addLabel(L"Scissor edges L / T / R / B", 700, 461, 250, 22);
    for (int i = 0; i < 4; i++) state.scissorEdges[i] = addEdit(IdScissorL + i, 700 + i * 64, 486);

    state.viewportEdgesLabel = addLabel(L"Orthographic viewport edges L / T / R / B", 700, 520, 292, 22);
    for (int i = 0; i < 4; i++) state.viewportEdges[i] = addEdit(IdViewportL + i, 700 + i * 64, 545);

    state.apply = addControl(L"BUTTON", L"Apply live", BS_DEFPUSHBUTTON, IdApply, 700, 589, 136, 34);
    state.clear = addControl(L"BUTTON", L"Clear selection", BS_PUSHBUTTON, IdClear, 846, 589, 146, 34);
    state.exportSelection = addControl(L"BUTTON", L"Submit report", BS_PUSHBUTTON,
        IdExport, 700, 589, 292, 34);
    state.footer = addLabel(L"Freeze game holds simulation while Composer changes automatically render one refresh frame. Hiding or closing Composer resumes automatically. Keyboard is routed here while open; XInput still controls the game. Ctrl+F10 hides/shows Composer.",
        700, 580, 292, 52);
}

void layoutControls(int clientWidth, int clientHeight) {
    constexpr int margin = 12;
    constexpr int gap = 12;
    const int rightWidth = std::clamp(clientWidth / 3, 310, 430);
    const int leftWidth = std::max(420, clientWidth - (margin * 2) - gap - rightWidth);
    const int rightX = margin + leftWidth + gap;
    const int captureWidth = 116;
    const int reloadWidth = 104;
    const int freezeWidth = 112;
    const int captureX = margin + leftWidth - captureWidth - reloadWidth - freezeWidth - 12;
    const int reloadX = captureX + captureWidth + 6;
    const int freezeX = reloadX + reloadWidth + 6;

    MoveWindow(state.header, margin, 10, std::max(160, captureX - margin - 8), 24, TRUE);
    MoveWindow(state.capture, captureX, 8, captureWidth, 28, TRUE);
    MoveWindow(state.reload, reloadX, 8, reloadWidth, 28, TRUE);
    MoveWindow(state.freeze, freezeX, 8, freezeWidth, 28, TRUE);
    const int sortWidth = std::clamp(leftWidth / 3, 180, 260);
    MoveWindow(state.summary, margin, 43, leftWidth, 22, TRUE);
    const int controlWidth = std::max(170, (leftWidth - 220) / 2);
    MoveWindow(state.sortLabel, margin, 71, 102, 22, TRUE);
    MoveWindow(state.sort, margin + 104, 68, controlWidth, 180, TRUE);
    const int filterX = margin + 116 + controlWidth;
    MoveWindow(state.filterLabel, filterX, 71, 92, 22, TRUE);
    MoveWindow(state.filter, filterX + 94, 68,
        std::max(170, margin + leftWidth - (filterX + 94)), 180, TRUE);
    MoveWindow(state.candidates, margin, 98, leftWidth, std::max(120, clientHeight - 110), TRUE);

    const int detailsHeight = std::max(100, clientHeight - 650);
    MoveWindow(state.details, rightX, 42, rightWidth, detailsHeight, TRUE);
    int y = 42 + detailsHeight + 12;
    MoveWindow(state.diagnosticLabel, rightX, y, rightWidth, 22, TRUE); y += 26;
    MoveWindow(state.tint, rightX, y, 128, 24, TRUE);
    MoveWindow(state.suppress, rightX + 138, y, std::max(150, rightWidth - 138), 24, TRUE); y += 38;
    MoveWindow(state.rectTranslateLabel, rightX, y, rightWidth, 22, TRUE); y += 25;
    MoveWindow(state.rectTranslate[0], rightX, y, 58, 24, TRUE);
    MoveWindow(state.rectTranslate[1], rightX + 64, y, 58, 24, TRUE); y += 34;
    MoveWindow(state.rectEdgesLabel, rightX, y, rightWidth, 22, TRUE); y += 25;
    for (int i = 0; i < 4; i++) MoveWindow(state.rectEdges[i], rightX + i * 64, y, 58, 24, TRUE);
    y += 34;
    MoveWindow(state.scissorTranslateLabel, rightX, y, rightWidth, 22, TRUE); y += 25;
    MoveWindow(state.scissorTranslate[0], rightX, y, 58, 24, TRUE);
    MoveWindow(state.scissorTranslate[1], rightX + 64, y, 58, 24, TRUE); y += 34;
    MoveWindow(state.scissorEdgesLabel, rightX, y, rightWidth, 22, TRUE); y += 25;
    for (int i = 0; i < 4; i++) MoveWindow(state.scissorEdges[i], rightX + i * 64, y, 58, 24, TRUE);
    y += 34;
    MoveWindow(state.viewportEdgesLabel, rightX, y, rightWidth, 22, TRUE); y += 25;
    for (int i = 0; i < 4; i++) MoveWindow(state.viewportEdges[i], rightX + i * 64, y, 58, 24, TRUE);
    y += 40;
    const int buttonGap = 8;
    const int buttonWidth = (rightWidth - (buttonGap * 2)) / 3;
    MoveWindow(state.apply, rightX, y, buttonWidth, 34, TRUE);
    MoveWindow(state.clear, rightX + buttonWidth + buttonGap, y, buttonWidth, 34, TRUE);
    MoveWindow(state.exportSelection, rightX + (buttonWidth + buttonGap) * 2, y,
        buttonWidth, 34, TRUE); y += 44;
    MoveWindow(state.footer, rightX, y, rightWidth, std::max(40, clientHeight - y - 8), TRUE);
}

LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if ((wparam == VK_F10) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) {
            ShowWindow(window, SW_HIDE);
            state.captureKeyboard.store(false, std::memory_order_release);
            if (state.gameWindow != nullptr) SetForegroundWindow(state.gameWindow);
            return 0;
        }
        break;
    case WM_CREATE:
        state.window = window;
        createControls();
        readProfile();
        loadControls();
        reloadCandidates();
        {
            RECT client{};
            GetClientRect(window, &client);
            layoutControls(client.right - client.left, client.bottom - client.top);
        }
        return 0;
    case WM_GETMINMAXINFO: {
        auto* limits = reinterpret_cast<MINMAXINFO*>(lparam);
        limits->ptMinTrackSize.x = 980;
        limits->ptMinTrackSize.y = 680;
        return 0;
    }
    case WM_SIZE:
        if (state.candidates != nullptr) {
            layoutControls(LOWORD(lparam), HIWORD(lparam));
        }
        return 0;
    case WM_SETFOCUS:
        state.captureKeyboard.store(true, std::memory_order_release);
        return 0;
    case WM_COMMAND: {
        const int id = LOWORD(wparam);
        const HWND sender = reinterpret_cast<HWND>(lparam);
        if ((id == IdCandidates) && (HIWORD(wparam) == LBN_SELCHANGE)) {
            applyCurrentSelection();
            return 0;
        }
        if ((id == IdSort) && (HIWORD(wparam) == CBN_SELCHANGE)) {
            const LRESULT selection = SendMessageW(state.sort, CB_GETCURSEL, 0, 0);
            state.sortMode = (selection >= 0) ? int(selection) : 0;
            refreshGroupList();
            setStatus("Layer arrangement changed. Stable L# identifiers are preserved across sorting modes.");
            return 0;
        }
        if ((id == IdFilter) && (HIWORD(wparam) == CBN_SELCHANGE)) {
            const LRESULT selection = SendMessageW(state.filter, CB_GETCURSEL, 0, 0);
            state.filterMode = (selection >= 0) ? int(selection) : 0;
            refreshGroupList();
            setStatus("Display filter changed. Hidden selected layers remain selected and highlighted magenta.");
            return 0;
        }
        if ((id == IdCapture) || ((sender != nullptr) && (sender == state.capture))) {
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[composer] Capture command received: id=%d notify=%u\n",
                id, unsigned(HIWORD(wparam))));
            readProfile();
            readControls();
            state.profile.captureId++;
            if (state.profile.captureId == 0) state.profile.captureId = 1;
            if (writeProfile()) {
                std::ostringstream status;
                status << "Capture " << state.profile.captureId
                    << " requested. Candidate list will refresh automatically.";
                setStatus(status.str());
                SetTimer(window, 1, 750, nullptr);
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[composer] Capture profile written: capture_id=%llu\n",
                    static_cast<unsigned long long>(state.profile.captureId)));
            }
            else {
                std::fprintf(stderr, "[composer] ERROR: capture profile write failed\n");
            }
            return 0;
        }
        if ((id == IdReload) || ((sender != nullptr) && (sender == state.reload))) {
            reloadCandidates();
            return 0;
        }
        if ((id == IdFreeze) || ((sender != nullptr) && (sender == state.freeze))) {
            setGameFrozen(!gameFrozen.load(std::memory_order_acquire));
            return 0;
        }
        if (id == IdApply) {
            applyProfile();
            return 0;
        }
        if (id == IdExport) {
            exportSelectionReport();
            return 0;
        }
        if (id == IdClear) {
            readControls();
            state.selectedGroups.clear();
            state.profile.signature = "0000000000000000";
            state.profile.signatures.clear();
            state.profile.suppress = false;
            writeProfile();
            loadControls();
            SendMessageW(state.candidates, LB_SETSEL, FALSE, static_cast<LPARAM>(-1));
            refreshGroupList();
            setStatus("Selection cleared. No draw is modified.");
            return 0;
        }
        break;
    }
    case WM_TIMER:
        if (wparam == 1) {
            KillTimer(window, 1);
            reloadCandidates();
            return 0;
        }
        break;
    case WM_CLOSE:
        setGameFrozen(false);
        ShowWindow(window, SW_HIDE);
        state.captureKeyboard.store(false, std::memory_order_release);
        return 0;
    case WM_DESTROY:
        setGameFrozen(false);
        state.captureKeyboard.store(false, std::memory_order_release);
        state.window = nullptr;
        return 0;
    default:
        break;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}

bool createComposerWindow() {
    WNDCLASSEXW windowClass{
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = windowProc,
        .hInstance = GetModuleHandleW(nullptr),
        .hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512)),
        .hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
        .lpszClassName = kClassName,
    };
    RegisterClassExW(&windowClass);

    RECT gameRect{};
    GetWindowRect(state.gameWindow, &gameRect);
    constexpr int windowWidth = 1020;
    constexpr int windowHeight = 760;
    MONITORINFO monitor{.cbSize = sizeof(MONITORINFO)};
    GetMonitorInfoW(MonitorFromWindow(state.gameWindow, MONITOR_DEFAULTTONEAREST), &monitor);
    int x = gameRect.right + 12;
    int y = gameRect.top;
    if ((x + windowWidth) > monitor.rcWork.right) x = monitor.rcWork.left + 32;
    if ((y + windowHeight) > monitor.rcWork.bottom) y = monitor.rcWork.bottom - windowHeight;
    x = std::max<int>(monitor.rcWork.left, x);
    y = std::max<int>(monitor.rcWork.top, y);
    state.window = CreateWindowExW(WS_EX_APPWINDOW, kClassName, kTitle,
        WS_OVERLAPPEDWINDOW, x, y, windowWidth, windowHeight, nullptr, nullptr,
        GetModuleHandleW(nullptr), nullptr);
    if (state.window == nullptr) {
        std::fprintf(stderr, "[composer] pop-out CreateWindowExW failed: %lu\n", GetLastError());
        return false;
    }
    state.captureKeyboard.store(false, std::memory_order_release);
    return true;
}

} // namespace

void initialize(void* game_window) {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    if (!state.profilePath.empty()) return;
    const char* configured = std::getenv("WR64_COMPOSER");
    if ((configured == nullptr) || (configured[0] == '\0') || (configured[0] == '0')) return;

    state.gameWindow = static_cast<HWND>(game_window);
    state.profilePath = std::filesystem::absolute((std::string(configured) == "1")
        ? std::filesystem::path("wr64-composer.cfg") : std::filesystem::path(configured));
    state.candidatePath = state.profilePath.parent_path() / "wr64-composer-candidates.csv";
    state.selectionPath = state.profilePath.parent_path() / "wr64-composer-selection.txt";
    state.captureKeyboard.store(false, std::memory_order_release);
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[composer] configured dormant; Ctrl+F10 creates and opens it, XInput unchanged\n"));
}

void update() {
    // Visibility and keyboard routing are event-driven by toggle(), focus,
    // close, and destroy. Do not poll the hidden HWND from the game loop.
}

void toggle() {
    if (state.profilePath.empty()) return;
    if ((state.window == nullptr) && !createComposerWindow()) return;
    const bool show = IsWindowVisible(state.window) == FALSE;
    if (!show) setGameFrozen(false);
    ShowWindow(state.window, show ? SW_SHOW : SW_HIDE);
    if (show) {
        SetForegroundWindow(state.window);
        reloadCandidates();
    }
    state.captureKeyboard.store(show, std::memory_order_release);
}

void shutdown() {
    setGameFrozen(false);
    state.captureKeyboard.store(false, std::memory_order_release);
    state.profile = Profile{};
    state.selectedGroups.clear();
    if (!state.profilePath.empty()) {
        writeProfile();
    }
    if (state.window != nullptr) DestroyWindow(state.window);
    if (state.font != nullptr) DeleteObject(state.font);
    state.font = nullptr;
}

bool keyboard_captured() {
    if (!WR64_DIAGNOSTIC_ENABLED) return false;
    return state.captureKeyboard.load(std::memory_order_acquire);
}

void wait_if_frozen() {
    if (!WR64_DIAGNOSTIC_ENABLED) return;
    static const uint64_t startupFreezeFrame = [] {
        const char* value = std::getenv("WR64_COMPOSER_FREEZE_FRAME");
        if ((value == nullptr) || (value[0] == '\0') || (value[0] == '0')) return uint64_t{0};
        char* end = nullptr;
        const unsigned long long parsed = std::strtoull(value, &end, 10);
        return ((end != value) && (*end == '\0')) ? uint64_t{parsed} : uint64_t{0};
    }();
    static bool startupFreezeTriggered = false;
    if (!startupFreezeTriggered && (startupFreezeFrame != 0) &&
        !gameFrozen.load(std::memory_order_acquire)) {
        const uint64_t currentFrame = RT64::WR64LayerTrace::composerLastNonzeroWorkloadFrame();
        if (currentFrame >= startupFreezeFrame) {
            startupFreezeTriggered = true;
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
                "[composer-freeze] startup trigger reached; requested=%llu current=%llu\n",
                static_cast<unsigned long long>(startupFreezeFrame),
                static_cast<unsigned long long>(currentFrame)));
            setGameFrozen(true);
        }
    }
    if (!gameFrozen.load(std::memory_order_acquire)) return;
    std::unique_lock lock(freezeMutex);
    while (gameFrozen.load(std::memory_order_acquire)) {
        if (renderRequestPending.load(std::memory_order_acquire)) {
            const uint64_t baseline = renderRequestBaseline.load(std::memory_order_acquire);
            const bool needsMatch = renderRequestNeedsMatch.load(std::memory_order_acquire);
            const uint64_t current = needsMatch
                ? RT64::WR64LayerTrace::composerLastMatchedWorkloadFrame()
                : RT64::WR64LayerTrace::composerLastNonzeroWorkloadFrame();
            if ((current != 0) && (current != baseline)) {
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
                    "[composer-freeze] workload refresh acknowledged; baseline=%llu current=%llu mode=%s; allowing presentation VI\n",
                    static_cast<unsigned long long>(baseline),
                    static_cast<unsigned long long>(current), needsMatch ? "matched" : "any"));
                renderRequestPending.store(false, std::memory_order_release);
                renderRequestNeedsMatch.store(false, std::memory_order_release);
                renderRequestBudget.store(0, std::memory_order_release);
                // Return once after acknowledgement. The next VI iteration queues
                // presentation of the newly rendered/highlighted workload, then
                // blocks again when it reaches this callback.
                return;
            }
            else {
                const uint32_t remaining = renderRequestBudget.load(std::memory_order_acquire);
                if (remaining > 0) {
                    renderRequestBudget.store(remaining - 1, std::memory_order_release);
                    return;
                }
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
                    "[composer-freeze] workload refresh timed out; baseline=%llu current=%llu\n",
                    static_cast<unsigned long long>(baseline),
                    static_cast<unsigned long long>(current)));
                renderRequestPending.store(false, std::memory_order_release);
                renderRequestNeedsMatch.store(false, std::memory_order_release);
            }
        }

        freezeCondition.wait(lock, [] {
            return !gameFrozen.load(std::memory_order_acquire) ||
                renderRequestPending.load(std::memory_order_acquire);
        });
    }
}

} // namespace wr64::composer

#else

namespace wr64::composer {
void initialize(void*) {}
void update() {}
void toggle() {}
void shutdown() {}
bool keyboard_captured() { return false; }
void wait_if_frozen() {}
}

#endif
