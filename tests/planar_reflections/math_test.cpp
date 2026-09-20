#include "common/rt64_wr64_planar_reflection_math.h"

#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace RT64;
namespace {
    using V3 = std::array<double, 3>;
    using V4 = std::array<double, 4>;
    struct Matrix { float rows[4][4] = {}; };
    size_t checks = 0, cameraCases = 0, geometricSamples = 0;
    void require(bool condition, const char *message) {
        ++checks;
        if (!condition) throw std::runtime_error(message);
    }
    void near(double actual, double expected, double tolerance, const char *message) {
        require(std::isfinite(actual) && std::abs(actual - expected) <= tolerance, message);
    }
    double dot(const V3 &a, const V3 &b) {
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    }
    V3 add(const V3 &a, const V3 &b, double scale = 1) {
        return {a[0]+b[0]*scale, a[1]+b[1]*scale, a[2]+b[2]*scale};
    }
    V3 normalize(const V3 &v) {
        const double length = std::sqrt(dot(v, v));
        return {v[0]/length, v[1]/length, v[2]/length};
    }
    V3 reflectedDirection(V3 v) { v[1] = -v[1]; return v; }
    V3 reflectedPoint(V3 v, double height) { v[1] = 2*height-v[1]; return v; }
    V4 project(const float rows[4][4], const V3 &p) {
        V4 result{};
        for (size_t r = 0; r < 4; ++r) {
            result[r] = rows[r][3];
            for (size_t c = 0; c < 3; ++c) result[r] += rows[r][c] * p[c];
        }
        return result;
    }
    Matrix cameraMatrix(const V3 &eye, const V3 &right, const V3 &up, const V3 &forward) {
        constexpr double nearPlane = 2, farPlane = 8000;
        constexpr double sy = 1.4281480067421146, sx = sy * 9/16;
        const V3 axes[] = {right, up, forward, forward};
        const double scales[] = {sx, sy, farPlane/(farPlane-nearPlane), 1};
        Matrix result;
        for (size_t r = 0; r < 4; ++r) {
            for (size_t c = 0; c < 3; ++c) result.rows[r][c] = float(axes[r][c] * scales[r]);
            result.rows[r][3] = float(-dot(axes[r], eye) * scales[r]);
        }
        result.rows[2][3] += float(-nearPlane*farPlane/(farPlane-nearPlane));
        return result;
    }
    V4 independentCameraProjection(const V3 &point, const V3 &eye,
        const V3 &right, const V3 &up, const V3 &forward) {
        constexpr double nearPlane = 2, farPlane = 8000, sy = 1.4281480067421146;
        const V3 relative = add(point, eye, -1);
        const double z = dot(relative, forward);
        return {dot(relative, right)*sy*9/16, dot(relative, up)*sy,
            (z-nearPlane)*farPlane/(farPlane-nearPlane), z};
    }
    void invalid(const Wr64PlanarReflectionProjection &p) {
        require(!p.valid, "Invalid input enabled planar projection");
        for (const auto &row : p.rows) for (float value : row) require(value == 0, "Rejected projection leaked partial rows");
        for (float value : p.clipPlane) require(value == 0, "Rejected projection leaked a clipping plane");
    }
}

