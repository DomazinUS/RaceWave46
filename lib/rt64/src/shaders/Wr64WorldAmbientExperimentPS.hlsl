// Parked AO research shader. Deliberately absent from the production shader
// build and PSO selection: disabling AO at runtime does not remove its compiled
// ray-query footprint from a shared shadow shader. Offline fixtures may compile
// this source explicitly; normal shadows use Wr64WorldShadowPS.hlsl.
// Surface effects for explicitly selected native physical surfaces.
// Native texture, fog, alpha/coverage, depth and blending stay in RasterPS.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64WorldBasePSMain
#include "RasterPS.hlsl"
#undef PSMain

#include "Wr64WaterParams.hlsli"
#include "shared/rt64_wr64_rt_ao.h"
RaytracingAccelerationStructure wr64Scene : register(t26, space0);
ByteAddressBuffer wr64Positions : register(t27, space0);
ByteAddressBuffer wr64Texcoords : register(t30, space0);
ByteAddressBuffer wr64Colors : register(t31, space0);
ByteAddressBuffer wr64Indices : register(t35, space0);
StructuredBuffer<uint4> wr64Geometry : register(t40, space0);
#include "Wr64WaterMaterial.hlsli"
#include "Wr64WaterShadow.hlsli"
#include "Wr64AmbientOcclusion.hlsli"

void PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    float3 worldPosition : TEXCOORD1, bool frontFace : SV_IsFrontFace,
    uint primitiveId : SV_PrimitiveID,
    out float4 pixelColor : SV_TARGET0, out float4 pixelAlpha : SV_TARGET1) {
    RenderParams rp = getRenderParams();
    if (!RasterPS(rp, position, uv, smoothColor, flatColor,
        frontFace, pixelColor, pixelAlpha)) discard;
    const bool aoOnlyReceiver = gConstants.padding.x == WR64_AO_ONLY_RECEIVER;
    // Actor/structure AO admission does not extend the directional-shadow
    // receiver set, including its diagnostic view and disabled-AO fallback.
    if (aoOnlyReceiver && (!wr64AOActive() || wr64DebugView == 5)) return;
    if (wr64Enabled == 0 || (wr64ShadowOptions.x != 1 && !wr64AOActive())) return;

    // Apply visibility to the surface contribution, not atmospheric fog.
    // These are the native standard-fog and unforced opaque pass-through
    // blender paths. Other materials retain their original output until an
    // equivalent pre-blender attenuation has been established for them.
    OtherMode om = {rp.omL, rp.omH};
    const uint blenderInputs = om.blenderInputs();
    const bool nativeFog = om.cycleType() == G_CYC_2CYCLE && !om.forceBlend() &&
        Blender::usesStandardFogCycle(blenderInputs, 0) &&
        Blender::decodeInputP(blenderInputs, true) == Blender::PM_CC_OR_BLENDER;
    const bool nativeOpaque = om.cycleType() == G_CYC_1CYCLE && !om.forceBlend() &&
        Blender::decodeInputP(blenderInputs, false) == Blender::PM_CC_OR_BLENDER;
    const uint instanceIndex = instanceRenderIndices[gConstants.renderIndex].instanceIndex;
    if ((!nativeFog && !nativeOpaque) || renderBlenderApproximation(rp.flags) != 0 ||
        instanceRenderIndices[gConstants.renderIndex].highlightColor != 0 || FrParams.viewUbershaders) return;
    float3 fogContribution = 0;
    if (nativeFog) {
        // RasterPS always uses interpolated alpha even for flat RGB shading.
        // Its optional alpha-dither block is disabled, so no extra perturbation
        // belongs here. Restrict the correction to finite native fog inputs.
        const float fogAmount = smoothColor.a;
        const float3 fogColor = instanceRDPParams[instanceIndex].fogColor.rgb;
        if (!isfinite(fogAmount) || fogAmount < 0 || fogAmount > 1 ||
            !all(isfinite(fogColor)) || any(fogColor < 0) || any(fogColor > 1)) return;
        if (fogAmount == 1 && wr64DebugView != 5 && wr64DebugView != 6) return;
        fogContribution = fogAmount * fogColor;
    }

    // Selected draws retain their original index range (the renderer excludes
    // vertex-test rewrites), so SV_PrimitiveID identifies the exact AS face.
    // Derivatives after native discard/fog exits were not reliable normals.
    // Their tiny errors also flipped the bias side on light-tangent walls.
    const uint receiverFace = instanceRenderIndices[gConstants.renderIndex].faceIndicesStart + primitiveId * 3;
    const uint3 indices = wr64Indices.Load3(receiverFace * 4);
    const float3 a = asfloat(wr64Positions.Load3(indices.x * 16));
    const float3 b = asfloat(wr64Positions.Load3(indices.y * 16));
    const float3 c = asfloat(wr64Positions.Load3(indices.z * 16));
    if (!all(isfinite(a)) || !all(isfinite(b)) || !all(isfinite(c)) ||
        !all(isfinite(worldPosition))) return;
    precise float3 edge1 = b - a;
    precise float3 edge2 = c - a;
    float3 normal = cross(edge1, edge2);
    float lengthSquared = dot(normal, normal);
    if (!all(isfinite(normal)) || !isfinite(lengthSquared) || lengthSquared < 1e-12f) return;
    normal *= rsqrt(lengthSquared);
    // Bias toward the light, independent of camera side or triangle winding,
    // so an ordinary receiving face does not immediately hit itself.
    if (dot(normal, wr64ShadowLight.xyz) < 0) normal = -normal;
    // Put the perspective-interpolated receiver back on that same geometric
    // plane before applying the existing bias. This removes interpolation
    // drift at distant walls without increasing the gap from nearby casters.
    precise float planeDistance = dot(worldPosition - a, normal);
    precise float3 receiverPosition = worldPosition - planeDistance * normal;
    // The ambient hemisphere belongs to the visible side of a two-sided
    // native card; it must not change with the directional-light preset.
    float3 ambientNormal = normal;
    if (all(isfinite(wr64Camera.xyz)) && dot(ambientNormal, wr64Camera.xyz - receiverPosition) < 0)
        ambientNormal = -ambientNormal;
    const float ambientOcclusion = wr64AmbientOcclusion(receiverPosition, ambientNormal,
        gConstants.renderIndex, receiverFace);
    if (wr64DebugView == 6) {
        pixelColor.rgb = 1 - ambientOcclusion;
        pixelAlpha.a = 1;
        return;
    }
    float shadowCoverage = 0;
    if (!aoOnlyReceiver)
        shadowCoverage = wr64WorldShadowCoverage(receiverPosition, normal,
            gConstants.renderIndex, receiverFace);
    if (wr64DebugView == 5) {
        pixelColor.rgb = 1 - shadowCoverage;
        pixelAlpha.a = 1;
        return;
    }
    // The original material has already baked/vertex lighting. This first
    // experiment mildly attenuates its unfogged contribution; it does not
    // pretend to reconstruct separate physical ambient and direct radiance.
    const float transmission = wr64WaterShadowTransmission(shadowCoverage) *
        wr64AOTransmission(ambientOcclusion);
    if (transmission < 1) {
        pixelColor.rgb = transmission * pixelColor.rgb + (1 - transmission) * fogContribution;
    }
}
