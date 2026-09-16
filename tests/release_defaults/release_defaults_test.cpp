#include "wr64_editions.hpp"
#include "wr64_graphics_config.hpp"
#include "librecomp/config.hpp"
#include "librecomp/game.hpp"
#include "common/rt64_wr64_ultrawide.h"
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

float parse_experimental_3d_aspect();
std::optional<int> wr64_presentation_rate_override();
RT64::UserConfiguration::GraphicsAPI wr64_requested_graphics_api(RT64::UserConfiguration::GraphicsAPI);
void apply_presentation_override(RT64::UserConfiguration&);
double initialWaveRoundnessPercent();
ultramodern::renderer::GraphicsConfig registered_graphics_defaults();
bool registered_gameplay_rumble_default();
bool registered_show_ghost_default();
void registered_hud_schema(recomp::config::Config&);
void registered_graphics_schema(recomp::config::Config&);
void registered_general_schema(recomp::config::Config&);
void registered_sound_schema(recomp::config::Config&);
std::array<float,3> released_workload_aspect(uint32_t,uint32_t,
    RT64::UserConfiguration::AspectRatio,RT64::UserConfiguration::AspectRatio,float);

namespace {
namespace fs=std::filesystem;
unsigned assertions=0;
fs::path profile_directory;
void require(bool value,const char* message) {
    ++assertions;
    if(!value) throw std::runtime_error(message);
}
void close(float actual,float expected,const char* message) {
    require(std::abs(actual-expected)<0.0005f,message);
}
std::string utf8(const fs::path& path) {
    const auto bytes=path.u8string();
    return {reinterpret_cast<const char*>(bytes.data()),bytes.size()};
}
wr64::editions::Options parse(std::vector<std::string> values,const fs::path& runtime={}) {
    std::vector<char*> arguments;
    for(auto& value:values) arguments.push_back(value.data());
    return wr64::editions::parse_options(int(arguments.size()),arguments.data(),runtime);
}
void startup_contract(int argc,char** argv) {
    const fs::path original=fs::current_path();
    const fs::path executable=fs::absolute(argv[0]);
    const auto identity=std::chrono::steady_clock::now().time_since_epoch().count();
    const auto isolated=executable.parent_path()/("isolated-release-"+std::to_string(identity));
    const auto package=isolated/fs::path(u8"Portable package 日本語");
    const auto foreign=isolated/fs::path(u8"Foreign cwd Espaço");
    fs::create_directories(package);
    fs::create_directories(foreign);
    try {
        for(const auto& directory:{package,foreign}) {
            fs::current_path(directory);
            const auto fallback=parse({"WaveRace64Recompiled.exe"});
            require(fallback.runtime==directory/".runtime","Generic parse fallback stopped using caller CWD");
            require(!fallback.launcher && !fallback.launch && !fallback.windowed && fallback.seconds==0 && fallback.rom.empty(),
                "No arguments must open the USA frontend without starting gameplay or a diagnostic run");
            const auto supplied=parse({"WaveRace64Recompiled.exe"},package/".runtime");
            require(supplied.runtime==package/".runtime" && !supplied.launcher,"Portable default profile followed foreign CWD");
            const auto process=wr64::editions::parse_process_options(argc,argv);
            require(process.runtime==executable.parent_path()/".runtime" && !process.launcher && !process.launch,
                "Actual Windows process parsing did not anchor the USA profile beside its executable");
            const auto relative=fs::path(u8"User profiles 日本語")/"profile";
            const auto rom=fs::path(u8"ROM files Espaço")/"Wave Race.z64";
            const auto explicitOptions=parse({"WaveRace64Recompiled.exe","--runtime-dir",utf8(relative),"--rom",utf8(rom)},package/".runtime");
            require(explicitOptions.runtime==directory/relative,"Explicit relative runtime no longer resolves from caller CWD");
            require(explicitOptions.rom==rom,"Explicit ROM path or Unicode bytes changed");
            require(!explicitOptions.launcher && !explicitOptions.launch,"Supplying paths unexpectedly launched a game");
            const auto normalCore=parse({"WaveRace64Recompiled.exe","--core"},package/".runtime");
            require(!normalCore.launcher && !normalCore.launch && normalCore.seconds==0,
                "Legacy --core compatibility must retain the USA frontend until Start Race is selected");
            const auto core=parse({"WaveRace64Recompiled.exe","--core","--launch","--runtime-dir",utf8(package/"usa"),"--rom",utf8(package/rom)},package/".runtime");
            require(!core.launcher && core.launch && core.runtime==package/"usa" && core.rom==package/rom && core.seconds==0,
                "Explicit USA launch arguments lost their requested profile or entered timed diagnostic mode");
            const auto legacy=parse({"WaveRace64Recompiled.exe",utf8(rom),"2"},package/".runtime");
            require(!legacy.launcher && legacy.launch && legacy.seconds==2 && legacy.rom==rom,
                "Existing positional diagnostic launch compatibility changed");
            require(fs::current_path()==directory,"Options parsing changed caller CWD");
            require(!fs::exists(package/".runtime") && !fs::exists(directory/relative),
                "Options parsing wrote profiles before runtime initialization");
        }
        for(const auto& arguments:std::vector<std::vector<std::string>>{
            {"exe","--runtime-dir"},{"exe","--rom"},{"exe","--seconds","-1"},
            {"exe","--seconds","60junk"},{"exe","--unexpected"},
            {"exe","--launcher"},{"exe","--language","ja"},{"exe","--language","en"},
            {"exe","--edition","shindou"}}) {
            bool rejected=false;
            try {parse(arguments,package/".runtime");} catch(const std::runtime_error&) {rejected=true;}
            require(rejected,"Invalid startup arguments bypassed validation");
        }
        fs::current_path(original);
    } catch(...) {fs::current_path(original);throw;}
}
void defaults_contract() {
    for(const char* name:{"WR64_EXPERIMENTAL_3D_ASPECT","WR64_GRAPHICS_API","WR64_FORCE_PRESENTATION_HZ",
        "WR64_FORCE_PRESENTATION_20HZ","WR64_WATER_LAPLACIAN_STRENGTH","WR64_WATERCRAFT_PREVIEW",
        "WR64_CHANGE_NAME_PREVIEW","WR64_COURSE_PREVIEW","WR64_CHAMPIONSHIP_PREVIEW"})
        require(std::getenv(name)==nullptr,"Test runner must remove overrides, rather than forcing feature values");
    close(parse_experimental_3d_aspect(),0,"Normal startup unexpectedly locks a diagnostic aspect ratio");
    require(!wr64_presentation_rate_override(),"Normal startup unexpectedly forces a diagnostic framerate");
    require(initialWaveRoundnessPercent()==50.0,"Fresh-profile Wave Roundness lost accepted 50% default");
    require(registered_gameplay_rumble_default() && registered_show_ghost_default(),
        "Fresh General defaults must enable gameplay rumble and ghost visibility");
    using Native=RT64::UserConfiguration;
    using namespace ultramodern::renderer;
    const auto defaults=registered_graphics_defaults();
    require(defaults.res_option==Resolution::Auto && defaults.ar_option==AspectRatio::Expand &&
        defaults.rr_option==RefreshRate::Display && defaults.api_option==GraphicsApi::D3D12,
        "Fresh graphics profile lost automatic resolution, aspect, display cadence or D3D12 defaults");
    require(defaults.hr_option==HUDRatioMode::Full,"Fresh USA HUD must use accepted expanded placement");
    require(defaults.wm_option==WindowMode::Fullscreen && defaults.msaa_option==Antialiasing::None &&
        defaults.ds_option==4 && defaults.rr_manual_value==90 &&
        defaults.hpfb_option==HighPrecisionFramebuffer::Off && !defaults.developer_mode,
        "Fresh graphics defaults must retain fullscreen, no MSAA, 4x downsampling and accepted hidden settings");
    Native config;
    wr64::renderer::apply_startup_graphics_config(config,defaults);
    const auto previous=config;
    apply_presentation_override(config);
    require(config.aspectRatio==Native::AspectRatio::Expand && config.resolution==Native::Resolution::WindowIntegerScale &&
        config.refreshRate==Native::RefreshRate::Display,"Normal frontend defaults did not reach actual renderer startup mapping");
    require(config.antialiasing==Native::Antialiasing::None &&
        config.internalColorFormat==Native::InternalColorFormat::Standard &&
        config.refreshRateTarget==90 && config.downsampleMultiplier==1 && !config.developerMode,
        "Startup mapping lost saved quality defaults or applied downsampling to Auto resolution");
    require(config.refreshRate==previous.refreshRate && config.refreshRateTarget==previous.refreshRateTarget,
        "No-env presentation path changed saved/default cadence");
    for(const auto api:{Native::GraphicsAPI::Automatic,Native::GraphicsAPI::D3D12,Native::GraphicsAPI::Vulkan})
        require(wr64_requested_graphics_api(api)==api,"No-env API path ignored saved selection");
    for(const auto dimensions:{std::array<uint32_t,2>{1280,720},{1260,540},{3440,1440},{1920,540},{800,600},{2560,540},{0,0}}) {
        const float actualAspect=dimensions[1]?float(dimensions[0])/float(dimensions[1]):16.0f/9.0f;
        const float expected=std::clamp(actualAspect,16.0f/9.0f,32.0f/9.0f);
        const auto automatic=released_workload_aspect(dimensions[0],dimensions[1],config.aspectRatio,config.extAspectRatio,float(config.extAspectTarget));
        close(automatic[0],expected,"Normal workload did not derive world aspect from current window dimensions");
        close(automatic[1],(424.0f/240.0f)*expected/(16.0f/9.0f),"Automatic expansion changed the established 424-pixel IPS baseline");
        close(automatic[2],1,"Fresh USA HUD did not follow expanded scene edges");
        close(RT64::wr64UltrawideLogicalWidth(),424.0f*expected/(16.0f/9.0f),"Automatic aspect did not publish the matching CPU sun/HUD coordinate plane");
        const auto original=released_workload_aspect(dimensions[0],dimensions[1],Native::AspectRatio::Original,Native::AspectRatio::Original,0);
        close(original[0],16.0f/9.0f,"Saved Original aspect should retain native USA 16:9");
        close(original[2],0,"Original HUD unexpectedly moved to expanded edges");
    }
}
void saved_hud_contract() {
    using namespace ultramodern::renderer;
    using Native=RT64::UserConfiguration;
    profile_directory=fs::current_path()/("isolated-hud-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    recomp::config::Config config("Graphics","graphics",true);
    registered_hud_schema(config);
    config.set_config_directory(profile_directory/"fresh");
    require(config.load_config(),"Fresh actual runtime Config could not initialize its HUD default");
    require(std::get<uint32_t>(config.get_option_value("hr_option"))==uint32_t(HUDRatioMode::Full),
        "Actual missing profile did not initialize the new expanded HUD default");
    const std::array<std::pair<const char*,HUDRatioMode>,3> saved{{
        {"Clamp16x9",HUDRatioMode::Clamp16x9},{"Original",HUDRatioMode::Original},{"Expand",HUDRatioMode::Full}}};
    for(const auto& [value,expected]:saved) {
        const auto directory=profile_directory/value;
        fs::create_directories(directory);
        const nlohmann::json original{{"hr_option",value},{"unrelated_saved",73}};
        {std::ofstream file(directory/"graphics.json");file<<original.dump();}
        config.set_config_directory(directory);
        require(config.load_config(),"Existing actual runtime Config could not reload its saved HUD choice");
        require(std::get<uint32_t>(config.get_option_value("hr_option"))==uint32_t(expected),
            "Fresh expanded default overwrote an existing saved HUD choice");
        auto graphics=registered_graphics_defaults();graphics.hr_option=expected;
        Native renderer;
        wr64::renderer::apply_startup_graphics_config(renderer,graphics);
        require(renderer.extAspectRatio==(expected==HUDRatioMode::Full?Native::AspectRatio::Expand:
            expected==HUDRatioMode::Clamp16x9?Native::AspectRatio::Manual:Native::AspectRatio::Original),
            "Saved HUD choice failed to reach the renderer");
        nlohmann::json after;
        {std::ifstream file(directory/"graphics.json");file>>after;}
        require(after==original,"HUD default initialization rewrote existing or unknown profile settings");
    }
}

void profile_defaults_contract() {
    using nlohmann::json;
    profile_directory=fs::current_path()/("isolated-settings-"+
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto check_profile=[&](const char* id, bool confirmation,
        void (*schema)(recomp::config::Config&), const json& expected, const json& saved) {
        recomp::config::Config config(id,id,confirmation);
        schema(config);
        config.set_config_directory(profile_directory/id/"fresh");
        require(config.load_config(),"Fresh profile failed to load its production defaults");
        require(config.get_json_config()==expected,"Fresh profile differs from accepted canary settings");
        if(std::string(id)=="general") {
            const auto& options=config.get_config_schema();
            require(options.options.at(options.options_by_id.at("rumble_strength")).description==
                options.options.at(options.options_by_id.at("rumble_strength_p2")).description,
                "Player 2 Rumble Strength description differs from Player 1");
        }
        for(const auto& [name,original]:std::array<std::pair<const char*,json>,2>{{
            {"saved",saved},{"partial",json{{"unrelated_saved",73}}}}}) {
            const auto directory=profile_directory/id/name;
            fs::create_directories(directory);
            {std::ofstream file(directory/(std::string(id)+".json"));file<<original.dump();}
            config.set_config_directory(directory);
            require(config.load_config(),"Existing profile could not load");
            auto merged=expected;
            merged.update(original);
            if(config.get_json_config()!=merged) {
                std::cerr<<id<<'/'<<name<<" expected "<<merged.dump()<<" got "<<config.get_json_config().dump()<<'\n';
            }
            require(config.get_json_config()==merged,"Defaults replaced saved settings or missing values used stale defaults");
            json after;
            {std::ifstream file(directory/(std::string(id)+".json"));file>>after;}
            require(after==original,"Loading new defaults rewrote an existing profile");
        }
    };
    check_profile("general",false,registered_general_schema,
        {{"background_input_mode","On"},{"debug_mode",false},{"gameplay_rumble",true},
         {"joystick_deadzone",5},{"rumble_strength",25},{"rumble_strength_p2",25},{"show_ghost",true}},
        {{"background_input_mode","Off"},{"debug_mode",false},{"gameplay_rumble",false},
         {"joystick_deadzone",12},{"rumble_strength",0},{"rumble_strength_p2",65},
         {"show_ghost",false},{"unrelated_saved",73}});
    check_profile("graphics",true,registered_graphics_schema,
        {{"api_option","D3D12"},{"ar_option","Expand"},{"developer_mode",false},
         {"ds_option",4},{"hpfb_option","Off"},{"hr_option","Expand"},{"msaa_option","None"},
         {"res_option","Auto"},{"rr_manual_value",90},{"rr_option","Display"},{"wm_option","Fullscreen"}},
        {{"api_option","Vulkan"},{"ar_option","Original"},{"developer_mode",false},
         {"ds_option",0},{"hpfb_option","Off"},{"hr_option","Original"},{"msaa_option","None"},
         {"res_option","1080p"},{"rr_manual_value",90},{"rr_option","Manual"},
         {"wm_option","Windowed"},{"unrelated_saved",73}});
    check_profile("sound",false,registered_sound_schema,{{"main_volume",100}},
        {{"main_volume",35},{"unrelated_saved",73}});

    // The custom numeric downsampling parser must retain every valid saved
    // choice while using the accepted default for missing or invalid values.
    recomp::config::Config graphics("Graphics","graphics",true);
    registered_graphics_schema(graphics);
    for(const auto& [value,expected]:std::array<std::pair<json,uint32_t>,5>{{
        {0,0},{2,2},{4,4},{nullptr,4},{3,4}}}) {
        const auto directory=profile_directory/("downsampling-"+value.dump());
        fs::create_directories(directory);
        {std::ofstream file(directory/"graphics.json");file<<json{{"ds_option",value}}.dump();}
        graphics.set_config_directory(directory);
        require(graphics.load_config(),"Downsampling fixture could not load");
        require(std::get<uint32_t>(graphics.get_option_value("ds_option"))==expected,
            "Downsampling parser lost an explicit saved choice or the new fallback default");
    }
}
}
namespace recomp {
std::filesystem::path get_config_path(){return profile_directory;}
const Version& get_project_version(){static const Version version;return version;}
}
int main(int argc,char** argv) {
    try {
        startup_contract(argc,argv);
        defaults_contract();
        saved_hud_contract();
        profile_defaults_contract();
        std::cout<<"Passed "<<assertions<<" no-override release startup/default/automatic-aspect assertions.\n";
    } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