int main() {
    try {
        // Independently project through a mirrored pinhole camera, including
        // translated courses, changing tide, pitch and yaw. The oracle never
        // constructs a reflection matrix or reads production output rows.
        for (float planeY : {-150.f, -100.f, -40.f, 0.f, 40.f})
        for (double yaw : {-2.7, -.4, 0., .9, 2.1})
        for (double pitch : {-.5, -.12, .08})
        for (double height : {8., 100., 450.}) {
            const V3 eye = {1437.5, planeY+height, -923.25};
            const V3 right = {std::cos(yaw), 0, -std::sin(yaw)};
            const V3 up = {-std::sin(yaw)*std::sin(pitch), std::cos(pitch), -std::cos(yaw)*std::sin(pitch)};
            const V3 forward = {std::sin(yaw)*std::cos(pitch), std::sin(pitch), std::cos(yaw)*std::cos(pitch)};
            const Matrix original = cameraMatrix(eye, right, up, forward);
            const auto reflected = wr64BuildPlanarReflectionProjection(original.rows, planeY);
            require(reflected.valid, "Finite native camera rejected");
            const V3 mirrorEye = reflectedPoint(eye, planeY);
            for (double side : {-300., 0., 270.}) for (double above : {0., 10., 180.}) {
                V3 object = add(add(eye, forward, 1200), right, side);
                object[1] = planeY+above;
                const V4 actual = project(reflected.rows, object);
                const V4 expected = independentCameraProjection(object, mirrorEye,
                    reflectedDirection(right), reflectedDirection(up), reflectedDirection(forward));
                for (size_t i = 0; i < 4; ++i)
                    near(actual[i], expected[i], .0007, "Projection disagrees with independently mirrored camera");
                const V3 mirrorObject = reflectedPoint(object, planeY);
                const V4 ordinary = project(original.rows, mirrorObject);
                for (size_t i = 0; i < 4; ++i)
                    near(actual[i], ordinary[i], .0002, "Geometry reflection and camera reflection diverge");
                if (above == 0) for (size_t i = 0; i < 4; ++i)
                    near(actual[i], project(original.rows, object)[i], .0002, "Points on the water plane changed screen projection");

                near(object[1]+reflected.clipPlane[3], above, 0, "Above-water clipping distance changed with camera");
                const V3 line = add(object, mirrorEye, -1);
                const double intersectionWeight = (planeY-mirrorEye[1])/line[1];
                const V3 contact = add(mirrorEye, line, intersectionWeight);
                near(contact[1], planeY, 1e-10, "Reflected sight line does not meet water");
                const V3 incident = normalize(add(contact, eye, -1));
                const V3 outgoing = normalize(add(object, contact, -1));
                if (above != 0) for (size_t i = 0; i < 3; ++i)
                    near(reflectedDirection(incident)[i], outgoing[i], 1e-10, "Reflected ray violates equal-angle reflection");
                ++geometricSamples;
            }

            // Camera-only movement must produce the new correct capture;
            // applying an equal translation to camera, plane and object must
            // preserve the reflected image. No previous-frame cache enters.
            const V3 delta = {320, 24, -512};
            const Matrix translatedCamera = cameraMatrix(add(eye, delta), right, up, forward);
            const auto translated = wr64BuildPlanarReflectionProjection(translatedCamera.rows, planeY+float(delta[1]));
            const V3 point = {eye[0]+57, planeY+123., eye[2]+810};
            const V4 baseClip = project(reflected.rows, point);
            const V4 movedClip = project(translated.rows, add(point, delta));
            for (size_t i = 0; i < 4; ++i)
                near(movedClip[i], baseClip[i], .0005, "World/camera translation detached the reflection");
            const auto twice = wr64BuildPlanarReflectionProjection(reflected.rows, planeY);
            for (size_t r = 0; r < 4; ++r) for (size_t c = 0; c < 4; ++c)
                near(twice.rows[r][c], original.rows[r][c], .00025, "Double reflection did not recover original projection");
            ++cameraCases;
        }

        // D3D depth and horizon checks are independent of above-water clipping.
        const Matrix simple = cameraMatrix({0, 20, -100}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1});
        const auto mirror = wr64BuildPlanarReflectionProjection(simple.rows, 0);
        require(project(mirror.rows, {0, 10, -101})[3] < 0, "Behind-camera geometry passed the horizon");
        const V4 nearClip = project(mirror.rows, {0, 10, -99});
        require(nearClip[3] > 0 && nearClip[2] < 0, "Near-plane clipping direction is incorrect");
        const V4 farClip = project(mirror.rows, {0, 10, 8001});
        require(farClip[2] > farClip[3], "Far-plane clipping direction is incorrect");
        require(-1+mirror.clipPlane[3] < 0 && 1+mirror.clipPlane[3] > 0, "Below-water geometry was retained");
        const V4 above = project(mirror.rows, {0, 30, 100});
        const V4 contact = project(mirror.rows, {0, 0, 100});
        require(.5-.5*above[1]/above[3] > .5-.5*contact[1]/contact[3], "Reflection rises above its water contact in texture UV");

        // Independently execute the two real shader stages, rather than
        // reproducing the row-conversion formula. Noncentral viewports and
        // screen nudges expose both Y flips and homogeneous W translation.
        for (float width : {320.f, 426.666667f, 640.f}) for (float height : {240.f, 480.f})
        for (float shift : {-17.f, 0.f, 11.f}) {
            const float size[] = {width, height};
            const float scale[] = {width*.46f, height*.41f, .499f};
            const float translate[] = {width*.5f+shift, height*.5f-shift, .5f};
            const float screenScale[] = {.97f, 1.03f}, screenOffset[] = {.08f, -.04f};
            const auto converted = wr64BuildPlanarD3DClipProjection(simple.rows,
                scale, translate, size, screenScale, screenOffset);
            require(converted.valid, "Finite viewport conversion rejected");
            for (double x : {-53., 0., 140.}) for (double y : {-31., 5., 68.}) {
                const V3 p = {x, y, 400};
                const V4 raw = project(simple.rows, p);
                V4 screen = {raw[0]/raw[3]*scale[0]+translate[0],
                    -raw[1]/raw[3]*scale[1]+translate[1],
                    raw[2]/raw[3]*scale[2]+translate[2], raw[3]};
                screen[0] = (screen[0]-width/2)/(width/2)*raw[3];
                screen[1] = (screen[1]-height/2)/(-height/2)*raw[3];
                screen[2] *= raw[3];
                for (size_t i = 0; i < 2; ++i) screen[i] = screen[i]*screenScale[i]+screenOffset[i]*raw[3];
                const V4 actual = project(converted.rows, p);
                for (size_t i = 0; i < 4; ++i)
                    near(actual[i], screen[i], .0001, "D3D row conversion differs from native viewport/raster shaders");
            }
        }
        const float viewportScale[] = {160, 120, .5f}, viewportTranslate[] = {160, 120, .5f};
        const float framebufferSize[] = {320, 240}, screenScale[] = {1, 1}, screenOffset[] = {0, 0};
        for (float badSize : {0.f, -1.f, std::numeric_limits<float>::quiet_NaN()}) {
            const float invalidSize[] = {badSize, 240};
            require(!wr64BuildPlanarD3DClipProjection(simple.rows, viewportScale,
                viewportTranslate, invalidSize, screenScale, screenOffset).valid, "Invalid framebuffer size accepted");
        }
        require(!wr64BuildPlanarD3DClipProjection(nullptr, viewportScale,
            viewportTranslate, framebufferSize, screenScale, screenOffset).valid, "Null native matrix accepted");

        invalid(wr64BuildPlanarReflectionProjection(nullptr, 0));
        Matrix zero;
        invalid(wr64BuildPlanarReflectionProjection(zero.rows, 0));
        for (float bad : {std::numeric_limits<float>::quiet_NaN(),
            std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()}) {
            invalid(wr64BuildPlanarReflectionProjection(simple.rows, bad));
            for (size_t r = 0; r < 4; ++r) for (size_t c = 0; c < 4; ++c) {
                Matrix corrupt = simple;
                corrupt.rows[r][c] = bad;
                invalid(wr64BuildPlanarReflectionProjection(corrupt.rows, 0));
            }
        }
        Matrix overflow = simple;
        overflow.rows[0][1] = std::numeric_limits<float>::max();
        invalid(wr64BuildPlanarReflectionProjection(overflow.rows, std::numeric_limits<float>::max()));

        // Native datum reading deliberately ignores local wave distributions
        // and camera coordinates. This tests all course IDs and changing tide
        // snapshots with the recomp's actual 32-bit RAM storage convention.
        std::vector<uint8_t> ram(0x800000, 0xa5);
        auto storeHeight = [&](int32_t height) { std::memcpy(ram.data()+0x00192458, &height, sizeof(height)); };
        for (int32_t height : {-150, -100, -1, 0, 19}) for (uint32_t course = 0; course <= 8; ++course) {
            storeHeight(height);
            const auto saved = wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 1);
            require(saved.valid, "Real-course datum rejected");
            near(saved.height, height, 0, "Native integer sea level was misread");
            storeHeight(height-1);
            near(saved.height, height, 0, "Retained datum changed after live RAM advanced");
            near(wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 1).height, height-1, 0,
                "Southern tide update did not produce a new datum");
        }
        for (int32_t height : {INT32_MIN, -32769, 32768, INT32_MAX}) {
            storeHeight(height);
            require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size(), 1, 1).valid, "Invalid VTX height enabled reflections");
            for (uint32_t course = 1; course <= 8; ++course)
                require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 2, true).valid,
                    "Invalid VTX height enabled two-player reflections");
        }
        for (uint32_t course = 1; course <= 8; ++course)
        for (int32_t height : {-32768, -150, -100, -40, -1, 0, 19, 32767}) {
            storeHeight(height);
            const auto playerOne = wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 2, true);
            const auto playerTwo = wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 2, true);
            require(playerOne.valid && playerTwo.valid, "Validated native two-player course datum rejected");
            near(playerOne.height, height, 0, "Two-player native integer sea level was misread");
            near(playerTwo.height, playerOne.height, 0, "Two views did not share one world sea level");
            storeHeight(0);
            near(playerOne.height, height, 0, "Queued two-player sea level followed mutable RAM");
        }
        // Southern Island lowers sea_offset during its race. Each queued tick
        // keeps its own signed datum; both views consume that tick's same tide.
        for (int32_t height = 0; height >= -150; --height) {
            storeHeight(height);
            const auto current = wr64ReadPlanarWaterDatum(ram.data(), ram.size(), 7, 2, true);
            require(current.valid, "Southern Island two-player tide snapshot rejected");
            storeHeight(height - 1);
            const auto next = wr64ReadPlanarWaterDatum(ram.data(), ram.size(), 7, 2, true);
            near(current.height, height, 0, "Southern Island current tide snapshot mutated");
            near(next.height, height - 1, 0, "Southern Island next tide snapshot froze");
        }
        storeHeight(0);
        for (uint32_t course : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, UINT32_MAX})
        for (uint32_t players : {0u, 1u, 2u, 3u, UINT32_MAX}) for (bool scope : {false, true}) {
            const bool expected = (course <= 8 && players == 1) || (course >= 1 && course <= 8 && players == 2 && scope);
            require(wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, players, scope).valid == expected,
                "Native datum widened beyond one-player courses and validated native two-player races");
        }
        for (uint32_t course : {9u, UINT32_MAX}) require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size(), course, 1).valid,
            "Menu-preview/invalid course enabled a native plane");
        for (uint32_t players : {0u, 2u, 3u, UINT32_MAX}) require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size(), 1, players).valid,
            "Unsupported player count enabled a native plane");
        require(!wr64ReadPlanarWaterDatum(nullptr, ram.size(), 1, 1).valid, "Null RAM accepted");
        require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size()-1, 1, 1).valid, "Truncated RAM accepted");
        require(!wr64ReadPlanarWaterDatum(nullptr, ram.size(), 1, 2, true).valid, "Two-player null RAM accepted");
        require(!wr64ReadPlanarWaterDatum(ram.data(), ram.size()-1, 1, 2, true).valid, "Two-player truncated RAM accepted");

        std::cout << "PASS " << checks << " checks: " << cameraCases << " rotated/translated cameras, "
            << geometricSamples << " geometric reflection samples, D3D clipping, finite guards and all-course native tide snapshots.\n";
        return 0;
    }
    catch (const std::exception &e) { std::cerr << "FAIL after " << checks << " checks: " << e.what() << '\n'; return 1; }
}
