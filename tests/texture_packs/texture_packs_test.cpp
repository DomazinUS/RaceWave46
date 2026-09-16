// Generated harness compiles actual production functions; RT64 GPU operations
// are recorded so ordering, callbacks, persistence, and idle work can be checked.
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#include "concurrentqueue.h"
#include "overloaded.h"

namespace recomp::config {
enum class ConfigOptionType { Enum, Bool, String };
struct ConfigOptionEnum { std::vector<std::string> options; };
struct ConfigOption {
    std::string id;
    ConfigOptionType type;
    std::variant<ConfigOptionEnum> variant;
};
using ConfigValueVariant = std::variant<uint32_t, bool>;
struct ConfigSchema {
    std::unordered_map<std::string, size_t> options_by_id;
    std::vector<ConfigOption> options;
};
}

namespace recomp::mods {
struct ModContext {
    config::ConfigSchema schema;
    config::ConfigValueVariant value = false;
    const config::ConfigSchema& get_mod_config_schema(const std::string&) const { return schema; }
    config::ConfigValueVariant get_mod_config_value(const std::string&, const std::string&) const { return value; }
};
struct ModHandle { struct { std::string mod_id; } manifest; };
struct ModContentType {
    std::string content_filename;
    bool allow_runtime_toggle;
    void (*on_enabled)(ModContext&, const ModHandle&);
    void (*on_disabled)(ModContext&, const ModHandle&);
    void (*on_reordered)(ModContext&);
};
struct ModContentTypeId { size_t value; };
std::vector<ModContentType> registered_types;
struct Container { std::string extension; std::vector<ModContentTypeId> types; bool requires_manifest; };
std::vector<Container> registered_containers;
ModContentTypeId register_mod_content_type(const ModContentType& type) {
    registered_types.push_back(type);
    return {registered_types.size() - 1};
}
bool register_mod_container_type(const std::string& extension, const std::vector<ModContentTypeId>& types, bool manifest) {
    assert(extension.find('.') == std::string::npos);
    registered_containers.push_back({extension, types, manifest});
    return true;
}
std::unordered_map<std::string, size_t> order{{"a", 0}, {"b", 1}};
size_t lookups = 0;
size_t get_mod_order_index(const std::string& id) { ++lookups; return order.at(id); }
std::filesystem::path get_mod_filename(const std::string& id) { ++lookups; return id + ".rtz"; }
}

namespace RT64 {
struct ReplacementDirectory {
    std::filesystem::path path;
    ReplacementDirectory(const std::filesystem::path& path) : path(path) {}
};
struct TextureCache {
    bool waited = false;
    size_t waits = 0;
    size_t loads = 0;
    size_t clears = 0;
    std::vector<std::filesystem::path> paths;
    void waitForGPUUploads() { waited = true; ++waits; }
    bool loadReplacementDirectories(const std::vector<ReplacementDirectory>& directories) {
        assert(waited);
        waited = false;
        ++loads;
        paths.clear();
        for (const auto& directory : directories) paths.push_back(directory.path);
        return true;
    }
    void clearReplacementDirectories() {
        assert(waited);
        waited = false;
        ++clears;
        paths.clear();
    }
};
struct Application { std::unique_ptr<TextureCache> textureCache = std::make_unique<TextureCache>(); };
}

namespace recompui {
void message_box(const char*) { assert(false && "Unexpected config validation error"); }
namespace renderer {
inline const std::string special_option_texture_pack_enabled = "_recomp_texture_pack_enabled";
// PRODUCTION_STATE
void check_texture_pack_actions(RT64::Application&, TexturePackState&, bool force_reload = false);
void trigger_texture_pack_update();
void enable_texture_pack(const recomp::mods::ModContext&, const recomp::mods::ModHandle&);
void disable_texture_pack(const recomp::mods::ModHandle&);
void secondary_enable_texture_pack(const std::string&);
void secondary_disable_texture_pack(const std::string&);
bool is_texture_pack_enable_config_option(const recomp::config::ConfigOption&, bool);
}
}
using namespace recompui;

