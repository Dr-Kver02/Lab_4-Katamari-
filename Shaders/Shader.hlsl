struct VS_IN
{
    float4 pos : POSITION;
    float4 tex : TEXCOORD;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 tex : TEXCOORD;
};

cbuffer TransformBuffer : register(b0)
{
float4x4 Transform;
}

Texture2D Texture : TEXTURE : register(t0);
SamplerState Sampler : SAMPLER : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output;

    output.pos = mul(float4(input.pos.xyz, 1), Transform);
    output.tex = input.tex;

    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float3 pixel_color = Texture.Sample(Sampler, input.tex);
    float4 col = float4(pixel_color, 0.1f);
    return col;
}
