#pragma once
#include "MeshData.h"
#include "SkeletonData.h"

class SkeletalMeshData :
	public MeshData
{
public:
	void Draw(const DirectX::SimpleMath::Matrix& worldmat);

	// Getter
	class SkeletonData* GetSkeletonData();

private:
	// Meshを構成するデータを取り出す
	void Meshese_Data_Ejection()override;

private:
	// 骨管理クラス
	class SkeletonData m_SkeletonData;

public:
	SkeletalMeshData(const SkeletalMeshData& meshdata);
	SkeletalMeshData(const char* myformatfile,
		             const char* texdirectory,
					 const char* skeletonname,
		             const class ShaderData* shaderdata = ShaderAssets::GetInstance()->GetShaderData("SkeletalMeshShader"));
};

