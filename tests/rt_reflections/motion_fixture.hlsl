// Synthetic source image/depth for the headless production-motion probe.
// The motion field itself always comes from the real native mask VS/PS.
cbuffer Fixture : register(b0) { float4 fixture; } // occluder, alpha, actor x0, actor x1
void VSMain(uint id : SV_VertexID, out float4 position : SV_POSITION) {
    float2 p = float2((id << 1) & 2, id & 2);
    position = float4(p * float2(2, -2) + float2(-1, 1), 0, 1);
}
void PSMain(float4 position : SV_POSITION, out float4 color : SV_TARGET0, out float depth : SV_DEPTH) {
    int2 p = int2(position.xy);
    bool actor = (fixture.x < 2 || fixture.x == 4) && p.x >= fixture.z && p.x < fixture.w && p.y >= 24 && p.y < 40;
    color = actor ? float4(0.95, 0.80, 0.10, fixture.y) : float4(0.04, 0.10, 0.20, fixture.y);
    depth = actor ? 0.5 : 0.9;
    if ((fixture.x == 1 || fixture.x == 3) && p.x >= 18 && p.x < 23 && p.y >= 20 && p.y < 44) {
        color = float4(0.05, 0.90, 0.30, fixture.y);
        depth = 0.2;
    }
    if (fixture.x == 4 && p.x >= 28 && p.x < 36 && p.y >= 24 && p.y < 40) {
        color = float4(.05,.90,.30,fixture.y);
        depth = .25;
    }
}
