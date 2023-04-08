#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Manager/FbxManager/FbxMyFormatManager.h"
#include "../ShaderAssets/ShaderAssets.h"

//--------------------------------
//	1�̃��b�V����\�����N���X
//--------------------------------
class OneMesh {
public:
	// Mesh�̕`��
	void MeshDraw();

	// ���_�f�[�^���쐬���Ȃ���
	void RemakeVertexBuffer();

	// ���_�̒�����ς��ă��f���̑傫����ς���
	void SetMeshScale(const DirectX::SimpleMath::Vector3& scale);

	// ���_�̒�����ς��ă��f���̃s�|�b�g�ʒu��ύX����
	void SetPibotOffset(const DirectX::SimpleMath::Vector3& offset);

public:
	// ���_�f�[�^
	struct Vertex {
		DirectX::SimpleMath::Vector3 Pos{};	     // �ʒu
		DirectX::SimpleMath::Vector3 Normal{};   // �@��
		DirectX::SimpleMath::Vector2 UV{};       // UV���W
		int	   BoneIndexA[4] = { -1,-1,-1,-1 };  // �{�[���C���f�b�N�X
		int	   BoneIndexB[4] = { -1,-1,-1,-1 };  // �{�[���C���f�b�N�X
		float  BoneWeightA[4] = { 0,0,0,0 };     // �E�F�C�g
		float  BoneWeightB[4] = { 0,0,0,0 };     // �E�F�C�g
		int    Index;                            // ���_�C���f�b�N�X
	};

	// �e�N�X�`���f�[�^
	struct Texture {
		std::string path;
		ComPtr<ID3D11Resource> Res;
		ComPtr<ID3D11ShaderResourceView> Sre;
	};

private:
	std::vector<Vertex> m_pVertices; // ���_�f�[�^
	std::vector<unsigned int>            m_Indices;  // �C���f�b�N�X
	struct Texture                       m_Texture;  // �e�N�X�`��

	// �o�b�t�@�f�[�^
	SimpleVertexBuffer m_VertexBuffer;
	SimpleIndexBuffer  m_IndexBuffer;

public:
	// Mesh�̃Z�b�g
	OneMesh(std::vector<Vertex>&       vertices,
			std::vector<unsigned int>& indices,
			struct Texture&            texture);
};

//---------------------------------
// 3D���f���̊�b�f�[�^���N���X
//---------------------------------

class MeshData {
public:
	// Scale�ݒ�
	void SetModelScale(const DirectX::SimpleMath::Vector3& scale);

	// Pibot�ʒu�ݒ�
	void SetModelPibotOffset(const DirectX::SimpleMath::Vector3& offset);

	// Owner�ݒ�
	void SetOwnerComponent(class Component* comp);

	// Getter
	std::unordered_map<std::string, class OneMesh>& GetMeshList();
	class Model::FbxMyFormatManager& GetFbxManager()const;
	class Component& GetComponent()const;

private:
	// Mesh���\������f�[�^�����o��
	virtual void Meshese_Data_Ejection() = 0;

protected:
	// Shader�f�[�^
	const class ShaderData* m_pShaderData;

	// Mesh�f�[�^
	std::unordered_map<std::string, class OneMesh> m_MeshList;

	// Texture�܂ł̃f�B���N�g��
	std::string m_TexDirectory;

	// Fbx��̓f�[�^
	std::unique_ptr<class Model::FbxMyFormatManager> m_pFbxManager;

	// OwnerComponent
	class Component* m_pOwnerComponent;

public:
	MeshData(const MeshData& meshdata) {};
	MeshData(const char* myformatfile,
			 const char* texdirectory,
			 const class ShaderData* shaderdata);
	virtual~MeshData() {};
};