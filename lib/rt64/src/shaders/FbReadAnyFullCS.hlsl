//
// RT64
//

#include "Depth.hlsli"
#include "FbCommon.hlsli"

[[vk::push_constant]] ConstantBuffer<FbCommonCB> gConstants : register(b0, space0);
#ifdef __spirv__
// Native buffers switch between 8, 16 and 32 bits; color targets can be SDR or HDR.
[[vk::image_format("unknown")]]
#endif
Buffer<uint> gNewInput : register(t1, space0);
#ifdef __spirv__
[[vk::image_format("unknown")]]
#endif
RWTexture2D<float4> gOutputChangeColor : register(u0, space1);
#ifdef __spirv__
[[vk::image_format("unknown")]]
// The unused depth binding aliases the color target. Vulkan validates both
// descriptors, so provide enough store components for either target format.
RWTexture2D<float4> gOutputChangeDepth : register(u1, space1);
#else
RWTexture2D<float> gOutputChangeDepth : register(u1, space1);
#endif
#ifdef __spirv__
[[vk::image_format("r8ui")]]
#endif
RWTexture2D<uint> gOutputChangeBoolean : register(u2, space1);

[numthreads(FB_COMMON_WORKGROUP_SIZE, FB_COMMON_WORKGROUP_SIZE, 1)]
void CSMain(uint2 coord : SV_DispatchThreadID) {
    if ((coord.x < gConstants.resolution.x) && (coord.y < gConstants.resolution.y)) {
        uint bufferIndex = coord.y * gConstants.resolution.x + coord.x;
        uint2 pixelCoord = gConstants.offset + coord.xy;
        uint swappedUint = EndianSwapUINT(gNewInput[bufferIndex], gConstants.siz);
        if (gConstants.fmt == G_IM_FMT_DEPTH) {
            const float newDepth = Depth16ToFloat(swappedUint);
            gOutputChangeDepth[pixelCoord] = newDepth;
        }
        else {
            const float4 newColor = UINTToFloat4(swappedUint, gConstants.siz, gConstants.fmt);
            gOutputChangeColor[pixelCoord] = newColor;
        }

        gOutputChangeBoolean[pixelCoord] = 1;
    }
}
