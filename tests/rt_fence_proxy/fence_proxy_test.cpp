#include "common/rt64_wr64_rt_fence_proxy.h"
#include "common/rt64_wr64_rt_fence_proxy_cache.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

namespace {
    unsigned checks=0;
    void require(bool value,const char *message) {
        ++checks;
        if (!value) { std::cerr<<"FAIL "<<message<<'\n'; std::exit(1); }
    }
    using Vertex=RT64::Wr64RTFenceVertex;
    std::array<Vertex,4> quad() {
        std::array<Vertex,4> q;
        q[0].position={-40,70,175,1}; q[0].uv={0,0};
        q[1].position={-40,-25,175,1}; q[1].uv={0,76};
        q[2].position={40,-25,175,1}; q[2].uv={64,76};
        q[3].position={40,70,175,1}; q[3].uv={64,0};
        for(auto &v:q) v.shade={.8f,.6f,.4f,1};
        return q;
    }
    bool equal(const std::vector<Vertex> &a,const std::vector<Vertex> &b) {
        if(a.size()!=b.size())return false;
        for(size_t i=0;i<a.size();++i) if(a[i].position!=b[i].position || a[i].uv!=b[i].uv || a[i].shade!=b[i].shade)return false;
        return true;
    }
    bool bytesEqual(const std::vector<Vertex> &a,const std::vector<Vertex> &b) {
        return a.size()==b.size() && (a.empty() || std::memcmp(a.data(),b.data(),a.size()*sizeof(Vertex))==0);
    }
    RT64::Wr64RTFenceExpansionKey cacheKey(const std::array<Vertex,4> &q,uint32_t first=0x0D00C8C0) {
        RT64::Wr64RTFenceExpansionKey key;
        for(uint32_t i=0;i<4;++i)key.sources[i]=first+i*16;
        key.material={1,0xFC127FFF,0xFFFFF238,0xC8113078,0x00182CFF,0};
        key.quad=q;
        return key;
    }
    void cacheChecks() {
        using namespace RT64;
        Wr64RTFenceExpansionCache cache;
        const auto key=cacheKey(quad());
        Wr64RTFenceProxy reference,first,second;
        require(wr64RTAppendFenceProxy(key.quad,reference),"uncached reference expands");
        first.drawIndex=148;second.drawIndex=1048;
        require(cache.append(key,first)&&bytesEqual(first.triangles,reference.triangles),"cache miss preserves exact generated vertex bytes");
        const auto bytes=cache.retainedBytes();
        require(cache.append(key,second)&&bytesEqual(second.triangles,reference.triangles),"other-view cache hit preserves exact geometry");
        require(first.drawIndex==148&&second.drawIndex==1048,"cache never reuses the other view's draw/material index");
        require(cache.stats().hits==1&&cache.stats().expansions==1&&cache.entryCount()==1&&cache.retainedBytes()==bytes,
            "repeated view avoids expansion and retains one immutable entry");
        for(uint32_t present=0;present<12;++present) {
            Wr64RTFenceProxy repeated;
            require(cache.append(key,repeated)&&bytesEqual(repeated.triangles,reference.triangles),"later presentation reuses exact static geometry");
        }
        require(cache.stats().expansions==1,"static repeated presentations do not regenerate slices");
        auto compareChanged=[&](const Wr64RTFenceExpansionKey &changed) {
            Wr64RTFenceProxy expected,actual;
            expected.triangles.resize(3);actual.triangles=expected.triangles;
            expected.triangles[0].position[0]=actual.triangles[0].position[0]=123;
            const uint64_t misses=cache.stats().misses;
            const bool valid=wr64RTAppendFenceProxy(changed.quad,expected);
            require(cache.append(changed,actual)==valid&&bytesEqual(actual.triangles,expected.triangles),
                "changed key preserves uncached acceptance and exact output/prefix bytes");
            require(cache.stats().misses==misses+1,"source/material/vertex change cannot hit a stale entry");
        };
        auto changed=key;for(auto &v:changed.quad)v.position[0]+=.125f;compareChanged(changed);
        changed=key;for(auto &v:changed.quad)v.uv[0]+=1;compareChanged(changed);
        changed=key;changed.quad[0].shade[0]=.25f;compareChanged(changed);
        changed=key;changed.quad[0].uv[0]=-0.0f;compareChanged(changed);
        changed=key;changed.quad[0].padding[0]=1;compareChanged(changed);
        for(size_t field=0;field<key.material.size();++field) {
            changed=key;changed.material[field]^=1;compareChanged(changed);
        }
        for(size_t field=0;field<key.sources.size();++field) {
            changed=key;changed.sources[field]^=16;compareChanged(changed);
        }
        changed=key;changed.quad[0].position[0]=std::numeric_limits<float>::quiet_NaN();compareChanged(changed);
        changed=key;changed.quad[0].uv[0]=std::numeric_limits<float>::infinity();compareChanged(changed);
        changed=key;changed.quad[0].position[1]+=1;compareChanged(changed);
        Wr64RTFenceProxy full;
        full.triangles.resize(Wr64RTFenceExpansionCache::MaxDrawVertices-reference.triangles.size()+1);
        const auto fullBefore=full.triangles;
        require(!cache.append(key,full)&&bytesEqual(full.triangles,fullBefore),"cache hits retain atomic per-draw budget rejection");
        full.triangles.pop_back();
        require(cache.append(key,full)&&full.triangles.size()==Wr64RTFenceExpansionCache::MaxDrawVertices,
            "cache hit can exactly fill the original draw budget");

        Wr64RTFenceExpansionCache bounded;
        for(uint32_t entry=0;entry<Wr64RTFenceExpansionCache::MaxEntries+8;++entry) {
            auto distinct=key;distinct.sources[0]+=entry*0x100;
            Wr64RTFenceProxy output;
            require(bounded.append(distinct,output)&&bytesEqual(output.triangles,reference.triangles),"entry eviction changes no geometry bytes");
            require(bounded.entryCount()<=Wr64RTFenceExpansionCache::MaxEntries&&bounded.retainedBytes()<=Wr64RTFenceExpansionCache::MaxVertexBytes,
                "retained entry and allocation capacity budgets remain bounded");
        }
        require(bounded.stats().evictions==8,"least-recent entries are evicted at the fixed count limit");
        const auto expansions=bounded.stats().expansions;
        Wr64RTFenceProxy evicted;
        require(bounded.append(key,evicted)&&bytesEqual(evicted.triangles,reference.triangles)&&bounded.stats().expansions==expansions+1,
            "evicted input regenerates exactly rather than returning unrelated geometry");
        auto large=key;large.quad[2].uv[0]=large.quad[3].uv[0]=4096;
        Wr64RTFenceExpansionCache byteBounded;
        Wr64RTFenceProxy largeReference;
        require(wr64RTAppendFenceProxy(large.quad,largeReference),"large valid quad exercises allocation bound");
        for(uint32_t entry=0;entry<12;++entry) {
            auto distinct=large;distinct.sources[0]+=entry*0x100;
            Wr64RTFenceProxy output;
            require(byteBounded.append(distinct,output)&&bytesEqual(output.triangles,largeReference.triangles),"byte-budget eviction preserves generated bytes");
            require(byteBounded.retainedBytes()<=Wr64RTFenceExpansionCache::MaxVertexBytes,"large cache entries cannot exceed allocation capacity budget");
        }
        require(byteBounded.stats().evictions>0&&byteBounded.entryCount()<Wr64RTFenceExpansionCache::MaxEntries,
            "memory limit evicts before entry count is exhausted");
    }
}

