#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Manager/FbxManager/FbxMyFormatManager.h"
#include "../ShaderAssets/ShaderAssets.h"

//--------------------------------
//	1つのメッシュを表す基底クラス
//--------------------------------
class OneMesh {
public:
	// Meshの描画
	void MeshDraw();

	// 頂点データを作成しなおす
	void RemakeVertexBuffer();

	// 頂点の長さを変えてモデルの大きさを変える
	void SetMeshScale(const DirectX::SimpleMath::Vector3& scale);

	// 頂点の長さを変えてモデルのピポット位置を変更する
	void SetPibotOffset(const DirectX::SimpleMath::Vector3& offset);

public:
	// 頂点データ
	struct Vertex {
		DirectX::SimpleMath::Vector3 Pos{};	     // 位置
		DirectX::SimpleMath::Vector3 Normal{};   // 法線
		DirectX::SimpleMath::Vector2 UV{};       // UV座標
		int	   BoneIndexA[4] = { -1,-1,-1,-1 };  // ボーンインデックス
		int	   BoneIndexB[4] = { -1,-1,-1,-1 };  // ボーンインデックス
		float  BoneWeightA[4] = { 0,0,0,0 };     // ウェイト
		float  BoneWeightB[4] = { 0,0,0,0 };     // ウェイト
		int    Index;                            // 頂点インデックス
	};

	// テクスチャデータ
	struct Texture {
		std::string path;
		ComPtr<ID3D11Resource> Res;
		ComPtr<ID3D11ShaderResourceView> Sre;
	};

private:
	std::vector<Vertex> m_pVertices; // 頂点データ
	std::vector<unsigned int>            m_Indices;  // インデックス
	struct Texture                       m_Texture;  // テクスチャ

	// バッファデータ
	SimpleVertexBuffer m_VertexBuffer;
	SimpleIndexBuffer  m_IndexBuffer;

public:
	// Meshのセット
	OneMesh(std::vector<Vertex>&       vertices,
			std::vector<unsigned int>& indices,
			struct Texture&            texture);
};

//---------------------------------
// 3Dモデルの基礎データ基底クラス
//---------------------------------

class MeshData {
public:
	// Scale設定
	void SetModelScale(const DirectX::SimpleMath::Vector3& scale);

	// Pibot位置設定
	void SetModelPibotOffset(const DirectX::SimpleMath::Vector3& offset);

	// Owner設定
	void SetOwnerComponent(class Component* comp);

	// Getter
	std::unordered_map<std::string, class OneMesh>& GetMeshList();
	class Model::FbxMyFormatManager& GetFbxManager()const;
	class Component& GetComponent()const;

private:
	// Meshを構成するデータを取り出す
	virtual void Meshese_Data_Ejection() = 0;

protected:
	// Shaderデータ
	const class ShaderData* m_pShaderData;

	// Meshデータ
	std::unordered_map<std::string, class OneMesh> m_MeshList;

	// Textureまでのディレクトリ
	std::string m_TexDirectory;

	// Fbx解析データ
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