#include "wr64_ghost.hpp"
#include "wr64_controller_pak.hpp"
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace ultramodern {
std::filesystem::path get_save_file_path() { return {}; }
}
namespace {
using namespace wr64::ghost;
using Pak = wr64::controller_pak::Store;
using PakResult = wr64::controller_pak::Result;
int checks = 0;
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
Frame frame(Course course = {1,0,false}) {
    Frame f; f.course=course; f.eligible=true; return f;
}
void record(Course course, std::uint32_t time, int points=10) {
    begin_run(course);
    auto f=frame(course);
    for(int i=0;i<points;++i) { f.position={float(i),2.5f,float(i*2)};observe(f); }
    f.finished=true;f.elapsed_ms=time;observe(f);
}
void lifecycle() {
    reset_session(); set_visible(true);
    require(save_slot(0)==Result::NoGhost,"unfinished run must not save");
    auto f=frame(); begin_run(f.course);
    f.paused=true;observe(f);
    require(status().recorded_samples==0,"pause cannot capture");
    f.paused=false;f.position={-101.5f,-2.5f,3.5f};observe(f);
    f.finished=true;f.elapsed_ms=123457;observe(f);
    require(status().best.finish_ms==123457,"finish time must retain sub-tick residual");
    require(status().best.samples==2,"finish sample must be captured after goal count");
    begin_run(f.course);f.finished=false;f.elapsed_ms=0;observe(f);
    auto p=render_pose();
    require(p.valid && p.position.x==-2 && p.position.y==-3 && p.position.z==4,"signed rounding and side slide");
    f.paused=true;observe(f);require(render_pose().sample_index==0,"pause cannot advance playback");
    f.paused=false;set_visible(false);observe(f);
    require(!render_pose().valid && status().playback_active,"hidden ghost must advance");
    set_visible(true);require(render_pose().sample_index==1,"hidden cursor advanced");
    const auto end_animation=render_pose().animation_frame;observe(f);
    require(render_pose().valid && render_pose().sample_index==1 &&
        render_pose().animation_frame==(end_animation+2)%16,"playback holds last pose and continues swimming");
    record(f.course,130000);require(status().best.finish_ms==123457,"slower run cannot replace best");
    record(f.course,123457);require(status().best.samples==2,"equal run cannot replace best");
    record(f.course,120001);require(status().best.finish_ms==120001,"faster run replaces best");
    record({2,1,true},150001);require(status().best.course==Course{2,1,true},"different course replaces RAM selection");
    begin_run({1,0,false});observe(frame());require(!render_pose().valid,"mismatched course cannot play");
    reset_session();begin_run(f.course);f=frame();f.retired=true;observe(f);
    f.retired=false;f.finished=true;f.elapsed_ms=1000;observe(f);
    require(!status().can_save,"retired run cannot become ghost");
    reset_session();begin_run(f.course);f=frame();
    for(unsigned i=0;i<kMaxSamples;++i) observe(f);
    f.finished=true;f.elapsed_ms=127850;observe(f);
    require(status().recorded_samples==kMaxSamples && !status().can_save,"full pre-goal trajectory cannot save");
    reset_session();begin_run(f.course);f=frame();f.position.x=std::numeric_limits<float>::infinity();observe(f);
    require(status().recording_invalid && !status().recording,"nonfinite coordinate invalidates capture");
    reset_session();begin_run(f.course);f=frame();f.position.x=32767;observe(f);
    require(status().recording_invalid,"slide overflow must not wrap signed coordinates");
    reset_session();begin_run(f.course);f=frame();observe(f);f.eligible=false;observe(f);
    require(!status().recording && !render_pose().valid,"non-race state ends capture/display");
}
void persistence() {
    reset_session();record({1,0,false},123457);
    require(save_slot(0)==Result::Ok,"save first slot");
    auto& pak=Pak::instance();std::int32_t free=0;
    require(pak.free_blocks(0,free)==PakResult::Ok && free==512,"two-slot container must consume exactly121 pages");
    record({8,2,true},111111);
    require(save_slot(1)==Result::Ok,"save independent second slot");
    require(status().slots[0].finish_ms==123457 && status().slots[1].finish_ms==111111,"slot metadata isolation");
    pak.reset_for_tests();reset_session();
    require(refresh_slots()==Result::Ok && status().slots[0].finish_ms==123457,"disk reload after Store reset");
    require(load_slot(1)==Result::Ok && status().best.course==Course{8,2,true},"disk trajectory selection");
    begin_run({8,2,true});observe(frame({8,2,true}));
    require(render_pose().valid && render_pose().position.x==100,"saved trajectory decodes and plays");
    require(load_slot(0)==Result::Ok,"load another slot during race");
    observe(frame({8,2,true}));require(render_pose().sample_index==1,"loading must not teleport active playback");
    require(save_slot(0)==Result::WouldOverwriteBetter,"equal saved time requires explicit overwrite");
    require(save_slot(0,true)==Result::Ok,"confirmed overwrite");
    require(clear_slot(1)==Result::Ok && !status().slots[1].available && status().slots[0].available,"clear one slot preserves other");
    require(load_slot(1)==Result::NoGhost && load_slot(2)==Result::InvalidSlot,"empty and invalid slots");
    wr64::controller_pak::Key records;records.game_code=0x4E575245;records.game_name[0]='R';int record_file=-1;
    require(pak.allocate_file(0,records,512,record_file)==PakResult::Ok,"normal records still fit alongside ghost");
    require(pak.free_blocks(0,free)==PakResult::Ok && free==0,"Pak full only after records allocation");
    wr64::controller_pak::FileState fs;int ghost_file=-1;
    for(int i=0;i<16;++i) if(pak.file_state(0,i,fs)==PakResult::Ok && fs.file_size==kFileBytes)ghost_file=i;
    require(ghost_file>=0,"find stored container");
    std::vector<std::uint8_t> bytes(kFileBytes);
    require(pak.read_file(0,ghost_file,0,bytes)==PakResult::Ok,"read container for corruption test");
    bytes[280]^=0x80;
    require(pak.write_file(0,ghost_file,0,bytes)==PakResult::Ok,"inject checksum corruption in isolated Pak");
    require(refresh_slots()==Result::CorruptData && load_slot(0)==Result::CorruptData,"reject damaged payload");
    require(save_slot(0,true)==Result::CorruptData,"save cannot silently erase corrupted other slot");
}
void export_synthetic_fixture(const std::filesystem::path& supplied_base) {
    auto normalized_base=supplied_base;
#if defined(__CYGWIN__) || defined(__MSYS__)
    // The standalone utility can be built with MSYS CMake. Accept a Windows
    // absolute command-line path without creating a literal "D:" component.
    auto spelling=supplied_base.string();
    if(spelling.size()>=3 && spelling[1]==':' &&
       ((spelling[0]>='A' && spelling[0]<='Z') || (spelling[0]>='a' && spelling[0]<='z')) &&
       (spelling[2]=='/' || spelling[2]=='\\')) {
        const char drive=spelling[0]>='A' && spelling[0]<='Z' ? spelling[0]+('a'-'A') : spelling[0];
        for(auto& c:spelling)if(c=='\\')c='/';
        normalized_base=std::string("/")+drive+spelling.substr(2);
    }
#endif
    const auto base=std::filesystem::absolute(normalized_base).lexically_normal();
    const auto directory=base.parent_path();
    if(base.filename().empty() || base.filename()=="." || base.filename()=="..")
        throw std::runtime_error("fixture requires an explicit save-base filename");
    // A fresh containing directory is stronger than checking the Pak filename:
    // it also protects EEPROM, backups, sidecars, and other existing profiles.
    if(std::filesystem::exists(directory))
        throw std::runtime_error("fixture destination directory already exists; refusing to overwrite or reuse it");
    std::filesystem::create_directories(directory.parent_path());
    if(!std::filesystem::create_directory(directory))
        throw std::runtime_error("could not claim a fresh fixture directory");
    std::ofstream label(directory/"SYNTHETIC-GHOST-FIXTURE.txt");
    label<<"SYNTHETIC TEST FIXTURE - NOT A COMPLETED HUMAN RACE\n"
        <<"Sunny Beach / Normal / Forward; slot0 (frontend Slot1); time1:00.001.\n"
        <<"Generated by the isolated ghost test utility through production observe/save APIs.\n"
        <<"A small synthetic oval near the USA starting grid tests disk Load -> native playback.\n"
        <<"It does not prove race completion or authenticity of a recorded lap.\n"
        <<"Grid evidence: USA ROM0x2A9F78 record0=(-1790,780,3,90);\n"
        <<"func8006AC84 one-rider grid uses goal minus512*forward, yielding(-2302,0,780), forward+X.\n"
        <<"The fixture adds its own visible height and oval; no ROM asset or game code is exported.\n"
        <<"Save base: "<<base<<'\n';
    label.close();
    require(bool(label),"write explicit synthetic-fixture label");
    Pak::instance().set_base_save_path_for_tests(base);
    reset_session();set_visible(true);begin_run({1,0,false});
    auto f=frame();f.forward={1,0,0};f.up={0,1,0};f.left={0,0,-1};
    constexpr unsigned goal_count=1200;
    constexpr float tau=6.28318530718f;
    for(unsigned i=0;i<=goal_count;++i) {
        const float phase=float(i)*tau/240.0f;
        f.position={-2302.0f+180.0f+120.0f*std::sin(phase),
            35.0f+10.0f*std::sin(2*phase),780.0f-80.0f+60.0f*(1-std::cos(phase))};
        f.elapsed_ms=i*50;
        if(i==goal_count) {f.finished=true;f.elapsed_ms=60001;}
        observe(f);
    }
    end_run();
    require(status().can_save && status().best.samples==1201,"synthetic fixture is a valid completed host record");
    require(save_slot(0)==Result::Ok,"save synthetic fixture using production Store and ghost APIs");
    Pak::instance().reset_for_tests();reset_session();
    require(refresh_slots()==Result::Ok && status().slots[0].available && !status().slots[1].available,
        "fixture reload has exactly one persisted ghost slot");
    require(load_slot(0)==Result::Ok,"fixture loads through production decoder");
    begin_run({1,0,false});observe(frame());
    const auto pose=render_pose();
    require(pose.valid && pose.position.x==-2122 && pose.position.y==35 && pose.position.z==600,
        "fixture starts beside the source-derived USA Sunny grid");
    auto pak=base;pak.replace_extension();pak+=".controller-pak-1.bin";
    std::cout<<"SYNTHETIC TEST FIXTURE ONLY: Sunny Beach Normal, Slot1,1:00.001,1201 samples.\n"
        <<"Pak: "<<pak<<"\nLabel: "<<(directory/"SYNTHETIC-GHOST-FIXTURE.txt")<<'\n';
}
}
int main(int argc,char** argv) {
    try {
        if(argc>=2 && std::string_view(argv[1])=="--export-synthetic-fixture") {
            if(argc!=3)throw std::runtime_error("--export-synthetic-fixture requires one fresh isolated save-base path");
            export_synthetic_fixture(argv[2]);return 0;
        }
        if(argc!=2)throw std::runtime_error("explicit isolated test directory required");
        auto path=std::filesystem::absolute(argv[1]);
        path/=std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        path/="ghost-test.bin";
        Pak::instance().set_base_save_path_for_tests(path);
        lifecycle();persistence();
        std::cout<<checks<<" ghost lifecycle/persistence checks passed; isolated Pak: "<<path<<'\n';
        return 0;
    } catch(const std::exception& e) {std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