// PRODUCTION_IMPLEMENTATION

int main() {
    using namespace recomp::mods;
    using namespace recompui::renderer;
    wr64::texture_packs::register_mod_types();
    wr64::texture_packs::register_mod_types();
    assert(registered_types.size() == 1 && registered_containers.size() == 1);
    const auto& content = registered_types.front();
    const auto& container = registered_containers.front();
    assert(content.content_filename == "rt64.json" && content.allow_runtime_toggle);
    assert(container.extension == "rtz" && !container.requires_manifest);
    assert(container.types.size() == 1 && container.types.front().value == 0);

    ModContext context;
    ModHandle a{{"a"}}, b{{"b"}};
    TexturePackState state;
    RT64::Application first;
    content.on_enabled(context, a);
    content.on_enabled(context, b);
    assert(first.textureCache->loads == 0); // Callbacks must not access GPU state.
    check_texture_pack_actions(first, state);
    assert((first.textureCache->paths == std::vector<std::filesystem::path>{"b.rtz", "a.rtz"}));

    const auto idle_lookups = lookups;
    const auto idle_waits = first.textureCache->waits;
    for (int i = 0; i < 100; ++i) check_texture_pack_actions(first, state);
    assert(lookups == idle_lookups && first.textureCache->waits == idle_waits);

    order["a"] = 1;
    order["b"] = 0;
    content.on_reordered(context);
    check_texture_pack_actions(first, state);
    assert((first.textureCache->paths == std::vector<std::filesystem::path>{"a.rtz", "b.rtz"}));

    secondary_disable_texture_pack("a");
    check_texture_pack_actions(first, state);
    assert((first.textureCache->paths == std::vector<std::filesystem::path>{"b.rtz"}));
    RT64::Application rebuilt;
    check_texture_pack_actions(rebuilt, state, true);
    assert(rebuilt.textureCache->paths == first.textureCache->paths);
    assert(rebuilt.textureCache->loads == 1); // No queued action needed after API rebuild.

    secondary_enable_texture_pack("a");
    check_texture_pack_actions(rebuilt, state);
    content.on_disabled(context, a);
    content.on_disabled(context, b);
    check_texture_pack_actions(rebuilt, state);
    assert(rebuilt.textureCache->paths.empty() && rebuilt.textureCache->clears == 1);
    content.on_enabled(context, a);
    check_texture_pack_actions(rebuilt, state);
    assert((rebuilt.textureCache->paths == std::vector<std::filesystem::path>{"a.rtz"}));

    // The real enable callback reads the special option; false starts disabled.
    content.on_disabled(context, a);
    context.schema.options_by_id[special_option_texture_pack_enabled] = 0;
    context.schema.options.push_back({special_option_texture_pack_enabled, recomp::config::ConfigOptionType::Bool, {}});
    context.value = false;
    content.on_enabled(context, a);
    check_texture_pack_actions(rebuilt, state);
    assert(rebuilt.textureCache->paths.empty());
    secondary_enable_texture_pack("a"); // Same entry point as native mod details UI.
    check_texture_pack_actions(rebuilt, state);
    assert((rebuilt.textureCache->paths == std::vector<std::filesystem::path>{"a.rtz"}));
    context.schema.options.front().type = recomp::config::ConfigOptionType::Enum;
    context.schema.options.front().variant = recomp::config::ConfigOptionEnum{{"Off", "On"}};
    context.value = uint32_t{1};
    content.on_disabled(context, a);
    content.on_enabled(context, a);
    check_texture_pack_actions(rebuilt, state);
    assert((rebuilt.textureCache->paths == std::vector<std::filesystem::path>{"a.rtz"}));
    puts("PASS: RTZ registration, deferred callbacks, toggle, priority, special option, idle cost, renderer recreation");
}
