#include "wr64_controller_pak.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

namespace ultramodern { std::filesystem::path get_save_file_path() { return {}; } }
namespace {
using namespace wr64::controller_pak;
using Bytes = std::vector<std::uint8_t>;
int checks = 0;
void check(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
void result(Result actual, Result expected, const char* message) { check(actual == expected, message); }
Key key(int id) { Key k{}; k.company_code=1; k.game_code=0x4E57524A; k.game_name[0]=static_cast<std::uint8_t>(id); return k; }
template<class T> void scalar(Bytes& bytes,T value) {
    const auto* first=reinterpret_cast<const std::uint8_t*>(&value);
    bytes.insert(bytes.end(),first,first+sizeof(value));
}
struct Record { std::uint8_t occupied; Key key; std::uint32_t size; };
Bytes image(const std::vector<Record>& records) {
    Bytes out={'W','R','6','4','P','A','K','1'}; scalar<std::uint32_t>(out,1);
    for(int i=0;i<kDirectoryEntryCount;++i) {
        const Record r=i<static_cast<int>(records.size())?records[i]:Record{};
        scalar(out,r.occupied); scalar(out,r.key.company_code); scalar(out,r.key.game_code);
        out.insert(out.end(),r.key.game_name.begin(),r.key.game_name.end());
        out.insert(out.end(),r.key.extension_name.begin(),r.key.extension_name.end());
        scalar(out,r.size);
        if(r.occupied) out.insert(out.end(),r.size,0x5A);
    }
    return out;
}
Bytes read(const std::filesystem::path& path) {
    std::ifstream in(path,std::ios::binary);
    return Bytes(std::istreambuf_iterator<char>{in},{});
}
void write(const std::filesystem::path& path,const Bytes& bytes) {
    std::ofstream out(path,std::ios::binary);
    out.write(reinterpret_cast<const char*>(bytes.data()),bytes.size());
    check(out.good(),"fixture write");
}
std::filesystem::path setup(const std::filesystem::path& root,const std::string& name) {
    const auto directory=root/name; std::filesystem::create_directories(directory);
    Store::instance().set_base_save_path_for_tests(directory/"test.bin");
    return directory/"test.controller-pak-1.bin";
}
void corrupt(const std::filesystem::path& root,const std::string& name,const Bytes& bytes) {
    const auto path=setup(root,name);write(path,bytes);
    auto& store=Store::instance();
    result(store.initialize(0),Result::Inconsistent,"corrupt image must be rejected");
    int slot=999;std::int32_t free=999,maximum=999,used=999;
    result(store.allocate_file(0,key(55),256,slot),Result::Inconsistent,"corrupt image must not be reformatted by allocation");
    result(store.free_blocks(0,free),Result::Inconsistent,"corrupt image cannot report wrapped free space");
    result(store.num_files(0,maximum,used),Result::Inconsistent,"corrupt directory cannot be used");
    check(slot==999 && free==999 && maximum==999 && used==999,"error outputs must remain unchanged");
    check(read(path)==bytes,"corrupt image must be preserved");
}
void malformed_images(const std::filesystem::path& root) {
    corrupt(root,"aggregate-capacity",image({{1,key(1),15743},{1,key(2),15743}}));
    corrupt(root,"oversized-entry",image({{1,key(1),static_cast<std::uint32_t>(kCapacityBytes+1)}}));
    corrupt(root,"duplicate-key",image({{1,key(1),256},{1,key(1),256}}));
    corrupt(root,"invalid-occupied",image({{2,key(1),256}}));
    corrupt(root,"zero-size-occupied",image({{1,key(1),0}}));
    corrupt(root,"size-on-empty-slot",image({{0,key(1),4}}));
    auto bytes=image({{1,key(1),256}});
    bytes.resize(43+8);corrupt(root,"truncated-payload",bytes);
    bytes=image({});bytes.pop_back();corrupt(root,"truncated-directory",bytes);
    bytes=image({});bytes.push_back(1);corrupt(root,"trailing-data",bytes);
    bytes=image({});bytes[0]=0;corrupt(root,"invalid-magic",bytes);
    bytes=image({});bytes[8]=2;corrupt(root,"unknown-version",bytes);
    corrupt(root,"empty-file",{});

    const auto path=setup(root,"exact-capacity");
    write(path,image({{1,key(1),30976},{1,key(2),512}}));
    auto& store=Store::instance();std::int32_t free=-1;
    result(store.initialize(0),Result::Ok,"valid ghost-plus-records image");
    result(store.free_blocks(0,free),Result::Ok,"full image free space");
    check(free==0,"exact capacity must remain supported");

    setup(root,"directory-full");
    int slot=-1;
    for(int i=0;i<kDirectoryEntryCount;++i) result(store.allocate_file(0,key(i),1,slot),Result::Ok,"fill directory");
    result(store.allocate_file(0,key(17),1,slot),Result::DirectoryFull,"directory bound");
    result(store.allocate_file(0,key(1),1,slot),Result::Exists,"existing key");
    result(store.allocate_file(0,key(18),0xFFFFFFFFU,slot),Result::Invalid,"huge size rejection");
}
void failed_mutations(const std::filesystem::path& path) {
    auto& store=Store::instance();
    const Bytes before=read(path);
    const std::array<std::uint8_t,4> replacement={9,9,9,9};
    std::array<std::uint8_t,4> received{};
    int new_slot=777;
    result(store.allocate_file(0,key(2),256,new_slot),Result::ControllerFailure,"failed allocation");
    check(new_slot==777,"failed allocation must not publish a slot");
    int existing=-1;
    result(store.find_file(0,key(2),existing),Result::Invalid,"failed allocation must not create RAM entry");
    result(store.write_file(0,0,8,replacement),Result::ControllerFailure,"failed write");
    result(store.read_file(0,0,8,received),Result::Ok,"read after failed write");
    check(received==std::array<std::uint8_t,4>{1,2,3,4},"failed write must preserve RAM");
    result(store.delete_file(0,key(1)),Result::ControllerFailure,"failed delete");
    result(store.find_file(0,key(1),existing),Result::Ok,"failed delete must preserve RAM entry");
    check(existing==0,"original slot must remain allocated");
    std::int32_t free=-1;
    result(store.free_blocks(0,free),Result::Ok,"free space after failures");
    check(free==kCapacityBytes-256,"failed allocation must preserve capacity");
    check(read(path)==before,"failed save must preserve the primary image");
}
std::filesystem::path seed(const std::filesystem::path& root,const std::string& name) {
    const auto path=setup(root,name);auto& store=Store::instance();int slot=-1;
    result(store.allocate_file(0,key(1),256,slot),Result::Ok,"seed allocation");
    const std::array<std::uint8_t,4> data={1,2,3,4};
    result(store.write_file(0,slot,8,data),Result::Ok,"seed write");
    return path;
}
void failures(const std::filesystem::path& root) {
    auto path=seed(root,"temp-open-failure");auto temporary=path;temporary+=".temp";
    std::filesystem::create_directory(temporary);failed_mutations(path);
    std::filesystem::remove(temporary);
    // Retrying the same requested operation succeeds, including after reload.
    auto& store=Store::instance();int slot=-1;
    result(store.allocate_file(0,key(2),256,slot),Result::Ok,"allocation retry");
    check(slot==1,"allocation retry must use first free slot");
    store.reset_for_tests();result(store.find_file(0,key(2),slot),Result::Ok,"successful retry persists");

    path=seed(root,"backup-failure");auto backup=path;backup+=".bak";
    std::filesystem::remove(backup);std::filesystem::create_directory(backup);failed_mutations(path);
#ifdef _WIN32
    path=seed(root,"atomic-replace-failure");
    HANDLE held=CreateFileW(path.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
    check(held!=INVALID_HANDLE_VALUE,"create isolated replacement failure");
    failed_mutations(path);CloseHandle(held);
    store.reset_for_tests();
    std::array<std::uint8_t,4> received{};
    result(store.read_file(0,0,8,received),Result::Ok,"reload after failed atomic replace");
    check(received==std::array<std::uint8_t,4>{1,2,3,4},"committed disk state survives replacement failure");
#endif
    path=setup(root,"unreadable-path");std::filesystem::create_directory(path);
    result(store.initialize(0),Result::ControllerFailure,"existing unreadable path must not be formatted");
}
}
int main(int argc,char** argv) {
    try {
        if(argc!=2)throw std::runtime_error("explicit isolated test root is required");
        auto root=std::filesystem::absolute(argv[1])/std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        malformed_images(root);failures(root);
        std::cout<<"Controller Pak corruption and transactional persistence: "<<checks<<" checks passed\n";
        return 0;
    } catch(const std::exception& e) { std::cerr<<e.what()<<"\n";return 1; }
}
