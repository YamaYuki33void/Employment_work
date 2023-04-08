#include "ShaderAssets.h"

using namespace std;

void ShaderAssets::LoadInitalize(){

	{
		// StaticMeshShader
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		m_pShaderDataList.emplace("StaticMeshShader", 
			ShaderData("ShaderData/vs_StaticMesh.hlsl", 
			layout, 
			ARRAYSIZE(layout), 
			"ShaderData/ps_ColorOutput.hlsl"));
	}

	{
		// SkeletalMeshShader
		D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEXA",	0, DXGI_FORMAT_R32G32B32A32_SINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEINDEXB",	0, DXGI_FORMAT_R32G32B32A32_SINT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHTA",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONEWEIGHTB",0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "INDEX",	    0, DXGI_FORMAT_R32_SINT,	        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		m_pShaderDataList.emplace("SkeletalMeshShader",
			ShaderData("ShaderData/vs_SkeletalMesh.hlsl",
			layout,
			ARRAYSIZE(layout),
			"ShaderData/ps_ColorOutput.hlsl"));
	}
}

const ShaderData* ShaderAssets::GetShaderData(const std::string& dataname){
	
	if (m_pShaderDataList.find(dataname) != m_pShaderDataList.end()) {
		return &m_pShaderDataList.at(dataname);
	}
	else {
		string log = string(dataname) + string("  NotFile");
		MessageBoxA(nullptr, log.c_str(), nullptr, MB_OK);
		return nullptr;
	}
}
