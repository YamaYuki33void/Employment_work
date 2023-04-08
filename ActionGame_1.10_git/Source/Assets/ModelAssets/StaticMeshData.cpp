#include "StaticMeshData.h"

void StaticMeshData::Draw(const DirectX::SimpleMath::Matrix& worldmat){

	// GPUにShaderをセットする
	auto* devcon = SimepleD3D::DX11GetDeviceContext();
	devcon->IASetInputLayout(m_pShaderData->GetVertexShader().m_pVertexLayout);
	devcon->VSSetShader(m_pShaderData->GetVertexShader().m_pVertexShader, nullptr, 0);
	devcon->PSSetShader(m_pShaderData->GetPixelShader().m_pPixelShader, nullptr, 0);

	//メッシュをワールド変換する
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::WORLD, worldmat);

	//全メッシュの描画
	for (auto&& mesh : m_MeshList) {
		mesh.second.MeshDraw();
	}
}

void StaticMeshData::Meshese_Data_Ejection(){

	//-------------------------------------------------------------//
	//						頂点データ格納                         //
	//-------------------------------------------------------------//

	for (auto&& meshdata : m_pFbxManager->GetMeshese()) {

		// サイズの取得
		int posSize = static_cast<int>(meshdata.second.GetPosList().size());
		int indexSize = static_cast<int>(meshdata.second.GetDrawIndexList().size());

		std::vector<OneMesh::Vertex> t_vertices(posSize);  // 頂点
		std::vector<unsigned int> t_indices(indexSize);                     // 面の構成情報
		OneMesh::Texture t_texture;

		for (int i = 0; i < posSize; i++) {

			// Posの取り出し
			t_vertices[i].Pos = meshdata.second.GetPosList()[i];

			// 法線の取り出し
			t_vertices[i].Normal = meshdata.second.GetNormalList()[i];

			// uv座標の取り出し
			t_vertices[i].UV = meshdata.second.GetuvList()[i];

			// 描画Indexの取り出し
			t_indices[i] = meshdata.second.GetDrawIndexList()[i];
		}

		// TexturePathの取り出し
		t_texture.path = m_TexDirectory + meshdata.second.GetTextruPath();

		// テクスチャの作成
		if (meshdata.second.GetTextruPath() != "") {

			auto* device = SimepleD3D::DX11GetDevice();
			auto* devcon = SimepleD3D::DX11GetDeviceContext();
			CreateSRVfromFile(t_texture.path.c_str(), device, devcon, &t_texture.Res, &t_texture.Sre);
		}

		// 追加
		m_MeshList.emplace(meshdata.first, OneMesh(t_vertices, t_indices, t_texture));
	}
}

StaticMeshData::StaticMeshData(const StaticMeshData& meshdata) :
	MeshData(meshdata)
{
	this->m_MeshList     = meshdata.m_MeshList;
	this->m_pShaderData  = meshdata.m_pShaderData;
	this->m_TexDirectory = meshdata.m_TexDirectory;
}

StaticMeshData::StaticMeshData(const char* myformatfile, const char* texdirectory, const ShaderData* shaderdata):
	MeshData(myformatfile,texdirectory,shaderdata)
{
	// Meshデータの取り出し
	Meshese_Data_Ejection();

	// FbxManagerの解放
	m_pFbxManager.reset();
}
