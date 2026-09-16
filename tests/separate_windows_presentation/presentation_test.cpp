// The GPU/window objects are inert counters. Production region math, the VI
// render function and secondary resource methods are compiled without edits.
#include "wr64_diagnostic_policy.h"
#include "common/rt64_wr64_present_region.h"
#include "common/rt64_wr64_separate_windows.h"
#include "shared/rt64_video_interface.h"
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

static unsigned checks = 0;
static void check(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
static void near(float a, float b, const char *message) { check(std::abs(a - b) < 0.002f, message); }

namespace RT64 {
struct UserConfiguration {
    enum class GraphicsAPI { D3D12, Vulkan };
    enum class Filtering { Nearest, AntiAliasedPixelScaling, Linear };
};
using RenderWindow = void *;
enum class RenderFormat { UNKNOWN, B8G8R8A8_UNORM };
enum class RenderTextureLayout { COLOR_WRITE, SHADER_READ, PRESENT };
enum class RenderBarrierStage { GRAPHICS, NONE };
struct RenderTexture { unsigned id = 0; };
struct RenderSampler {};
struct RenderPipeline {};
struct RenderPipelineLayout {};
struct RenderCommandFence {};
struct RenderCommandSemaphore {};
struct RenderFramebuffer { unsigned id = 0; };
struct RenderTextureBarrier { RenderTextureBarrier(const RenderTexture *, RenderTextureLayout) {} };
struct RenderFramebufferDesc {
    const RenderTexture *texture;
    RenderFramebufferDesc(const RenderTexture **p, unsigned) : texture(*p) {}
};
struct RenderViewport {
    float x=0, y=0, width=0, height=0;
    RenderViewport()=default;
    RenderViewport(float a,float b,float c,float d):x(a),y(b),width(c),height(d){}
    bool operator==(const RenderViewport &) const = default;
};
struct RenderRect {
    int32_t left=0,top=0,right=0,bottom=0;
    RenderRect()=default;
    RenderRect(int32_t a,int32_t b,int32_t c,int32_t d):left(a),top(b),right(c),bottom(d){}
    bool operator==(const RenderRect &) const = default;
};
struct Simulation {
    bool createFails=false, resizeFails=false, resizeNeeded=false;
    uint32_t width=1280,height=720;
    unsigned creates=0,destroys=0,resizes=0,executes=0,waits=0,acquires=0;
    unsigned waitCount=0,signalCount=0,hooks=0,normalViewports=0;
    std::vector<unsigned> clears,hookTargets;
    struct Draw { unsigned target,texture; RenderViewport viewport; interop::VideoInterfaceCB constants; };
    std::vector<Draw> draws;
    std::vector<std::string> events;
} sim;
struct RenderSwapChainDesc {
    RenderWindow renderWindow=nullptr;
    RenderFormat format=RenderFormat::UNKNOWN;
    uint32_t textureCount=0,maxFrameLatency=0;
    bool enablePresentWait=false;
};
struct RenderSwapChain {
    bool empty=false,vsync=true;
    uint32_t width=1280,height=720,count=3;
    std::array<RenderTexture,3> textures{{{20},{21},{22}}};
    explicit RenderSwapChain(bool failed=false):empty(failed),width(sim.width),height(sim.height){}
    ~RenderSwapChain(){++sim.destroys;}
    bool isEmpty()const{return empty || width==0 || height==0;}
    void setVsyncEnabled(bool value){vsync=value;}
    bool needsResize()const{return sim.resizeNeeded;}
    bool resize(){++sim.resizes;sim.resizeNeeded=false;width=sim.width;height=sim.height;return !sim.resizeFails;}
    uint32_t getTextureCount()const{return count;}
    RenderTexture* getTexture(uint32_t i){return &textures.at(i);}
    uint32_t getWidth()const{return width;}
    uint32_t getHeight()const{return height;}
    bool acquireTexture(RenderCommandSemaphore*,uint32_t*i){++sim.acquires;*i=0;return !empty;}
};
struct VideoInterfaceDescriptorSet {
    const RenderTexture *texture=nullptr;
    unsigned gInput=0;
    template<class Device> VideoInterfaceDescriptorSet(const RenderSampler *,Device*){}
    void setTexture(unsigned,const RenderTexture*t,RenderTextureLayout){texture=t;}
    VideoInterfaceDescriptorSet* get(){return this;}
};
struct RenderCommandList {
    RenderFramebuffer *framebuffer=nullptr;
    VideoInterfaceDescriptorSet *descriptor=nullptr;
    RenderViewport viewport;
    interop::VideoInterfaceCB constants{};
    void begin(){sim.events.emplace_back("begin");}
    void end(){sim.events.emplace_back("end");}
    void barriers(RenderBarrierStage,RenderTextureBarrier){}
    void setFramebuffer(RenderFramebuffer*f){framebuffer=f;}
    void clearColor(){sim.clears.push_back(framebuffer->id);}
    void setViewports(RenderViewport v){viewport=v;}
    void setScissors(RenderRect){}
    void setPipeline(const RenderPipeline*){}
    void setGraphicsPipelineLayout(const RenderPipelineLayout*){}
    void setGraphicsDescriptorSet(VideoInterfaceDescriptorSet*d,unsigned){descriptor=d;}
    void setGraphicsPushConstants(unsigned,const interop::VideoInterfaceCB*c){constants=*c;}
    void setVertexBuffers(unsigned,std::nullptr_t,unsigned,std::nullptr_t){}
    void drawInstanced(unsigned,unsigned,unsigned,unsigned){
        sim.draws.push_back({framebuffer->id,descriptor->texture->id,viewport,constants});
        sim.events.emplace_back("draw");
    }
};
struct RenderDevice {
    std::unique_ptr<RenderCommandSemaphore> createCommandSemaphore(){return std::make_unique<RenderCommandSemaphore>();}
    std::unique_ptr<RenderFramebuffer> createFramebuffer(RenderFramebufferDesc d){return std::make_unique<RenderFramebuffer>(RenderFramebuffer{d.texture->id});}
};
struct RenderCommandQueue {
    std::unique_ptr<RenderSwapChain> createSwapChain(const RenderSwapChainDesc&desc){
        ++sim.creates;
        check(desc.textureCount==3 && !desc.enablePresentWait,"secondary wait policy");
        check(desc.renderWindow!=nullptr,"missing secondary HWND");
        return std::make_unique<RenderSwapChain>(sim.createFails);
    }
    void executeCommandLists(const RenderCommandList**,unsigned n,RenderCommandSemaphore**waits,unsigned nw,
        RenderCommandSemaphore**signals,unsigned ns,RenderCommandFence*){
        check(n==1,"outputs must share one command list");
        sim.waitCount=nw;sim.signalCount=ns;++sim.executes;
        for(unsigned i=0;i<nw;++i)check(waits[i]!=nullptr,"missing acquire semaphore");
        for(unsigned i=0;i<ns;++i)check(signals[i]!=nullptr,"missing draw semaphore");
        sim.events.emplace_back("submit");
    }
};
struct RenderWorker {
    std::unique_ptr<RenderCommandList> commandList=std::make_unique<RenderCommandList>();
    std::unique_ptr<RenderCommandQueue> commandQueue=std::make_unique<RenderCommandQueue>();
    std::unique_ptr<RenderCommandFence> commandFence=std::make_unique<RenderCommandFence>();
    void execute(){++sim.executes;sim.events.emplace_back("submit");}
    void wait(){++sim.waits;sim.events.emplace_back("complete");}
};
struct ShaderRecord {std::unique_ptr<RenderPipeline>pipeline=std::make_unique<RenderPipeline>();std::unique_ptr<RenderPipelineLayout>pipelineLayout=std::make_unique<RenderPipelineLayout>();};
struct ShaderLibrary {
    ShaderRecord videoInterfaceNearest,videoInterfacePixel,videoInterfaceLinear;
    struct SamplerEntry {std::unique_ptr<RenderSampler>borderBorder=std::make_unique<RenderSampler>();};
    struct Samplers {SamplerEntry nearest,linear;}samplerLibrary;
};
struct VI {hlslpp::float2 fbSize()const{return {424,240};}float gamma()const{return 1.0f;}};
inline hlslpp::float2 computeHDSize(hlslpp::float2 sd,hlslpp::float2 scale,uint32_t down){return sd*scale/float(down);}
struct VIRenderer {
    std::unique_ptr<VideoInterfaceDescriptorSet>descriptorSet;
    const RenderSampler*descriptorSetSampler=nullptr;
    struct RenderParams {
        RenderDevice*device=nullptr;RenderCommandList*commandList=nullptr;RenderTexture*texture=nullptr;
        const RenderSwapChain*swapChain=nullptr;const ShaderLibrary*shaderLibrary=nullptr;
        RenderFormat textureFormat=RenderFormat::UNKNOWN;hlslpp::float2 resolutionScale{1,1},presentationResolutionScale{1,1};
        uint32_t downsamplingScale=1,textureWidth=0,textureHeight=0;
        UserConfiguration::Filtering filtering=UserConfiguration::Filtering::Linear;
        const VI*vi=nullptr;bool removeBlackBorders=false;Wr64PresentRegion outputRegion;
    };
    void render(const RenderParams&);
    static void getViewportAndScissor(const RenderSwapChain*,const VI&,hlslpp::float2,uint32_t,bool,RenderViewport&v,RenderRect&s){
        ++sim.normalViewports;v={10,20,300,200};s={10,20,310,220};
    }
};
struct Inspector {void draw(RenderCommandList*){}}
;
using RenderHookDraw=void(RenderCommandList*,RenderFramebuffer*);
static void hook(RenderCommandList*,RenderFramebuffer*f){++sim.hooks;sim.hookTargets.push_back(f->id);sim.events.emplace_back("ui");}
inline RenderHookDraw*GetRenderHookDraw(){return &hook;}
struct PresentQueue {
    struct External {RenderDevice*device=nullptr;RenderWorker*presentGraphicsWorker=nullptr;UserConfiguration::GraphicsAPI createdGraphicsAPI=UserConfiguration::GraphicsAPI::D3D12;}ext;
    std::unique_ptr<VIRenderer>viRenderer=std::make_unique<VIRenderer>();
    std::unique_ptr<RenderSwapChain>secondarySwapChain;
    std::vector<std::unique_ptr<RenderFramebuffer>>secondaryFramebuffers;
    std::unique_ptr<RenderCommandSemaphore>secondaryAcquiredSemaphore;
    std::vector<std::unique_ptr<RenderCommandSemaphore>>secondaryDrawSemaphores;
    std::unique_ptr<VIRenderer>secondaryViRenderer;
    uintptr_t secondaryWindowHandle=0;bool secondarySwapChainValid=false,secondaryRetryBlocked=false;
    std::unique_ptr<RenderCommandSemaphore>acquiredSemaphore=std::make_unique<RenderCommandSemaphore>();
    std::vector<std::unique_ptr<RenderCommandSemaphore>>drawSemaphores;
    std::recursive_mutex inspectorMutex;std::unique_ptr<Inspector>inspector;
    bool prepareSecondaryOutput(bool);
    void releaseSecondaryOutput();
};
struct FakeCom {unsigned releases=0;void Release(){++releases;}};
struct D3D12SwapChain {
    struct Texture{FakeCom*d3d=nullptr;};std::vector<Texture>textures;
    struct Desc{uint32_t textureCount=3;}desc;FakeCom*d3d=nullptr;
    ~D3D12SwapChain();
};
#include "presentation_functions.inc"
}

using namespace RT64;
static void lifecycle() {
    sim={};RenderDevice device;RenderWorker worker;PresentQueue q;
    q.ext.device=&device;q.ext.presentGraphicsWorker=&worker;
    wr64SeparateWindowsBackend=true;wr64SecondaryWindowClosed=false;
    wr64SecondaryWindowDrawable=true;wr64SecondaryWindowHandle=uintptr_t(1);
    check(!q.prepareSecondaryOutput(false)&&sim.creates==0,"menus must not create a window output");
    check(q.prepareSecondaryOutput(true)&&sim.creates==1,"first race creates once");
    const auto*first=q.secondarySwapChain.get();
    check(!first->vsync&&q.secondaryFramebuffers.size()==3&&q.secondaryDrawSemaphores.size()==3,"secondary resources");
    for(int n=0;n<40;++n)check(q.prepareSecondaryOutput(true),"race continuation");
    check(sim.creates==1&&sim.waits==0,"normal preparation must not pace or recreate");
    check(q.prepareSecondaryOutput(false)&&q.secondarySwapChain.get()==first,"between races retain swapchain");
    check(q.prepareSecondaryOutput(true)&&q.secondarySwapChain.get()==first,"next race reuses swapchain");
    wr64SecondaryWindowDrawable=false;sim.resizeNeeded=true;
    check(q.prepareSecondaryOutput(true)&&sim.resizes==0&&sim.acquires==0,"minimized secondary is untouched");
    wr64SecondaryWindowDrawable=true;sim.width=900;sim.height=900;
    check(q.prepareSecondaryOutput(true)&&sim.resizes==1&&sim.waits==1,"restore resizes once after GPU drain");
    wr64SecondaryWindowClosed=true;
    check(!q.prepareSecondaryOutput(true)&&q.secondarySwapChain.get()==first,"close falls back without destroying output");
    wr64SecondaryWindowClosed=false;
    check(q.prepareSecondaryOutput(true)&&sim.creates==1,"reopen reuse");
    sim.resizeNeeded=true;sim.resizeFails=true;
    check(!q.prepareSecondaryOutput(true),"resize failure fallback");
    check(!q.prepareSecondaryOutput(true)&&!q.secondarySwapChain,"failed resources released safely");
    const auto attempts=sim.creates;
    for(int n=0;n<10;++n)check(!q.prepareSecondaryOutput(true),"resize failure must latch");
    check(sim.creates==attempts,"no per-frame recreate after failure");
    q.prepareSecondaryOutput(false);sim.resizeFails=false;
    check(q.prepareSecondaryOutput(true),"later race may retry");
    wr64SeparateWindowsBackend=false;
    check(!q.prepareSecondaryOutput(true)&&!q.secondarySwapChain,"backend switch tears down secondary");
    wr64SeparateWindowsBackend=true;q.ext.createdGraphicsAPI=UserConfiguration::GraphicsAPI::Vulkan;
    check(!q.prepareSecondaryOutput(true),"Vulkan cannot create secondary");
    q.ext.createdGraphicsAPI=UserConfiguration::GraphicsAPI::D3D12;sim.createFails=true;
    check(!q.prepareSecondaryOutput(true)&&q.secondaryRetryBlocked,"creation failure fallback");
    const auto failures=sim.creates;
    for(int n=0;n<10;++n)check(!q.prepareSecondaryOutput(true),"creation failure must latch");
    check(sim.creates==failures,"creation failure cannot repeat every frame");
    wr64SecondaryWindowHandle=0;
    check(!q.prepareSecondaryOutput(true)&&q.secondaryWindowHandle==0,"host teardown clears resources");
    {D3D12SwapChain failed;} // desc says3, but construction allocated nothing.
    FakeCom t0,t1,chain;
    {D3D12SwapChain partial;partial.textures={{&t0},{&t1}};partial.d3d=&chain;}
    check(t0.releases==1&&t1.releases==1&&chain.releases==1,"partial Plume teardown releases actual objects");
}

static void crops() {
    for(unsigned d3d=0;d3d<2;++d3d)for(unsigned scratch=0;scratch<2;++scratch)for(unsigned tagged=0;tagged<2;++tagged)
        check(wr64SeparateDisplayedRace(d3d,scratch,tagged)==bool(d3d&&!scratch&&tagged),"immutable race classification");
    for(uint32_t w: {1U,320U,853U,1280U,1920U,2560U,3840U,7680U})
    for(uint32_t h: {1U,240U,720U,1080U,1440U,2160U})
    for(uint32_t p=0;p<3;++p){
        auto region=wr64SeparatePresentRegion(p);auto v=wr64PresentRegionViewport(region,w,h);
        check(v.width>0&&v.height>0,"nonempty fitted region");
        check(v.x>=-0.001f&&v.y>=-0.001f&&v.x+v.width<=w+0.002f&&v.y+v.height<=h+0.002f,"fit stays inside output");
        near(v.width/v.height,region.aspect,"no aspect stretch");
        near(2*v.x+v.width,float(w),"horizontal centering");near(2*v.y+v.height,float(h),"vertical centering");
    }
    auto p1=wr64SeparatePresentRegion(1),p2=wr64SeparatePresentRegion(2);
    near(p1.right,p2.left,"no gap or overlap between crops");
    near(p1.left,0,"P1 starts at left edge");near(p2.right,1,"P2 ends at right edge");
    for(float value:{std::numeric_limits<float>::quiet_NaN(),-1.0f,0.0f}){
        auto bad=p1;bad.aspect=value;check(!wr64PresentRegionValid(bad),"invalid aspect rejected");
    }
    auto bad=p1;bad.right=1.1f;check(!wr64PresentRegionValid(bad),"out-of-bounds crop rejected");
    bad=p1;bad.right=bad.left;check(!wr64PresentRegionValid(bad),"empty crop rejected");
    check(wr64PresentRegionViewport(p1,0,1080).width==0,"zero output rejected");
}

static void outputRecording() {
    sim={};RenderDevice device;RenderWorker worker;PresentQueue q;ShaderLibrary shaders;VI vi;
    q.ext.device=&device;q.ext.presentGraphicsWorker=&worker;
    wr64SeparateWindowsBackend=true;wr64SecondaryWindowDrawable=true;wr64SecondaryWindowClosed=false;wr64SecondaryWindowHandle=1;
    check(q.prepareSecondaryOutput(true),"prepare fake output");
    q.drawSemaphores.emplace_back(std::make_unique<RenderCommandSemaphore>());
    RenderSwapChain primary;primary.width=1920;primary.height=1080;
    RenderTexture source{100},swap{1};RenderFramebuffer framebuffer{1};
    VIRenderer::RenderParams params;
    params.device=&device;params.commandList=worker.commandList.get();params.texture=&source;
    params.swapChain=&primary;params.shaderLibrary=&shaders;params.vi=&vi;
    params.textureWidth=3856;params.textureHeight=1080;
    params.resolutionScale={3840.0f/424.0f,4.5f};params.presentationResolutionScale={1,1};
    params.outputRegion=wr64SeparatePresentRegion(1);
    _putenv_s("WR64_PRESENTATION_CROP","0.1,0.2,0.3,0.4");
    recordBothOutputs(q,worker.commandList.get(),params,true,true,0,0,&swap,&framebuffer);
    check(sim.draws.size()==2&&sim.hooks==1,"one draw per player and one primary UI");
    check(sim.draws[0].target==20&&sim.draws[1].target==1&&sim.hookTargets[0]==1,"primary-only UI target");
    check(sim.draws[0].texture==100&&sim.draws[1].texture==100,"same immutable source");
    near(sim.draws[0].constants.sourceUVOffset.x,0.5f,"P2 crop overrides environment");
    near(sim.draws[1].constants.sourceUVOffset.x,0.0f,"P1 crop overrides environment");
    near(sim.draws[0].constants.sourceUVScale.x,0.5f,"P2 exact half crop");
    near(sim.draws[1].constants.sourceUVScale.x,0.5f,"P1 exact half crop");
    for(auto&draw:sim.draws){
        near(draw.constants.videoResolution.x,3840,"logical width preserved despite allocation padding");
        near(draw.constants.textureResolution.x,3856,"actual texture width preserved");
        near(draw.viewport.width/draw.viewport.height,16.0f/9.0f,"per-window aspect");
    }
    check(q.viRenderer->descriptorSet.get()!=q.secondaryViRenderer->descriptorSet.get(),"independent descriptors for same submission");
    check(sim.waitCount==2&&sim.signalCount==2&&sim.waits==1,"both images included in one completed submission");
    check(sim.events.back()=="complete","sampling finishes before return/retirement");
    sim.draws.clear();sim.clears.clear();sim.hookTargets.clear();sim.hooks=0;
    params.outputRegion={};
    recordBothOutputs(q,worker.commandList.get(),params,true,false,0,0,&swap,&framebuffer);
    check(sim.draws.size()==1&&sim.draws[0].target==1,"menus draw primary only");
    check(sim.clears.size()==2&&sim.clears[0]==20,"secondary cleared black between races");
    check(sim.hooks==1&&sim.hookTargets[0]==1,"menus UI remains primary");
    sim.draws.clear();sim.clears.clear();
    params.outputRegion=wr64SeparatePresentRegion(0);
    recordBothOutputs(q,worker.commandList.get(),params,false,true,0,0,&swap,&framebuffer);
    check(sim.draws.size()==1&&sim.waitCount==1&&sim.signalCount==1,"closed secondary records only primary");
    near(sim.draws[0].constants.sourceUVScale.x,1,"fallback shows complete composite");
    near(sim.draws[0].viewport.width/sim.draws[0].viewport.height,32.0f/9.0f,"fallback composite cannot stretch");
    sim.draws.clear();params.outputRegion.right=std::numeric_limits<float>::quiet_NaN();
    q.viRenderer->render(params);check(sim.draws.empty(),"invalid explicit crop cannot expose other player");
    q.releaseSecondaryOutput();
}

int main(){crops();lifecycle();outputRecording();std::cout<<"PASS separate presentation: "<<checks<<" checks; actual VI/secondary lifecycle and two-output recording\n";}
