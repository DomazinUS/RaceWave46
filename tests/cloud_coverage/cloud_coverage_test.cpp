#include "common/rt64_wr64_cloud_coverage.h"
#include "native_capture_fixture.h"
#include "../rt_reflections/native_sky_archive_fixture.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
using namespace RT64;
using P = std::array<double,3>;
using Matrix = std::array<std::array<double,4>,4>;
static size_t checks=0, triangles=0, rays=0, newCoverage=0, farRejected=0;
static std::string fixture;
static void require(bool ok,const char* why) {
    ++checks;
    if(!ok) throw std::runtime_error(fixture+": "+why);
}
static double cross(const P&a,const P&b,const P&c) {
    return (b[0]-a[0])*(c[2]-a[2])-(b[2]-a[2])*(c[0]-a[0]);
}
static bool inTriangle(const P&p,const P&a,const P&b,const P&c,double epsilon=1e-5) {
    const double area=cross(a,b,c);
    const double u=cross(a,p,c)/area, v=cross(a,b,p)/area;
    return u>=-epsilon && v>=-epsilon && u+v<=1+epsilon;
}
static P point(const Wr64CloudCoverageInput&input,const Wr64CloudCoverageMesh&mesh,uint32_t index) {
    const auto&p=index<7?input.vertices[index].position:mesh.vertices[index-7].position;
    return {p[0],p[1],p[2]};
}
static bool insideNative(const P&p,const Wr64CloudCoverageInput&input,const Wr64CloudCoverageMesh&mesh) {
    for(unsigned i=1;i<=6;++i)
        if(inTriangle(p,point(input,mesh,0),point(input,mesh,i),point(input,mesh,i==6?1:i+1))) return true;
    return false;
}
static bool insideAdded(const P&p,const Wr64CloudCoverageInput&input,const Wr64CloudCoverageMesh&mesh) {
    for(size_t t=0;t<mesh.indices.size();t+=3)
        if(inTriangle(p,point(input,mesh,mesh.indices[t]),point(input,mesh,mesh.indices[t+1]),point(input,mesh,mesh.indices[t+2]))) return true;
    return false;
}
static bool sampleAddedUV(const P&p,const Wr64CloudCoverageInput&input,const Wr64CloudCoverageMesh&mesh,std::array<double,2>&uv) {
    for(size_t t=0;t<mesh.indices.size();t+=3) {
        const uint32_t a=mesh.indices[t],b=mesh.indices[t+1],c=mesh.indices[t+2];
        const auto pa=point(input,mesh,a),pb=point(input,mesh,b),pc=point(input,mesh,c);
        if(!inTriangle(p,pa,pb,pc))continue;
        const double area=cross(pa,pb,pc),u=cross(pa,p,pc)/area,v=cross(pa,pb,p)/area;
        const auto&ua=a<7?input.vertices[a].uv:mesh.vertices[a-7].uv;
        const auto&ub=b<7?input.vertices[b].uv:mesh.vertices[b-7].uv;
        const auto&uc=c<7?input.vertices[c].uv:mesh.vertices[c-7].uv;
        for(unsigned k=0;k<2;++k)uv[k]=(1-u-v)*ua[k]+u*ub[k]+v*uc[k];
        return true;
    }
    return false;
}
static std::array<double,4> multiply(const std::array<double,4>&p,const Matrix&m) {
    std::array<double,4> result{};
    for(unsigned j=0;j<4;++j)for(unsigned i=0;i<4;++i) result[j]+=p[i]*m[i][j];
    return result;
}
static Matrix inverse(Matrix matrix) {
    Matrix result{};
    for(unsigned i=0;i<4;++i) result[i][i]=1;
    for(unsigned column=0;column<4;++column) {
        unsigned pivot=column;
        for(unsigned row=column+1;row<4;++row)
            if(std::abs(matrix[row][column])>std::abs(matrix[pivot][column])) pivot=row;
        require(std::abs(matrix[pivot][column])>1e-10,"fixture matrix singular");
        std::swap(matrix[pivot],matrix[column]); std::swap(result[pivot],result[column]);
        const double divisor=matrix[column][column];
        for(unsigned j=0;j<4;++j) {matrix[column][j]/=divisor;result[column][j]/=divisor;}
        for(unsigned row=0;row<4;++row)if(row!=column) {
            const double factor=matrix[row][column];
            for(unsigned j=0;j<4;++j) {matrix[row][j]-=factor*matrix[column][j];result[row][j]-=factor*result[column][j];}
        }
    }
    return result;
}
static void checkGeometry(const Wr64CloudCoverageInput&input) {
    std::array<unsigned char,sizeof(input)> untouched{};
    std::memcpy(untouched.data(),&input,sizeof(input));
    const auto mesh=wr64BuildCloudCoverage(input);
    require(mesh.valid,"actual native fan rejected");
    require(std::memcmp(untouched.data(),&input,sizeof(input))==0,"native input prefix changed");
    require(mesh.vertices.size()==96 && mesh.indices.size()==576,"annulus work is not bounded to16x6 vertices/192triangles");
    const double orientation=cross(point(input,mesh,0),point(input,mesh,1),point(input,mesh,2));
    std::map<std::pair<uint32_t,uint32_t>,unsigned> edges;
    double area=0;
    for(size_t t=0;t<mesh.indices.size();t+=3) {
        const uint32_t a=mesh.indices[t], b=mesh.indices[t+1], c=mesh.indices[t+2];
        require(a>0 && b>0 && c>0 && a<103 && b<103 && c<103,"annulus touches native center or invalid index");
        const double value=cross(point(input,mesh,a),point(input,mesh,b),point(input,mesh,c));
        require(value*orientation>0 && std::abs(value)>1e-3,"annulus triangle is inverted or degenerate");
        area+=value*.5; ++triangles;
        for(auto e:{std::pair{a,b},std::pair{b,c},std::pair{c,a}}) {
            if(e.first>e.second)std::swap(e.first,e.second);
            ++edges[e];
        }
    }
    unsigned openEdges=0;
    for(const auto&[edge,count]:edges) {
        require(count==1 || count==2,"nonmanifold annulus edge");
        if(count==1) {
            ++openEdges;
            const bool inner=edge.first>=1 && edge.second<=6;
            const bool outer=edge.first>=97 && edge.second<=102;
            require(inner||outer,"crack between rings");
        }
    }
    require(openEdges==12,"annulus has gaps or overlaps at its two boundaries");
    for(unsigned i=1;i<=6;++i) {
        const unsigned j=i==6?1u:i+1;
        require(edges[{std::min(i,j),std::max(i,j)}]==1,"native perimeter edge not reused exactly once");
    }
    double expectedArea=0;
    for(unsigned i=0;i<6;++i) {
        const auto a=point(input,mesh,97+i), b=point(input,mesh,97+(i+1)%6);
        const auto c=point(input,mesh,1+i), d=point(input,mesh,1+(i+1)%6);
        expectedArea+=(a[0]*b[2]-a[2]*b[0]-c[0]*d[2]+c[2]*d[0])*.5;
    }
    require(std::abs(area-expectedArea)<std::abs(expectedArea)*1e-10,"annulus area differs from outer-minus-native polygon");
    for(unsigned sector=1;sector<=6;++sector)for(unsigned step=1;step<8;++step) {
        const auto a=point(input,mesh,0), b=point(input,mesh,sector), c=point(input,mesh,sector==6?1:sector+1);
        const double v=double(step)/10, w=(1-v)*.35;
        P p{a[0]*(1-v-w)+b[0]*v+c[0]*w,a[1],a[2]*(1-v-w)+b[2]*v+c[2]*w};
        require(!insideAdded(p,input,mesh),"new triangle overlaps protected native fan interior");
    }
    for(const auto&vertex:mesh.vertices) {
        double sum=0; for(float weight:vertex.weights)sum+=weight;
        require(std::abs(sum-1)<2e-6,"affine weights do not sum to one");
        for(unsigned component=0;component<3;++component) {
            double value=0;for(unsigned i=0;i<7;++i)value+=vertex.weights[i]*double(input.vertices[i].position[component]);
            require(std::abs(value-vertex.position[component])<.02,"position disagrees with native affine weights");
        }
        for(unsigned component=0;component<2;++component) {
            double value=0;for(unsigned i=0;i<7;++i)value+=vertex.weights[i]*double(input.vertices[i].uv[component]);
            require(std::abs(value-vertex.uv[component])<.001,"UV disagrees with native affine weights");
        }
        const double distance=std::hypot(double(vertex.position[0])-input.camera[0],double(vertex.position[2])-input.camera[2]);
        const auto alpha=uint8_t(std::clamp(std::round(distance*input.slope+input.intercept),0.0,255.0));
        require(vertex.alpha==alpha,"new vertex does not follow native radial alpha");
        require(vertex.position[1]==input.vertices[0].position[1],"cloud annulus leaves native plane");
    }
    for(size_t i=90;i<96;++i)require(mesh.vertices[i].alpha==0,"outer boundary retains nonzero alpha");
    const double radius=-double(input.intercept)/input.slope;
    for(unsigned step=0;step<720;++step) {
        const double angle=step*3.141592653589793/360;
        const P p{input.camera[0]+radius*.999*std::cos(angle),input.vertices[0].position[1],input.camera[2]+radius*.999*std::sin(angle)};
        require(insideNative(p,input,mesh)||insideAdded(p,input,mesh),"positive-opacity support circle has uncovered direction");
    }
}
static void checkMotion(const Wr64CloudCoverageInput&input) {
    const auto original=wr64BuildCloudCoverage(input);
    auto shifted=input;
    constexpr std::array<float,3> translation{1024,128,-512};
    for(unsigned k=0;k<3;++k) {
        shifted.camera[k]+=translation[k];
        for(auto&v:shifted.vertices)v.position[k]+=translation[k];
    }
    const auto translated=wr64BuildCloudCoverage(shifted);
    require(translated.valid && translated.indices==original.indices,"world rebase changes annulus topology");
    auto scroll=input;
    for(auto&v:scroll.vertices) {v.uv[0]+=192;v.uv[1]-=64;}
    const auto scrolled=wr64BuildCloudCoverage(scroll);
    require(scrolled.valid && scrolled.indices==original.indices,"periodic UV rebase changes topology");
    for(size_t i=0;i<original.vertices.size();++i) {
        const auto&a=original.vertices[i];const auto&b=translated.vertices[i];const auto&c=scrolled.vertices[i];
        for(unsigned k=0;k<3;++k)require(std::abs((double(b.position[k])-translation[k])-a.position[k])<.002,"world rebase changes geometric coverage");
        require(a.alpha==b.alpha,"camera/world rebase changes native radial opacity");
        for(unsigned k=0;k<2;++k) {
            const double period=k?-64:192;
            require(std::abs((double(c.uv[k])-period)-a.uv[k])<.001,"native tiled UV period/phase changes");
            double velocity=0;
            for(unsigned j=0;j<7;++j) {
                const auto&p=input.vertices[j].position;
                const double nativeVelocity=k?-.003*p[0]+.001*p[2]-2:.001*p[0]+.002*p[2]+3;
                velocity+=a.weights[j]*nativeVelocity;
            }
            const double expected=k?-.003*a.position[0]+.001*a.position[2]-2:.001*a.position[0]+.002*a.position[2]+3;
            require(std::abs(velocity-expected)<.0001,"weighted native UV velocities break affine chart motion");
        }
    }
    // Moving the camera-relative coverage boundary must not drag the texture
    // chart at fixed world locations. The retained native rim has quantized
    // UVs, so allow one native 1/32-texel step across a changed triangulation.
    auto movedCamera=input;
    movedCamera.camera[0]+=128;movedCamera.camera[2]-=256;
    // The native producer recomputes radial alpha from the active camera.
    // Keep this moving-camera fixture consistent with that actual input contract.
    for(auto&vertex:movedCamera.vertices) {
        const double distance=std::hypot(double(vertex.position[0])-movedCamera.camera[0],
            double(vertex.position[2])-movedCamera.camera[2]);
        vertex.alpha=uint8_t(std::clamp(std::round(distance*movedCamera.slope+movedCamera.intercept),0.0,255.0));
    }
    const auto moved=wr64BuildCloudCoverage(movedCamera);
    require(moved.valid && moved.indices==original.indices,"camera-relative coverage changes topology");
    unsigned overlapSamples=0;
    const double radius=-double(input.intercept)/input.slope;
    for(size_t t=0;t<original.indices.size();t+=3) {
        const auto a=point(input,original,original.indices[t]),b=point(input,original,original.indices[t+1]),c=point(input,original,original.indices[t+2]);
        const P p{(a[0]+b[0]+c[0])/3,a[1],(a[2]+b[2]+c[2])/3};
        if(std::hypot(p[0]-input.camera[0],p[2]-input.camera[2])>=radius ||
            std::hypot(p[0]-movedCamera.camera[0],p[2]-movedCamera.camera[2])>=radius)continue;
        std::array<double,2> beforeUV{},afterUV{};
        require(sampleAddedUV(p,input,original,beforeUV) && sampleAddedUV(p,movedCamera,moved,afterUV),"camera-relative positive-opacity region loses coverage");
        for(unsigned k=0;k<2;++k)require(std::abs(beforeUV[k]-afterUV[k])<=1.0/32,"camera-relative extension drags world-space cloud UV phase");
        ++overlapSamples;
    }
    require(overlapSamples>30,"insufficient camera-relative UV continuity samples");
}
static void checkView(const Wr64CloudCoverageInput&input,const Matrix&vp,double baseAspect,double authoredFov) {
    const auto mesh=wr64BuildCloudCoverage(input);
    const double radius=-double(input.intercept)/input.slope;
    for(double aspect:{4.0/3,16.0/9,21.0/9,32.0/9})for(double fovExtra:{0.0,10.0}) {
        Matrix modified=vp;
        const double yScale=std::tan(authoredFov*3.141592653589793/360)/std::tan((authoredFov+fovExtra)*3.141592653589793/360);
        for(unsigned row=0;row<4;++row) {modified[row][0]*=baseAspect/aspect*yScale;modified[row][1]*=yScale;}
        const auto inv=inverse(modified);
        for(unsigned row=0;row<30;++row)for(unsigned col=0;col<48;++col) {
            const auto unprojected=multiply({(col+.5)/48*2-1,1-(row+.5)/30*2,0,1},inv);
            if(std::abs(unprojected[3])<1e-10)continue;
            const P direction{unprojected[0]/unprojected[3]-input.camera[0],unprojected[1]/unprojected[3]-input.camera[1],unprojected[2]/unprojected[3]-input.camera[2]};
            if(direction[1]<=0)continue;
            const double t=(input.vertices[0].position[1]-input.camera[1])/direction[1];
            if(t<=0)continue;
            const P p{input.camera[0]+direction[0]*t,input.vertices[0].position[1],input.camera[2]+direction[2]*t};
            if(std::hypot(p[0]-input.camera[0],p[2]-input.camera[2])>=radius)continue;
            ++rays;
            const bool native=insideNative(p,input,mesh);
            require(native||insideAdded(p,input,mesh),"FOV/aspect ray with positive alpha misses annulus");
            if(!native)++newCoverage;
            const auto clip=multiply({p[0],p[1],p[2],1},modified);
            if(clip[2]>clip[3])++farRejected;
        }
    }
}
static void checkInvalid(Wr64CloudCoverageInput input) {
    auto rejected=[](const Wr64CloudCoverageInput&value) {
        const auto result=wr64BuildCloudCoverage(value);
        require(!result.valid && result.vertices.empty() && result.indices.empty(),"invalid input did not produce empty fallback");
    };
    for(float slope:{0.0f,.055f,-2.0f,-.000001f}) {auto bad=input;bad.slope=slope;rejected(bad);}
    for(float intercept:{0.0f,-1.0f,5000.0f}) {auto bad=input;bad.intercept=intercept;rejected(bad);}
    for(float nonfinite:{std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()}) {
        auto bad=input;bad.vertices[2].position[0]=nonfinite;rejected(bad);
        bad=input;bad.vertices[2].uv[1]=nonfinite;rejected(bad);
        bad=input;bad.camera[0]=nonfinite;rejected(bad);
        bad=input;bad.slope=nonfinite;rejected(bad);
        bad=input;bad.intercept=nonfinite;rejected(bad);
    }
    auto bad=input;bad.vertices[2]=bad.vertices[1];rejected(bad);
    bad=input;bad.vertices[0]=bad.vertices[1];rejected(bad);
    bad=input;bad.vertices[3].position[1]+=1;rejected(bad);
    bad=input;bad.vertices[2].position=input.vertices[0].position;rejected(bad);
    bad=input;bad.vertices[2].uv[0]+=1;rejected(bad);
    bad=input;bad.vertices[2].uv[1]+=2048;rejected(bad);
    for(unsigned i=0;i<7;++i) {
        bad=input;
        bad.vertices[i].alpha=uint8_t(input.vertices[i].alpha>127?input.vertices[i].alpha-8:input.vertices[i].alpha+8);
        rejected(bad);
    }
    bad=input;bad.camera[0]+=4096;rejected(bad);
    bad=input;bad.intercept-=32;rejected(bad);
}
int main() {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX|SEM_NOOPENFILEERRORBOX);
#endif
    try {
        for(const auto&capture:CloudCaptureFixtures::Captures) {
            fixture=capture.name;
            Wr64CloudCoverageInput input{};
            for(unsigned i=0;i<7;++i) {
                for(unsigned k=0;k<3;++k)input.vertices[i].position[k]=float(capture.positions[i][k]);
                for(unsigned k=0;k<2;++k)input.vertices[i].uv[k]=float(capture.texcoords[i][k]);
                input.vertices[i].alpha=uint8_t(std::round(capture.alpha[i]*255));
            }
            Matrix vp{};
            for(unsigned r=0;r<4;++r)for(unsigned c=0;c<4;++c)vp[r][c]=capture.viewProjection[r][c];
            for(unsigned k=0;k<3;++k)input.camera[k]=float(capture.camera[k]);
            input.slope=-.055f;input.intercept=450;
            checkGeometry(input);checkMotion(input);checkInvalid(input);
            checkView(input,vp,capture.projection[1][1]/capture.projection[0][0],capture.authoredFov);
        }
        fixture="Archived frame127 logged fan (alpha derived separately from native rule)";
        Wr64CloudCoverageInput archive{}; Matrix vp{};
        for(unsigned k=0;k<3;++k)archive.camera[k]=float(NativeSkyArchiveFixture::DerivedCamera[k]);
        archive.slope=NativeSkyArchiveFixture::NativeAlphaSlope;archive.intercept=NativeSkyArchiveFixture::NativeAlphaIntercept;
        for(unsigned i=0;i<7;++i) {
            for(unsigned k=0;k<3;++k)archive.vertices[i].position[k]=NativeSkyArchiveFixture::Positions[i][k];
            for(unsigned k=0;k<2;++k)archive.vertices[i].uv[k]=NativeSkyArchiveFixture::Texcoords[i][k];
            const double radius=std::hypot(double(archive.vertices[i].position[0])-archive.camera[0],double(archive.vertices[i].position[2])-archive.camera[2]);
            archive.vertices[i].alpha=uint8_t(std::clamp(std::round(radius*archive.slope+archive.intercept),0.0,255.0));
        }
        for(unsigned r=0;r<4;++r)for(unsigned c=0;c<4;++c)vp[r][c]=NativeSkyArchiveFixture::ViewProjection[r][c];
        checkGeometry(archive);checkMotion(archive);checkInvalid(archive);
        // For this log-only fixture the authored lens is not captured. This is
        // a synthetic +10 degree widening around a60 degree reference, applied
        // to the actual logged VP; five same-RAM fixtures above use real lenses.
        checkView(archive,vp,424.0/240,60);
        require(newCoverage>1000,"fixtures did not exercise missing native cloud coverage");
        std::printf("PASS six native/archive fixtures; %zu triangles; %zu positive-opacity FOV/aspect rays (%zu newly covered, %zu beyond native far plane); %zu checks.\n",triangles,rays,newCoverage,farRejected,checks);
        return 0;
    } catch(const std::exception&error) {std::fprintf(stderr,"FAIL %s\n",error.what());return 1;}
}
