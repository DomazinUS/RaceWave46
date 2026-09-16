#include "recomp.h"
#include "wr64_twilight_buoy_lights.h"
#include "common/rt64_wr64_rt_beam.h"
#include <array>
#include <algorithm>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

extern "C" {
void baseline_twilight_lights(uint8_t*, recomp_context*);
void enhanced_twilight_lights(uint8_t*, recomp_context*);
void func_8006A264(uint8_t*, recomp_context*);
}
namespace {
using Ram = std::vector<uint8_t>;
using Command = std::pair<uint32_t, uint32_t>;
using Fn = void(*)(uint8_t*, recomp_context*);
constexpr uint32_t Size=0x800000, Stack=0x807FE000, Common=0x80480000;
constexpr uint32_t Display=0x8011F8E8, Pool=0x80198368;
constexpr uint32_t Buoy=0x801AEE20, Visibility=0x801C0840, Count=0x801BB120;
unsigned checks=0, cases=0; uint64_t accesses=0; bool active=false;
Ram rom;
void require(bool good,const char* text) {++checks;if(!good){std::cerr<<"FAIL case "<<cases<<": "<<text<<'\n';std::exit(1);}}
void put(Ram& ram,uint32_t at,uint32_t value){auto* rdram=ram.data();MEM_W(0,S32(at))=value;}
uint32_t get(const Ram& ram,uint32_t at){return *reinterpret_cast<const uint32_t*>(ram.data()+(at&0x7FFFFF));}
void number(Ram& ram,uint32_t at,float value){put(ram,at,std::bit_cast<uint32_t>(value));}
void context(recomp_context& c){c={};c.f_odd=&c.f0.u32h;c.r29=S32(Stack);}
Ram initial(unsigned players,unsigned view,unsigned total=2,unsigned bank=0,unsigned course=6){
    Ram ram(Size,0);auto* rdram=ram.data();
    put(ram,0x800DAB28,players);put(ram,0x800DAB2C,view);put(ram,Count,total);
    put(ram,0x800D8170,course);put(ram,0x801518B8,Display+bank*0x18FE8);
    put(ram,0x80151984,Common&0x1FFFFFFF);
    for(uint32_t i=0;i<0x6FB70;++i)MEM_B(0,S32(Common+i))=rom[0xF6090+i];
    // Execute the actual double-buffer selection/reset, not a fabricated pool pointer.
    put(ram,0x800D4B0C,bank);recomp_context c;context(c);func_8006A264(ram.data(),&c);
    require(get(ram,0x801AE948)==Pool+bank*0xB2F0,"native matrix-pool family changed");
    require(get(ram,0x801AE950)==0,"native matrix allocation reset changed");
    put(ram,0x801AE950,17);
    for(unsigned i=0;i<std::min(total,64u);++i){
        const uint32_t b=Buoy+i*0x104;
        number(ram,b+0x24,100.25f+i*120);number(ram,b+0x28,-200.5f-i*100);
        put(ram,b+0x98,i%2);put(ram,b+0x9C,0);put(ram,b+0xC8,1);
        MEM_H(0,S32(Visibility+i*2))=i;
    }
    for(unsigned p=0;p<2;++p){
        const uint32_t camera=0x80227C80+p*0x10C;
        number(ram,camera+0x4C,500+p*100);number(ram,camera+0x50,80);number(ram,camera+0x54,700-p*50);
    }
    return ram;
}
uint32_t listStart(Ram& ram){return get(ram,0x801518B8)+0x100;}
std::vector<Command> draw(Ram& ram,Fn fn,uint32_t start=0){
    if(!start)start=listStart(ram);
    put(ram,Stack+0x550,start);
    recomp_context c;context(c);c.r24=get(ram,0x800DAB28);c.r21=S32(0x800DAB28);
    fn(ram.data(),&c);const auto end=get(ram,Stack+0x550);
    require(end>=start&&end<=start+0x900&&(end-start)%8==0,"native light list exceeds bound");
    require(uint32_t(c.r29)==Stack,"native light stack imbalance");
    std::vector<Command> out;for(uint32_t at=start;at<end;at+=8)out.emplace_back(get(ram,at),get(ram,at+4));return out;
}
bool has(const std::vector<Command>& c,uint32_t a,uint32_t b){return std::find(c.begin(),c.end(),Command{a,b})!=c.end();}
void preserve(const Ram& before,const Ram& after,uint32_t display,uint32_t matrices){
    for(unsigned i=0;i<Size;++i) if(before[i]!=after[i]){
        const uint32_t p=0x80000000+i;
        bool allowed=(p>=Stack-0x100&&p<Stack+0x554)||(p>=display&&p<display+0x6000)||
            (p>=matrices+0x4140&&p<matrices+0x5140)||(p>=0x801AE950&&p<0x801AE954);
        require(allowed,"light draw changed camera, viewport, physics or unrelated matrix memory");
    }
}
void verify(const std::vector<Command>& commands,unsigned total,unsigned firstSlot,bool reused=true){
    require(commands.size()==14+4*total,"native command budget incorrect");
    require(has(commands,0xB900031D,0x00552078),"native opaque light base material missing");
    require(has(commands,0xB900031D,0x005049D8),"native translucent column material missing");
    unsigned m=0;for(auto [a,b]:commands)if(a==0x01020040){
        require(b==0x05004140+(firstSlot+(reused?m%total:m))*64,"dynamic matrix slot wrong");++m;
    }
    require(m==total*2,"light matrix count differs");
    if(total>=2)for(uint32_t root:{0x0102BF48u,0x0102BFD8u,0x0102C798u,0x0102C828u})
        require(has(commands,0x06000000,root),"native left/right light model missing");
    for(auto [a,b]:commands)require((a>>24)!=0xED && (a>>24)!=0x03,"light pass changed scissor/viewport");
}
// Follow the actual emitted light commands into their resident common-bank
// models. Material and indexed provenance are both checked by production RT
// predicates; native view/scissor preservation is verified separately below.
struct RTBeamDecoder {
    uint32_t ccL=0,ccH=0,omL=0,omH=0,geometry=0,image=0;
    bool texture=false;
    std::array<uint32_t,128> vertices{};
    std::vector<uint32_t> sources;
    unsigned commands=0,beams=0,baseDraws=0,families=0;
    // The unmodified caller at 80070FF4..80071074 sets no TLUT,
    // perspective and three-point filtering before this local branch. The
    // emitted pass supplies its own cycle/blender/combiner/geometry state.
    explicit RTBeamDecoder(uint32_t dither):omH((0x080CFFu&~0xC0u)|dither){}
    void flush(){
        if(sources.empty())return;
        const int family=RT64::wr64RTTwilightBeamSourceFamily(sources.data(),sources.size());
        const bool material=RT64::wr64RTTwilightBeamMaterial(ccL,ccH,omL,omH,geometry,
            uint32_t(sources.size()/3),texture?1u:0u);
        if(family>=0){
            require(material,"actual native beam geometry not admitted by production RT material");
            require(texture&&((image>>21)&7)==3&&((image>>19)&3)==2,
                "actual beam does not use its native IA16 alpha texture");
            ++beams;families|=1u<<family;
        }else{
            require(!material,"opaque light base misclassified as translucent RT beam");
            ++baseDraws;
        }
        sources.clear();
    }
    uint32_t word(size_t at){
        require(at+4<=rom.size(),"beam display-list ROM bounds");
        return uint32_t(rom[at])<<24|uint32_t(rom[at+1])<<16|uint32_t(rom[at+2])<<8|rom[at+3];
    }
    void command(uint32_t a,uint32_t b,unsigned depth=0){
        require(++commands<5000&&depth<12,"bounded native light display-list traversal");
        const unsigned op=a>>24;
        if(op!=0xBF&&op!=0xB1&&op!=0xB5)flush();
        if(op==0xFC){ccL=a;ccH=b;}
        else if(op==0xBA||op==0xB9){
            const unsigned size=a&255,shift=(a>>8)&255;
            require(size<=32&&shift<32&&size+shift<=32,"beam othermode field bounds");
            const uint32_t mask=uint32_t(((uint64_t(1)<<size)-1)<<shift);
            auto& value=op==0xBA?omH:omL;value=(value&~mask)|b;
        }else if(op==0xB6)geometry&=~b;
        else if(op==0xB7)geometry|=b;
        else if(op==0xBB){
            texture=(a&255)!=0;
            require(((a>>11)&7)==0,"native beam unexpectedly uses multiple texture levels");
        }else if(op==0xFD)image=a;
        else if(op==0x04){
            const unsigned count=(a>>9)&127,first=((a>>16)&255)/5;
            require(count&&first+count<=vertices.size(),"native light vertex slots");
            for(unsigned i=0;i<count;++i)vertices[first+i]=b+i*16;
        }else if(op==0xBF||op==0xB1){
            auto triangle=[&](uint32_t w){for(unsigned shift:{16u,8u,0u}){
                const unsigned index=((w>>shift)&255)/5;
                require(index<vertices.size()&&vertices[index],"native beam triangle unloaded vertex");
                sources.push_back(vertices[index]);
            }};
            if(op==0xB1)triangle(a);triangle(b);
        }else if(op==0xB5){
            const unsigned indices[4]={(b>>24)/5,((b>>16)&255)/5,((b>>8)&255)/5,(b&255)/5};
            for(unsigned corner:{0u,1u,2u,0u,2u,3u}){
                const unsigned index=indices[corner];
                require(index<vertices.size()&&vertices[index],"native beam quad unloaded vertex");
                sources.push_back(vertices[index]);
            }
        }else if(op==0x06){
            require((b>>24)==1,"native light model outside resident common bank");
            size_t at=0xF6090+(b&0xFFFFFF);
            while(true){const uint32_t x=word(at),y=word(at+4);command(x,y,depth+1);at+=8;if((x>>24)==0xB8)break;}
        }
    }
};
void verifyRTAdmission(const std::vector<Command>& emitted){
    for(uint32_t dither:{0u,0xC0u}){
        RTBeamDecoder decoder(dither);
        // Verify the caller's original instruction operands before replaying
        // its three-point command. This is inherited state, not added by RT.
        require(decoder.word(0x80071060-0x80045800)==0x35CE0C02 &&
            decoder.word(0x8007106C-0x80045800)==0x240F2000,
            "unchanged native caller three-point setup instruction changed");
        decoder.command(0xBA000C02,0x2000);
        for(auto [a,b]:emitted)decoder.command(a,b);
        decoder.flush();
        require(decoder.beams==2&&decoder.families==3,"both native yellow/red columns admitted to RT");
        require(decoder.baseDraws==2,"opaque light bases retain separate native identity");
    }
}

void standard(unsigned players,unsigned view,bool enable,unsigned bank,unsigned course){
    ++cases;active=enable;auto input=initial(players,view,2,bank,course),baseline=input,enhanced=input;
    auto before=draw(baseline,baseline_twilight_lights),after=draw(enhanced,enhanced_twilight_lights);
    preserve(input,enhanced,Display+bank*0x18FE8,Pool+bank*0xB2F0);
    if(!enable||players==1||course!=6) require(before==after&&baseline==enhanced,"Original/1P/non-Twilight path changed");
    const bool visible=course==6&&(players==1||enable);
    if(visible){
        const bool reused=players==2&&enable;
        verify(after,2,17,reused);verifyRTAdmission(after);require(get(enhanced,0x801AE950)==(reused?19:21),"native matrix counter delta wrong");
        auto single=input;put(single,0x800DAB28,1);
        const auto original=draw(single,baseline_twilight_lights);
        require(original.size()==after.size(),"native command count changed");
        for(unsigned i=0;i<original.size();++i){
            if(original[i].first!=0x01020040){require(original[i]==after[i],"native material/model command changed");continue;}
            require(after[i].first==original[i].first,"native matrix command changed");
            const auto origAddress=((Pool+bank*0xB2F0)&0x7FFFFF)+(original[i].second&0xFFFFFF);
            const auto newAddress=((Pool+bank*0xB2F0)&0x7FFFFF)+(after[i].second&0xFFFFFF);
            require(std::equal(single.begin()+origAddress,single.begin()+origAddress+64,enhanced.begin()+newAddress),
                "shared matrix bytes differ from either original base or column translation");
        }
    } else require(after.empty(),"inactive native path emitted light geometry");
}
void sequentialViews(bool vertical,unsigned bank){
    ++cases;active=true;auto ram=initial(2,0,2,bank);const auto list=listStart(ram);
    // Existing viewport/scissor commands stand for the caller's split layout.
    // The restored world geometry must append after these, without changing them.
    put(ram,list-16,0x03800010);put(ram,list-12,0x05000000);
    put(ram,list-8,0xED000000);put(ram,list-4,vertical?0x00280500:0x00500280);
    const auto first=draw(ram,enhanced_twilight_lights);verify(first,2,17);
    const auto p1=ram;const uint32_t second=list+uint32_t(first.size()*8)+16;
    put(ram,0x800DAB2C,1);auto* rdram=ram.data();MEM_H(0,S32(Visibility))=-1;
    put(ram,second-16,0x03800010);put(ram,second-12,0x05000010);
    put(ram,second-8,vertical?0xED280000:0xED000280);put(ram,second-4,0x00500500);
    const auto before=ram;const auto result=draw(ram,enhanced_twilight_lights,second);verify(result,1,19);
    require(get(ram,0x801AE950)==20,"second view did not append exactly its visible light matrices");
    require(std::equal(p1.begin()+((Pool+bank*0xB2F0+0x4140+17*64)&0x7FFFFF),
        p1.begin()+((Pool+bank*0xB2F0+0x4140+19*64)&0x7FFFFF),
        ram.begin()+((Pool+bank*0xB2F0+0x4140+17*64)&0x7FFFFF)),"P2 overwrote P1 light matrices");
    require(has(result,0x06000000,0x0102BF48)&&!has(result,0x06000000,0x0102C798),"P2 ignored its own visibility");
    for(uint32_t at:{list-16,list-12,list-8,list-4,second-16,second-12,second-8,second-4})
        require(get(before,at)==get(ram,at),"split-layout caller state was overwritten");
    preserve(before,ram,Display+bank*0x18FE8,Pool+bank*0xB2F0);
}
void boundaries(){
    for(unsigned bank=0;bank<2;++bank){
        ++cases;active=true;auto full=initial(2,1,64,bank);put(full,0x801AE950,0);
        // The very next native region holds live sprite vertices, not more matrices.
        for(uint32_t i=0;i<0x80;i+=4)put(full,Pool+bank*0xB2F0+0x5140+i,0xA53F7091);
        auto atMatrixLimit=full;verify(draw(atMatrixLimit,enhanced_twilight_lights),64,0);
        require(get(atMatrixLimit,0x801AE950)==64,"exact64-slot allocation rejected");
        preserve(full,atMatrixLimit,Display+bank*0x18FE8,Pool+bank*0xB2F0);
        put(full,0x801AE950,1);require(draw(full,enhanced_twilight_lights).empty(),"matrix/sprite boundary overflow not rejected");
        ++cases;auto ram=initial(2,1,2,bank);const auto last=Display+bank*0x18FE8+0x6000-0x800-(112+2*32);
        auto exact=ram;verify(draw(exact,enhanced_twilight_lights,last),2,17);
        require(draw(ram,enhanced_twilight_lights,last+8).empty(),"display-list tail overflow not rejected");
    }
    // Exact reservations for actual native downstream categories. P1 also
    // reserves P2 objects outside P1's frustum and the other player's lights.
    for(unsigned view=0;view<2;++view){
        ++cases;active=true;auto ram=initial(2,view,1);auto* rdram=ram.data();
        put(ram,0x801BFA40,2);
        put(ram,0x801BC940+0x54,2);MEM_H(0,S32(0x801C0AC0))=0;
        put(ram,0x801BC940+0xC4+0x54,1);put(ram,0x801BC940+0xC4+0x58,1);
        MEM_H(0,S32(0x801C0AC2))=-1;
        put(ram,0x801D7B70,1);put(ram,0x801D7B70+15*0x24,1);
        // P1: currentlight1 + currentbillboard1 + P2objects2 + debris4 + P2light1=9.
        // P2: currentlight1 + currentbillboard1 + debris2=4.
        const unsigned available=view==0?55:60;
        put(ram,0x801AE950,available);auto exact=ram;
        verify(draw(exact,enhanced_twilight_lights),1,available);
        put(ram,0x801AE950,available+1);
        require(draw(ram,enhanced_twilight_lights).empty(),"downstream matrix reservation was not retained");
    }
    for(unsigned reject=0;reject<13;++reject){
        ++cases;active=true;auto ram=initial(2,1,1);auto* rdram=ram.data();
        switch(reject){
        case 0: MEM_H(0,S32(Visibility))=-1;break;
        case 1: put(ram,Buoy+0x9C,1);break;
        case 2: put(ram,Buoy+0xC8,0);break;
        case 3: put(ram,Count,0);break;
        case 4: put(ram,Count,65);break;
        case 5: put(ram,0x800DAB2C,2);break;
        case 6: put(ram,0x801AE948,Pool+4);break;
        case 7: put(ram,0x801AE950,0xFFFFFFFF);break;
        case 8: put(ram,0x801518B8,Display+8);break;
        case 9: put(ram,0x80151984,0x7FFFF0);break;
        case 10: put(ram,Common+0x2BF48,0);break;
        case 11: put(ram,Common+0x2C82C,0);break;
        case 12: put(ram,Common+0x2BFE0,0);break;
        }
        require(draw(ram,enhanced_twilight_lights).empty(),"invalid or invisible native light pass not rejected");
        require(get(ram,0x801AE950)==(reject==7?0xFFFFFFFFu:17u),"rejected pass allocated matrix");
    }
}
}
extern "C" uint32_t wr64_sunny_detail_active(uint8_t*){return active;}
extern "C" void do_break(uint32_t){require(false,"native break");}
extern "C" void* wr64_test_address(uint8_t* r,uint64_t at,unsigned width,const char*,int){
    ++accesses;uint32_t a=uint32_t(at);require(a>=0x80000000&&a<=0x80800000-width,"native access outside RDRAM");return r+(a&0x7FFFFF);
}
int main(int argc,char** argv){
    require(argc==2,"private ROM path required");std::ifstream f(argv[1],std::ios::binary);
    rom=Ram(std::istreambuf_iterator<char>(f),{});require(rom.size()==Size,"ROM size");
    for(unsigned bank=0;bank<2;++bank)for(unsigned view=0;view<2;++view){
        standard(1,view,false,bank,6);standard(2,view,false,bank,6);standard(2,view,true,bank,6);
    }
    for(unsigned course=0;course<=9;++course)if(course!=6)standard(2,0,true,0,course);
    for(bool vertical:{false,true})for(unsigned bank=0;bank<2;++bank)sequentialViews(vertical,bank);
    boundaries();std::cout<<"PASS "<<cases<<" native Twilight light scenarios, "<<checks<<" checks, "<<accesses<<" checked accesses\n";
}
