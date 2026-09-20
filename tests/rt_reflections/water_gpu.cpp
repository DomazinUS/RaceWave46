// Headless GPU regression for the actual RSPProcessCS/RSPWorldCS shaders.
// The deliberately nonplanar fixture exercises field interpolation, recentering,
// coverage and fallback paths. It is analytical data, not a captured game mesh.
// Shader outputs are read back only here in the standalone optional test.
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <algorithm>
using Microsoft::WRL::ComPtr;
static void check(HRESULT hr,const char* s) { if(FAILED(hr)) {std::cerr<<s<<" hr="<<std::hex<<hr<<'\n';throw std::runtime_error(s);} }
static void require(bool b,const char* s) {if(!b)throw std::runtime_error(s);}
static std::vector<char> readFile(const char* p) {std::ifstream f(p,std::ios::binary);require(bool(f),"missing shader");return {std::istreambuf_iterator<char>(f),{}};}
static ComPtr<ID3D12Resource> buffer(ID3D12Device* d,UINT64 size,D3D12_HEAP_TYPE heapType,D3D12_RESOURCE_STATES state,D3D12_RESOURCE_FLAGS flags=D3D12_RESOURCE_FLAG_NONE) {
 D3D12_HEAP_PROPERTIES h{};h.Type=heapType;D3D12_RESOURCE_DESC r{};r.Dimension=D3D12_RESOURCE_DIMENSION_BUFFER;r.Width=size;r.Height=1;r.DepthOrArraySize=1;r.MipLevels=1;r.SampleDesc.Count=1;r.Layout=D3D12_TEXTURE_LAYOUT_ROW_MAJOR;r.Flags=flags;
 ComPtr<ID3D12Resource> out;check(d->CreateCommittedResource(&h,D3D12_HEAP_FLAG_NONE,&r,state,nullptr,IID_PPV_ARGS(&out)),"buffer");return out;
}
static void barrier(ID3D12GraphicsCommandList* c,ID3D12Resource* r,D3D12_RESOURCE_STATES before,D3D12_RESOURCE_STATES after) {
 D3D12_RESOURCE_BARRIER b{};b.Type=D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;b.Transition={r,D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,before,after};c->ResourceBarrier(1,&b);
}
struct F4{float x,y,z,w;};struct U4{UINT x,y,z,w;};
struct Constants{UINT start,count;float previous,current;UINT enabled;};
static_assert(sizeof(Constants)==20,"RSPWorld push constants must match production WorldCB");
struct Fixture {
 static constexpr UINT count=13;
 std::vector<float> pos,vel,tc,tcVel;
 std::vector<UINT> indices,colors;
 std::vector<int> normals;
 std::vector<U4> info;
 std::vector<F4> previousPos,previousTc;
 std::array<UINT,6> faces{0,1,2,1,3,2};
 std::array<float,16> matrix{1.25f,0,0,0,0,.75f,0,0,0,0,2,0,0,0,0,1};
 Fixture():pos(count*3),vel(count*3),tc(count*2),tcVel(count*2),indices(count),colors(count*4,127),normals(count*4),info(count),previousPos(count),previousTc(count) {
  const F4 positions[count]={{0,2,0,0},{8,6,0,0},{0,8,8,0},{8,3,8,0},{2,25,2,0},{4,8,3,0},{1,9,6,0},{6,20,6,0},{-2,5,10,0},{3,14,5,0},{3,40,4,0},{12,50,12,0},{-3,4,6,0}};
  for(UINT i=0;i<count;i++) {pos[i*3]=positions[i].x;pos[i*3+1]=positions[i].y;pos[i*3+2]=positions[i].z;vel[i*3]=i>=4?.2f*i:0;vel[i*3+1]=i>=4?3.25f*i:0;vel[i*3+2]=i>=4?-.15f*i:0;previousPos[i]={positions[i].x+1,positions[i].y-4,positions[i].z-.5f,1.75f};previousTc[i]={.1f*i,.2f*i,-.75f,0};tc[i*2]=.5f*i;tc[i*2+1]=.25f*i;tcVel[i*2]=.02f*i;tcVel[i*2+1]=-.03f*i;}
  previousPos[0].y=-1;previousPos[1].y=7;previousPos[2].y=3;previousPos[3].y=11;
  const UINT modes[count]={0,0,0,0,1,2,3,4,5,6,1,1,0};
  float offsetX=.25f,offsetZ=-.125f;UINT ox,oz;std::memcpy(&ox,&offsetX,4);std::memcpy(&oz,&offsetZ,4);
  for(UINT i=4;i<12;i++) info[i]={modes[i],2,ox,oz};info[10].y=0;
 }
};
struct Device {
 ComPtr<ID3D12Device> device;ComPtr<ID3D12CommandQueue> queue;ComPtr<ID3D12CommandAllocator> allocator;ComPtr<ID3D12GraphicsCommandList> commands;ComPtr<ID3D12Fence> fence;HANDLE event=nullptr;UINT64 serial=0;
 Device() {
  ComPtr<IDXGIFactory6> f;check(CreateDXGIFactory1(IID_PPV_ARGS(&f)),"factory");ComPtr<IDXGIAdapter1> a;
  for(UINT i=0;f->EnumAdapterByGpuPreference(i,DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,IID_PPV_ARGS(&a))!=DXGI_ERROR_NOT_FOUND;i++) {DXGI_ADAPTER_DESC1 ad{};a->GetDesc1(&ad);if(!(ad.Flags&DXGI_ADAPTER_FLAG_SOFTWARE)&&SUCCEEDED(D3D12CreateDevice(a.Get(),D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device)))) {std::wcout<<L"Compute adapter: "<<ad.Description<<L'\n';break;}a.Reset();}
  if(!device){ComPtr<IDXGIAdapter> warp;check(f->EnumWarpAdapter(IID_PPV_ARGS(&warp)),"warp");check(D3D12CreateDevice(warp.Get(),D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device)),"warp device");std::cout<<"Compute adapter: WARP fallback\n";}
  D3D12_COMMAND_QUEUE_DESC q{};q.Type=D3D12_COMMAND_LIST_TYPE_DIRECT;check(device->CreateCommandQueue(&q,IID_PPV_ARGS(&queue)),"queue");check(device->CreateCommandAllocator(q.Type,IID_PPV_ARGS(&allocator)),"allocator");check(device->CreateCommandList(0,q.Type,allocator.Get(),nullptr,IID_PPV_ARGS(&commands)),"commands");check(commands->Close(),"close initial");check(device->CreateFence(0,D3D12_FENCE_FLAG_NONE,IID_PPV_ARGS(&fence)),"fence");event=CreateEvent(nullptr,FALSE,FALSE,nullptr);require(event!=nullptr,"event");
 }
 ~Device(){if(event)CloseHandle(event);}
 void begin(){check(allocator->Reset(),"reset allocator");check(commands->Reset(allocator.Get(),nullptr),"reset commands");}
 void finish(){check(commands->Close(),"close");ID3D12CommandList* c[]={commands.Get()};queue->ExecuteCommandLists(1,c);check(queue->Signal(fence.Get(),++serial),"signal");check(fence->SetEventOnCompletion(serial,event),"event setup");require(WaitForSingleObject(event,30000)==WAIT_OBJECT_0,"GPU timeout");}
};
struct Runner {
 Device& d;ComPtr<ID3D12DescriptorHeap> heap;ComPtr<ID3D12RootSignature> root;ComPtr<ID3D12PipelineState> pipeline;UINT descriptorSize;std::vector<ComPtr<ID3D12Resource>> inputs;std::array<ComPtr<ID3D12Resource>,3> outputs,readbacks;std::array<UINT,3> strides;bool ran=false;
 D3D12_CPU_DESCRIPTOR_HANDLE cpu(UINT i){auto h=heap->GetCPUDescriptorHandleForHeapStart();h.ptr+=SIZE_T(i)*descriptorSize;return h;}
 Runner(Device& dev,const char* shader,bool world):d(dev),strides{16,world?16U:8U,16} {
  D3D12_DESCRIPTOR_HEAP_DESC hd{};hd.Type=D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;hd.NumDescriptors=64;hd.Flags=D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;check(d.device->CreateDescriptorHeap(&hd,IID_PPV_ARGS(&heap)),"descriptor heap");descriptorSize=d.device->GetDescriptorHandleIncrementSize(hd.Type);
  D3D12_DESCRIPTOR_RANGE ranges[2]={{D3D12_DESCRIPTOR_RANGE_TYPE_SRV,32,0,0,0},{D3D12_DESCRIPTOR_RANGE_TYPE_UAV,32,0,0,32}};D3D12_ROOT_PARAMETER params[2]{};params[0].ParameterType=D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;params[0].DescriptorTable={2,ranges};params[1].ParameterType=D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;params[1].Constants={0,0,5};D3D12_ROOT_SIGNATURE_DESC rd{};rd.NumParameters=2;rd.pParameters=params;ComPtr<ID3DBlob> blob,errors;check(D3D12SerializeRootSignature(&rd,D3D_ROOT_SIGNATURE_VERSION_1,&blob,&errors),"root serialize");check(d.device->CreateRootSignature(0,blob->GetBufferPointer(),blob->GetBufferSize(),IID_PPV_ARGS(&root)),"root");auto bytes=readFile(shader);D3D12_COMPUTE_PIPELINE_STATE_DESC pd{};pd.pRootSignature=root.Get();pd.CS={bytes.data(),bytes.size()};check(d.device->CreateComputePipelineState(&pd,IID_PPV_ARGS(&pipeline)),"pipeline");
  for(UINT i=0;i<3;i++){UINT size=Fixture::count*strides[i];outputs[i]=buffer(d.device.Get(),size,D3D12_HEAP_TYPE_DEFAULT,D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);readbacks[i]=buffer(d.device.Get(),size,D3D12_HEAP_TYPE_READBACK,D3D12_RESOURCE_STATE_COPY_DEST);D3D12_UNORDERED_ACCESS_VIEW_DESC ud{};ud.ViewDimension=D3D12_UAV_DIMENSION_BUFFER;ud.Buffer.NumElements=Fixture::count;ud.Buffer.StructureByteStride=strides[i];d.device->CreateUnorderedAccessView(outputs[i].Get(),nullptr,&ud,cpu(32+(world?8:19)+i));}
 }
 void input(UINT reg,const void* data,UINT count,UINT stride,DXGI_FORMAT format=DXGI_FORMAT_UNKNOWN) {
  UINT bytes=count*stride;auto resource=buffer(d.device.Get(),bytes,D3D12_HEAP_TYPE_UPLOAD,D3D12_RESOURCE_STATE_GENERIC_READ);void* dst=nullptr;D3D12_RANGE noRead{};check(resource->Map(0,&noRead,&dst),"upload map");std::memcpy(dst,data,bytes);resource->Unmap(0,nullptr);D3D12_SHADER_RESOURCE_VIEW_DESC sv{};sv.Format=format;sv.ViewDimension=D3D12_SRV_DIMENSION_BUFFER;sv.Shader4ComponentMapping=D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;sv.Buffer.NumElements=count;sv.Buffer.StructureByteStride=format==DXGI_FORMAT_UNKNOWN?stride:0;d.device->CreateShaderResourceView(resource.Get(),&sv,cpu(reg));inputs.push_back(std::move(resource));
 }
 void populate(const Fixture& f,bool world) {
  constexpr UINT n=Fixture::count;input(1,f.pos.data(),n*3,4,DXGI_FORMAT_R32_FLOAT);input(2,f.vel.data(),n*3,4,DXGI_FORMAT_R32_FLOAT);
  if(world){input(3,f.normals.data(),n*4,4,DXGI_FORMAT_R32_SINT);input(4,f.indices.data(),n,4,DXGI_FORMAT_R32_UINT);for(UINT i=5;i<=7;i++)input(i,f.matrix.data(),1,64);input(11,f.tc.data(),n*2,4,DXGI_FORMAT_R32_FLOAT);input(12,f.tcVel.data(),n*2,4,DXGI_FORMAT_R32_FLOAT);}
  else {
   input(3,f.tc.data(),n*2,4,DXGI_FORMAT_R32_FLOAT);input(4,f.tcVel.data(),n*2,4,DXGI_FORMAT_R32_FLOAT);input(5,f.colors.data(),n*4,4,DXGI_FORMAT_R32_UINT);input(6,f.normals.data(),n*4,4,DXGI_FORMAT_R32_SINT);for(UINT i=7;i<=12;i++)input(i,f.indices.data(),n,4,DXGI_FORMAT_R32_UINT);
   const float viewport[6]={1,-1,1,0,0,0};input(13,viewport,1,24);const float zeros[16]={};input(14,zeros,1,8);input(15,zeros,1,48);input(16,zeros,1,48);const float identity[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};input(17,identity,1,64);input(18,f.matrix.data(),1,64);
  }
  UINT base=world?13:22;input(base,f.info.data(),n,16);input(base+1,f.previousPos.data(),n,16);input(base+2,f.previousTc.data(),n,16);input(base+3,f.faces.data(),UINT(f.faces.size()),4);
 }
 std::array<std::vector<float>,3> run(const Constants& c) {
  d.begin();auto* cmd=d.commands.Get();if(ran)for(auto& out:outputs)barrier(cmd,out.Get(),D3D12_RESOURCE_STATE_COPY_SOURCE,D3D12_RESOURCE_STATE_UNORDERED_ACCESS);ID3D12DescriptorHeap* heaps[]={heap.Get()};cmd->SetDescriptorHeaps(1,heaps);cmd->SetComputeRootSignature(root.Get());cmd->SetPipelineState(pipeline.Get());cmd->SetComputeRootDescriptorTable(0,heap->GetGPUDescriptorHandleForHeapStart());cmd->SetComputeRoot32BitConstants(1,5,&c,0);cmd->Dispatch(1,1,1);
  for(UINT i=0;i<3;i++){barrier(cmd,outputs[i].Get(),D3D12_RESOURCE_STATE_UNORDERED_ACCESS,D3D12_RESOURCE_STATE_COPY_SOURCE);cmd->CopyResource(readbacks[i].Get(),outputs[i].Get());}d.finish();ran=true;std::array<std::vector<float>,3> values;
  for(UINT i=0;i<3;i++){UINT bytes=Fixture::count*strides[i];values[i].resize(bytes/4);void* mapped=nullptr;D3D12_RANGE range{0,bytes};check(readbacks[i]->Map(0,&range,&mapped),"readback map");std::memcpy(values[i].data(),mapped,bytes);D3D12_RANGE none{};readbacks[i]->Unmap(0,&none);}return values;
 }
};
int main(int argc,char** argv)try {
 require(argc==3,"Usage: gpu_probe RSPProcessCS.dxil RSPWorldCS.dxil");Device d;Fixture f;Runner raster(d,argv[1],false),world(d,argv[2],true);raster.populate(f,false);world.populate(f,true);UINT assertions=0,changedWater=0;float maxError=0;
 for(float weight:{0.f,.125f,.25f,.5f,.625f,.875f,1.f}) {
  const float previous=std::max(weight-.125f,0.f);Constants c{0,Fixture::count,previous,weight,1};auto r=raster.run(c);Constants previousC=c;previousC.current=previous;auto p=raster.run(previousC);auto w=world.run(c);c.enabled=0;auto off=world.run(c);
  for(UINT v=0;v<Fixture::count;v++)for(UINT axis=0;axis<3;axis++) {
   const UINT i=v*4+axis;const float scale=f.matrix[axis*5];float error=std::abs(r[0][i]-w[0][i]);maxError=std::max(maxError,error);require(std::isfinite(w[0][i])&&error<2.e-4f,"raster/world water positions differ");assertions++;
   require(std::abs((r[0][i]-p[0][i])-w[2][i])<2.e-4f,"world water velocity differs from raster previous weight");assertions++;
   float expected=(f.pos[v*3+axis]-f.vel[v*3+axis]*(1-weight))*scale;require(std::abs(off[0][i]-expected)<2.e-4f,"disabled path changed stock world position");assertions++;
   if(f.info[v].x==0){require(std::abs(off[0][i]-w[0][i])<1.e-6f,"ordinary geometry affected by water gate");assertions++;}
   else if(std::abs(off[0][i]-w[0][i])>.01f)changedWater++;
  }
 }
 require(changedWater>50,"fixture did not distinguish enabled water evaluation");std::cout<<"PASS: "<<assertions<<" actual compute-output assertions; modes0/1/2/3/4/5/6, recenter+coverage, nonplanar fields, outside fallback, missing field, current/previous weights, disabled gate. max_position_error="<<maxError<<" changed_water_components="<<changedWater<<". No window created.\n";return 0;
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
