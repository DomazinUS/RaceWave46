#include "wr64_menu_layout.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
extern "C" {
#include "recomp.h"
#include "funcs.h"
void title_menu_baseline_draw(uint8_t*,recomp_context*);
void do_break(uint32_t){std::abort();}
void switch_error(const char*,uint32_t,uint32_t){std::abort();}
}
struct Draw {int kind,id,x,y,width,height,flag;};
static std::vector<Draw> draws;static int flag=0;static unsigned checks=0;
static void check(bool ok,const char*why){++checks;if(!ok){std::cerr<<"FAIL "<<why<<"\n";std::exit(1);}}
static uint32_t word(const std::vector<uint8_t>&r,uint32_t a){uint32_t v;std::memcpy(&v,r.data()+(a&0x7fffff),4);return v;}
static void put(std::vector<uint8_t>&r,uint32_t a,uint32_t v){std::memcpy(r.data()+(a&0x7fffff),&v,4);}
static recomp_context context(){recomp_context c{};c.r29=S32(0x807ff000);c.r4=S32(0x80600000);return c;}
extern "C" void func_80094338(uint8_t*rdram,recomp_context*c){draws.push_back({0,int(c->r5),int(c->r6),int(c->r7),MEM_W(0x10,c->r29),MEM_W(0x14,c->r29),0});c->r2=c->r4;}
extern "C" void func_801E946C(uint8_t*,recomp_context*c){flag=int(c->r5);c->r2=c->r4;}
extern "C" void func_801E3EE0(uint8_t*rdram,recomp_context*c){draws.push_back({1,int(c->r6),int(c->r7),MEM_W(0x10,c->r29),0,0,flag});c->r2=c->r4;}
extern "C" void func_801E5554(uint8_t*,recomp_context*c){c->r2=c->r4;}
int main(int argc,char**argv){
 check(argc==2,"ROM argument");std::ifstream f(argv[1],std::ios::binary);check(bool(f),"private ROM opens");std::vector<uint8_t>b{std::istreambuf_iterator<char>(f),{}};check(b.size()>0x1B5680,"ROM contains overlay");
 std::vector<uint8_t>ram(8*1024*1024);for(uint32_t i=0;i<0x17f0;++i)ram[(0x2c5800+i)^3]=b[0x1b3ec0+i];
 auto c=context();func_i0_802C6878(ram.data(),&c);check(word(ram,0x800dab24)==3,"native title init mode");
 for(unsigned k=0;k<6;++k){uint32_t table=0x802c6e08+k*24;std::cout<<"table "<<k<<" x="<<word(ram,table+12)<<" rows="<<word(ram,table+4)<<"\n";check(word(ram,table+12)==(k==5?98:150),"live IPS omission");}
 // Confirm Championship through the actual native input handler with Reverse available.
 put(ram,0x802c6ee0,0);put(ram,0x802c6ee4,0);put(ram,0x802c6bc0,1);put(ram,0x802c6bcc,0);
 uint8_t*rdram=ram.data();MEM_H(0,S32(0x801ce65a))=0x8000;c=context();func_i0_802C63AC(ram.data(),&c);check(word(ram,0x802c6ee0)==5,"native unlock path selects table5");
 auto nativeTable=std::array<uint32_t,6>{};for(unsigned j=0;j<6;++j)nativeTable[j]=word(ram,0x802c6e80+j*4);
 for(unsigned k=0;k<6;++k){auto t=0x802c6e08+k*24,n=word(ram,t+4);for(unsigned selected=0;selected<n;++selected){put(ram,0x802c6ee0,k);put(ram,0x802c6ee4,selected);for(unsigned j=0;j<4;++j)put(ram,0x802c6bd4+j*4,1);
  draws.clear();c=context();title_menu_baseline_draw(ram.data(),&c);auto before=draws;
  draws.clear();c=context();func_i0_802C6044(ram.data(),&c);check(draws.size()==before.size(),"draw count preserved");
  for(unsigned j=0;j<draws.size();++j){auto&a=draws[j];auto&z=before[j];check(a.x==z.x+(k==5&&a.kind==1?52:0),"only omitted origin changes");check(a.id==z.id&&a.y==z.y&&a.kind==z.kind&&a.flag==z.flag&&a.width==z.width&&a.height==z.height,"identity color size Y preserved");if(a.kind==0)check(a.x==142,"native frame origin142");}
  check(draws.back().kind==1&&draws.back().flag==6,"selected label native flash3 flag");
  if(k==5&&selected==0){std::cout<<"Reverse before/after label origins:";for(unsigned j=0;j<draws.size();++j)if(draws[j].kind==1)std::cout<<" "<<before[j].x<<"->"<<draws[j].x<<"(y"<<draws[j].y<<",flag"<<draws[j].flag<<")";std::cout<<"\n";}
 }}
 for(unsigned j=0;j<6;++j)check(word(ram,0x802c6e80+j*4)==nativeTable[j],"ROM-derived table never mutated");
 put(ram,0x802c6ee0,5);for(int mode:{1,2,4,40,102,103}){put(ram,0x800dab24,mode);check(wr64_title_menu_origin(ram.data(),0x802c6e80,98)==98,"other modes unchanged");}put(ram,0x800dab24,3);
 check(wr64_title_menu_origin(ram.data(),0x802c6e80,150)==150,"already-corrected data unchanged");
 for(unsigned j=0;j<6;++j){auto a=0x802c6e80+j*4,v=word(ram,a);put(ram,a,v+1);check(wr64_title_menu_origin(ram.data(),0x802c6e80,98)==98,"unknown table fallback");put(ram,a,v);}
 std::cout<<"PASS "<<checks<<" checks; all six menu tables, every selection, native unlock, local-only correction.\n";
}
