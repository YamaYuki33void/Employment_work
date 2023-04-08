#pragma once
#include "MeshData.h"

class StaticMeshData :
    public MeshData
{
public:
	void Draw(const DirectX::SimpleMath::Matrix& worldmat);

private:
	// Meshを構成するデータを取り出す
	void Meshese_Data_Ejection()override;

public:
	StaticMeshData(const StaticMeshData& meshdata);
	StaticMeshData(const char* myformatfile,
				   const char* texdirectory,
			       const class ShaderData* shaderdata = ShaderAssets::GetInstance()->GetShaderData("StaticMeshShader"));
};