int main(int argc,char **argv) {
    using namespace RT64;
    cacheChecks();
    auto q=quad(); const auto unchanged=q;
    Wr64RTFenceProxy proxy; proxy.drawIndex=148;
    require(wr64RTAppendFenceProxy(q,proxy),"native-shaped upright fence yields bounded transverse geometry");
    require(proxy.triangles.size()==192,"64 native S texels produce32 cross-sections,64 triangles");
    require(equal({q.begin(),q.end()},{unchanged.begin(),unchanged.end()}),"original reflection/visible vertices remain unchanged");
    for(size_t i=0;i<proxy.triangles.size();i+=6) {
        const auto &a=proxy.triangles[i],&b=proxy.triangles[i+1],&c=proxy.triangles[i+2];
        require(a.position[0]==b.position[0] && b.position[0]==c.position[0],"slices lie across the fence rather than rotating its full span");
        require(std::abs(a.position[2]-175)==2 && std::abs(c.position[2]-175)==2,"thickness is bounded to four world units");
        require(a.uv[0]==b.uv[0] && b.uv[0]==c.uv[0],"native alpha samples preserve the original S coordinate");
        require(a.uv[1]==0 && b.uv[1]==76,"native T clamp range is retained, not renormalized to texture dimensions");
        const float crossX=(b.position[1]-a.position[1])*(c.position[2]-a.position[2]);
        require(crossX!=0,"Sunny horizontal light component intersects proxy cross-sections; original constant-Z plane is parallel");
    }
    for(uint32_t first=0;first<132;first+=4) {
        const uint32_t a=0x0D00C840+first*16;
        const std::array<uint32_t,6> ids{a,a+16,a+32,a,a+32,a+48};
        const bool fence=first==8 || (first>=16&&first<=56) || first==64 || first==68 || (first>=80&&first<=120);
        require(wr64RTIsSunnyFenceQuad(1,ids)==fence,"only native rope/post sources are accepted, not cottage walls or START lattice");
        for(uint32_t course=0;course<10;++course) if(course!=1)
            require(!wr64RTIsSunnyFenceQuad(course,ids),"shared segment offsets in another course cannot generate proxies");
    }
    const std::array<uint32_t,6> ids{0x0D00C8C0,0x0D00C8D0,0x0D00C8E0,0x0D00C8C0,0x0D00C8E0,0x0D00C8F0};
    for(size_t corner=0;corner<6;++corner) for(uint32_t bad:{0u,0xffffffffu,0x0D00C840u,0x0D00C8C1u,0x0D00C900u}) {
        auto changed=ids;changed[corner]=bad;
        require(!wr64RTIsSunnyFenceQuad(1,changed),"malformed and mixed native source quads are rejected");
    }
    for(float bad:{std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()}) {
        auto broken=q;broken[0].position[0]=bad;
        const auto before=proxy.triangles;
        require(!wr64RTAppendFenceProxy(broken,proxy)&&equal(before,proxy.triangles),"invalid positions cannot partially append geometry");
        broken=q;broken[0].uv[0]=bad;
        require(!wr64RTAppendFenceProxy(broken,proxy),"invalid texture coordinates are rejected");
    }
    auto broken=q;broken[3].position[1]+=1;
    require(!wr64RTAppendFenceProxy(broken,proxy),"non-upright and distorted quads fail closed");
    broken=q;broken[2].uv[0]=broken[3].uv[0]=100000;
    require(!wr64RTAppendFenceProxy(broken,proxy),"excessive repeat count stays bounded");
    Wr64RTFenceProxy full;full.triangles.resize(24576);
    require(!wr64RTAppendFenceProxy(q,full)&&full.triangles.size()==24576,"per-draw budget does not corrupt prior output");

    if(argc>1) {
        std::ifstream stream(argv[1],std::ios::binary);
        const std::vector<uint8_t> ram((std::istreambuf_iterator<char>(stream)),{});
        require(ram.size()==0x800000,"archive has original eight-MiB RAM layout");
        auto s16=[&](uint32_t a) { require(a+1<ram.size(),"captured native vertex bounds");return int16_t((uint16_t(ram[a^3])<<8)|ram[(a+1)^3]); };
        auto word=[&](uint32_t a) { uint32_t v=0;for(unsigned j=0;j<4;++j)v=(v<<8)|ram[(a+j)^3];return v; };
        const uint32_t segment=word(0x1CE6B0+13*4)&0xffffff;
        require(segment==0x2D6800,"fixture is the documented Sunny course archive");
        const std::array<std::array<uint32_t,3>,4> draws{{{148,80,44},{150,64,8},{151,16,44},{154,8,4}}};
        size_t total=0,quads=0;
        Wr64RTFenceExpansionCache nativeCache;
        std::vector<std::pair<Wr64RTFenceExpansionKey,uint32_t>> nativeKeys;
        std::vector<Wr64RTFenceProxy> nativeReference;
        for(auto draw:draws) {
            Wr64RTFenceProxy actual;actual.drawIndex=draw[0];
            Wr64RTFenceProxy cached;cached.drawIndex=draw[0];
            for(uint32_t first=draw[1];first<draw[1]+draw[2];first+=4) {
                std::array<Vertex,4> vertices;
                for(uint32_t j=0;j<4;++j) {
                    const uint32_t a=segment+0xC840+(first+j)*16;
                    for(uint32_t axis=0;axis<3;++axis)vertices[j].position[axis]=float(s16(a+axis*2));
                    vertices[j].position[3]=1;
                    vertices[j].uv={float(s16(a+8))/32,float(s16(a+10))/32};
                    vertices[j].shade={1,1,1,1};
                }
                const bool accepted=wr64RTAppendFenceProxy(vertices,actual);
                if(!accepted) {
                    std::cerr<<"Rejected native draw "<<draw[0]<<" quad "<<first<<" prior vertices "<<actual.triangles.size()<<'\n';
                    for(const auto &v:vertices)std::cerr<<v.position[0]<<','<<v.position[1]<<','<<v.position[2]<<" UV "<<v.uv[0]<<','<<v.uv[1]<<'\n';
                }
                require(accepted,"every quad in actual native aggregated fence draw fits proxy geometry/UV guards and budget");
                auto key=cacheKey(vertices,0x0D00C840+first*16);
                require(nativeCache.append(key,cached),"complete native draw fits cached expansion path");
                nativeKeys.emplace_back(key,draw[0]);
                ++quads;
            }
            require(actual.triangles.size()<=24576,"complete actual native fence draw remains under budget without dropping late quads");
            require(bytesEqual(actual.triangles,cached.triangles),"all archived native proxy vertices match uncached bytes exactly");
            nativeReference.push_back(actual);
            total+=actual.triangles.size()/3;
            std::cout<<"Native draw "<<draw[0]<<": "<<actual.triangles.size()/6<<" slices, "<<actual.triangles.size()/3<<" triangles\n";
        }
        require(quads==25,"all25 native rope fence quads were exercised");
        for(uint32_t present=0;present<6;++present) for(const auto &reference:nativeReference) {
            Wr64RTFenceProxy otherView;otherView.drawIndex=reference.drawIndex+1000;
            for(const auto &key:nativeKeys)if(key.second==reference.drawIndex)
                require(nativeCache.append(key.first,otherView),"later view/presentation reuses every actual native fence quad");
            require(bytesEqual(reference.triangles,otherView.triangles)&&otherView.drawIndex==reference.drawIndex+1000,
                "actual native full-draw geometry is byte-identical while view metadata remains distinct");
        }
        require(nativeCache.stats().expansions==25&&nativeCache.stats().hits==150&&nativeCache.stats().evictions==0,
            "complete Sunny fence expands once and all later views/presentations reuse it without eviction");
        std::cout<<"Native complete fence: "<<quads<<" quads, "<<total<<" proxy triangles\n";
        std::cout<<"Native cache: "<<nativeCache.stats().expansions<<" expansions, "<<nativeCache.stats().hits<<" hits, "
            <<nativeCache.retainedBytes()<<" retained vertex bytes\n";
    }
    std::cout<<"PASS "<<checks<<" checks\n";
}
