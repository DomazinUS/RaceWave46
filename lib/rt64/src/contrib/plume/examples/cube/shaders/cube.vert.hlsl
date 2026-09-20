// Cube texture vertex shader
// Renders a fullscreen triangle and generates view directions for cubemap sampling

struct VSOutput {
    float4 position : SV_POSITION;
    float3 viewDir : TEXCOORD0;
};

// Push constants for view/projection
[[vk::push_constant]]
struct Constants {
    float4x4 invViewProj;
} constants;

// Fullscreen triangle - no vertex buffer needed
// Uses vertex ID to generate positions
VSOutput VSMain(uint vertexID : SV_VertexID) {
    VSOutput output;

    // Generate fullscreen triangle vertices
    // Vertex 0: (-1, -1), Vertex 1: (3, -1), Vertex 2: (-1, 3)
    float2 uv = float2((vertexID << 1) & 2, vertexID & 2);
    float2 ndc = uv * 2.0 - 1.0;

    // Flip Y for proper orientation
    ndc.y = -ndc.y;

    output.position = float4(ndc, 0.0, 1.0);

    // Transform NDC to world direction using inverse view-projection
    // Use near and far plane points to get a proper ray direction
    float4 nearPoint = mul(constants.invViewProj, float4(ndc, -1.0, 1.0));
    float4 farPoint = mul(constants.invViewProj, float4(ndc, 1.0, 1.0));

    nearPoint /= nearPoint.w;
    farPoint /= farPoint.w;

    // Ray direction from near to far plane
    output.viewDir = farPoint.xyz - nearPoint.xyz;

    return output;
}
