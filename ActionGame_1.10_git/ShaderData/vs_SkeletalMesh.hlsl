//--------------------------------------------------------------------------------------
// vsstage.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main( float4 Pos         : POSITION,
				float4 Normal      : NORMAL,
				float2 Tex         : TEXCOORD,
				int4   BoneIndexA  : BONEINDEXA,
				int4   BoneIndexB  : BONEINDEXB,
				float4 BoneWeightA : BONEWEIGHTA,
				float4 BoneWeightB : BONEWEIGHTB,
				int    Index       : INDEX
)
{

	VS_OUTPUT output = (VS_OUTPUT)0;


	//頂点ブレンドの処理
	matrix comb = (matrix)0;
	
	for (int i = 0; i < 4; i++) {
		comb += (mBoneMatrix[BoneIndexA[i]] * BoneWeightA[i]);
	}
	for (int i = 0; i < 4; i++) {
		comb += (mBoneMatrix[BoneIndexB[i]] * BoneWeightB[i]);
	}
	
	output.Pos = mul(Pos, comb);
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