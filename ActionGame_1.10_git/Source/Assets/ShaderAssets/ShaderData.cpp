#include "ShaderData.h"

using namespace std;

std::unordered_map<std::string, ShaderData::ComvsParts> ShaderData::m_pVertexShaderList;
std::unordered_map<std::string, ShaderData::CompsParts> ShaderData::m_pPixelShaderList;

const ShaderData::vsParts& ShaderData::GetVertexShader() const{
	return m_vsParts;
}

const ShaderData::psParts& ShaderData::GetPixelShader() const{
	return m_psParts;
}

void ShaderData::CreateVSshader(const char* vsfile, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int len){

	auto iter = m_pVertexShaderList.find(vsfile);
	if (iter != m_pVertexShaderList.end()) {

		// 同じ頂点シェーダがある場合それを使う
		m_vsParts.m_pVertexShader = iter->second.m_pVertexShader.Get();
		m_vsParts.m_pVertexLayout = iter->second.m_pVertexLayout.Get();
	}
	else {

		// シェーダがない場合新しく作る
		auto* device = SimepleD3D::DX11GetDevice();
		ComvsParts temp;

		//頂点シェーダー作成
		bool sts = CreateVertexShader(
			device,
			vsfile,
			"main",
			"vs_5_0",
			layout,
			len,
			temp.m_pVertexShader.GetAddressOf(),
			temp.m_pVertexLayout.GetAddressOf());
		if (!sts) {
			string log = string(vsfile) + string("  NotFile");
			MessageBoxA(nullptr, log.c_str(), nullptr, MB_OK);
		}
		else {
			m_pVertexShaderList.emplace(vsfile, temp);
			m_vsParts.m_pVertexShader = temp.m_pVertexShader.Get();
			m_vsParts.m_pVertexLayout = temp.m_pVertexLayout.Get();
		}
	}
}

void ShaderData::CreatePSshader(const char* psfile){

	auto iter = m_pPixelShaderList.find(psfile);
	if (iter != m_pPixelShaderList.end()) {

		// 同じピクセルシェーダがある場合それを使う
		m_psParts.m_pPixelShader = iter->second.m_pPixelShader.Get();
	}
	else {

		// シェーダがない場合新しく作る
		auto* device = SimepleD3D::DX11GetDevice();
		CompsParts temp;

		// ピクセルシェーダ作成
		bool sts = CreatePixelShader(
			device,
			psfile,
			"main",
			"ps_5_0",
			temp.m_pPixelShader.GetAddressOf());
		if (!sts) {
			string log = string(psfile) + string("  NotFile");
			MessageBoxA(nullptr, log.c_str(), nullptr, MB_OK);
		}
		else {
			m_pPixelShaderList.emplace(psfile, temp);
			m_psParts.m_pPixelShader = temp.m_pPixelShader.Get();
		}
	}
}

ShaderData::ShaderData(const char* vsfile,
		               D3D11_INPUT_ELEMENT_DESC layout[], 
					   unsigned int len, 
					   const char* psfile)
{
	CreateVSshader(vsfile, layout, len);
	CreatePSshader(psfile);
}
