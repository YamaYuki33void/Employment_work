//--------------------------------------------------------------------------------------
// vsstage.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main( float4 Pos         : POSITION,
				float4 Normal      : NORMAL,
				float2 Tex         : TEXCOORD
)
{

    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.Pos = Pos;
    output.Pos.r = -output.Pos.r;
    output.Pos = mul(output.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.WPos = output.Pos;
    output.Tex = Tex;

    float4 N = Normal;
    N.w = 0.0f;

    N = mul(N, World);
    N = normalize(N);

    output.Normal = N;
  
    return output;
}