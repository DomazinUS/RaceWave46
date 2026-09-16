void VSMain(uint id : SV_VertexID, out float4 position : SV_POSITION) {
    float2 p = float2((id << 1) & 2, id & 2);
    position = float4(p * float2(2, -2) + float2(-1, 1), 0, 1);
}
