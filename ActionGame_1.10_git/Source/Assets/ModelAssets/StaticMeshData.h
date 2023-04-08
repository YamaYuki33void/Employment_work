#pragma once
#include "MeshData.h"

class StaticMeshData :
    public MeshData
{
public:
	void Draw(const DirectX::SimpleMath::Matrix& worldmat);

private:
	// Mesh���\������f�[�^�����o��
	void Meshese_Data_Ejection()override;

public:
	StaticMeshData(const StaticMeshData& meshdata);
	StaticMeshData(const char* myformatfile,
				   const char* texdirectory,
			       const class ShaderData* shaderdata = ShaderAssets::GetInstance()->GetShaderData("StaticMeshShader"));
};

