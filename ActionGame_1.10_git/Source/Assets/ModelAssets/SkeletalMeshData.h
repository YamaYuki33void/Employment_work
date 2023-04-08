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
	// Mesh���\������f�[�^�����o��
	void Meshese_Data_Ejection()override;

private:
	// ���Ǘ��N���X
	class SkeletonData m_SkeletonData;

public:
	SkeletalMeshData(const SkeletalMeshData& meshdata);
	SkeletalMeshData(const char* myformatfile,
		             const char* texdirectory,
					 const char* skeletonname,
		             const class ShaderData* shaderdata = ShaderAssets::GetInstance()->GetShaderData("SkeletalMeshShader"));
};

