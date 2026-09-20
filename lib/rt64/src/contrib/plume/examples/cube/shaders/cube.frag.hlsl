// Cube texture fragment shader
// Samples from a cubemap texture

[[vk::binding(0, 0)]] TextureCube<float4> cubeTexture : register(t0);
[[vk::binding(1, 0)]] SamplerState cubeSampler : register(s1);

struct PSInput {
    float4 position : SV_POSITION;
    float3 viewDir : TEXCOORD0;
};

float4 PSMain(PSInput input) : SV_TARGET {
    // Normalize the view direction and sample the cubemap
    float3 dir = normalize(input.viewDir);
    return cubeTexture.Sample(cubeSampler, dir);
}
