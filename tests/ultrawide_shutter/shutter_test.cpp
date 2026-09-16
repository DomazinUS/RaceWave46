#include "common/rt64_wr64_shutter.h"
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <vector>
static unsigned checks=0;
static void require(bool value,const char* reason) {
 ++checks;
 if(!value){std::fprintf(stderr,"FAIL: %s\n",reason);std::exit(1);}
}
struct DrawData {
 std::vector<uint32_t> faceIndices,vertexSegmentedAddresses,worldIndices;
 std::vector<uint32_t> worldTransformSegmentedAddresses;
};
struct GameCall {
 struct{uint32_t faceIndicesStart=0;}meshDesc;
 struct{uint32_t triangleCount=1;}callDesc;
};
int main(){
 using namespace RT64;
 for(uint32_t base:{0x0105A7A8U,0x0105B3D8U,0x0105C008U,0x0105CC38U}){
  for(uint32_t offset=0;offset<0x240;offset+=16){
   require(wr64UsaShutterVertex(base+offset),"native cover/edge vertex rejected");
   require(!wr64UsaShutterVertex(base+offset+1),"unaligned source accepted");
   DrawData data{{0,1,2},{base+offset,base,base+16},{1,1,1},{0,0x07001340}};
   GameCall call;
   require(wr64UsaShutterCall(data,call),"valid native indexed draw rejected");
   data.vertexSegmentedAddresses[1]=0x01020000;
   require(!wr64UsaShutterCall(data,call),"mixed unrelated geometry accepted");
   data.vertexSegmentedAddresses[1]=base;
   data.worldTransformSegmentedAddresses[1]=0x02000A40;
   require(!wr64UsaShutterCall(data,call),"same mesh with unrelated transform accepted");
   data.worldTransformSegmentedAddresses[1]=0x07001340;
   data.worldIndices[1]=5;
   require(!wr64UsaShutterCall(data,call),"out-of-range transform accepted");
   data.worldIndices[1]=1;
   data.worldIndices.pop_back();
   require(!wr64UsaShutterCall(data,call),"missing vertex transform accepted");
  }
  require(!wr64UsaShutterVertex(base-16),"preceding display list claimed as mesh");
  require(!wr64UsaShutterVertex(base+0x240),"following texture claimed as mesh");
 }
 DrawData data{{0,1,2},{0x0105A7A8,0x0105A7B8,0x0105A7C8},{0,0,0},{0x07001340}};
 GameCall call;
 call.callDesc.triangleCount=0;
 require(!wr64UsaShutterCall(data,call),"empty draw accepted");
 call.callDesc.triangleCount=2;
 require(!wr64UsaShutterCall(data,call),"truncated index list accepted");
 call.callDesc.triangleCount=1;call.meshDesc.faceIndicesStart=UINT32_MAX;
 require(!wr64UsaShutterCall(data,call),"invalid index start accepted");
 call.meshDesc.faceIndicesStart=0;data.faceIndices[1]=UINT32_MAX;
 require(!wr64UsaShutterCall(data,call),"invalid vertex index accepted");
 constexpr float scale=0.875f,offset=0.3125f,halfPixel=0.000125f;
 for(float expansion:{-1.0f,0.0f,0.75f,1.0f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()}){
  const auto result=wr64UsaShutterMapping(scale,offset,halfPixel,expansion);
  require(result.scale==scale && result.offset==offset,"baseline or invalid aspect changed");
 }
 for(float expansion:{1.3125f,2.0f}){
  const auto result=wr64UsaShutterMapping(scale,offset,halfPixel,expansion);
  require(result.scale==scale*expansion,"existing call scale lost");
  require(result.offset==halfPixel+(offset-halfPixel)*expansion,"animated offset or raster origin lost");
 }
 std::printf("PASS: %u USA shutter identity and mapping checks\n",checks);
}
