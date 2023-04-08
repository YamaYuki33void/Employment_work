#include "StaticMeshData.h"

void StaticMeshData::Draw(const DirectX::SimpleMath::Matrix& worldmat){

	// GPU��Shader���Z�b�g����
	auto* devcon = SimepleD3D::DX11GetDeviceContext();
	devcon->IASetInputLayout(m_pShaderData->GetVertexShader().m_pVertexLayout);
	devcon->VSSetShader(m_pShaderData->GetVertexShader().m_pVertexShader, nullptr, 0);
	devcon->PSSetShader(m_pShaderData->GetPixelShader().m_pPixelShader, nullptr, 0);

	//���b�V�������[���h�ϊ�����
	WorldTransformation::GetInstance()->SetTransform(WorldTransformation::TYPE::WORLD, worldmat);

	//�S���b�V���̕`��
	for (auto&& mesh : m_MeshList) {
		mesh.second.MeshDraw();
	}
}

void StaticMeshData::Meshese_Data_Ejection(){

	//-------------------------------------------------------------//
	//						���_�f�[�^�i�[                         //
	//-------------------------------------------------------------//

	for (auto&& meshdata : m_pFbxManager->GetMeshese()) {

		// �T�C�Y�̎擾
		int posSize = static_cast<int>(meshdata.second.GetPosList().size());
		int indexSize = static_cast<int>(meshdata.second.GetDrawIndexList().size());

		std::vector<OneMesh::Vertex> t_vertices(posSize);  // ���_
		std::vector<unsigned int> t_indices(indexSize);                     // �ʂ̍\�����
		OneMesh::Texture t_texture;

		for (int i = 0; i < posSize; i++) {

			// Pos�̎��o��
			t_vertices[i].Pos = meshdata.second.GetPosList()[i];

			// �@���̎��o��
			t_vertices[i].Normal = meshdata.second.GetNormalList()[i];

			// uv���W�̎��o��
			t_vertices[i].UV = meshdata.second.GetuvList()[i];

			// �`��Index�̎��o��
			t_indices[i] = meshdata.second.GetDrawIndexList()[i];
		}

		// TexturePath�̎��o��
		t_texture.path = m_TexDirectory + meshdata.second.GetTextruPath();

		// �e�N�X�`���̍쐬
		if (meshdata.second.GetTextruPath() != "") {

			auto* device = SimepleD3D::DX11GetDevice();
			auto* devcon = SimepleD3D::DX11GetDeviceContext();
			CreateSRVfromFile(t_texture.path.c_str(), device, devcon, &t_texture.Res, &t_texture.Sre);
		}

		// �ǉ�
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
	// Mesh�f�[�^�̎��o��
	Meshese_Data_Ejection();

	// FbxManager�̉��
	m_pFbxManager.reset();
}
