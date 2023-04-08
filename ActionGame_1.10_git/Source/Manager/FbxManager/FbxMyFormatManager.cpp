#include "FbxMyFormatManager.h"

namespace Model {

	namespace Mesh {

		const std::vector<DirectX::XMFLOAT3>& FbxOneMesh::GetPosList() const {
			return m_PosList;
		}

		const std::vector<DirectX::XMFLOAT3>& FbxOneMesh::GetNormalList() const {
			return m_NormalList;
		}

		const std::vector<DirectX::XMFLOAT2>& FbxOneMesh::GetuvList() const {
			return m_uvList;
		}

		const std::vector<int>& FbxOneMesh::GetVertexIndexList() const{
			return m_VertexIndexList;
		}

		const std::vector<int>& FbxOneMesh::GetDrawIndexList() const{
			return m_DrawIndexList;
		}

		const std::string& FbxOneMesh::GetTextruPath() const {
			return m_TextruePath;
		}

		FbxOneMesh::FbxOneMesh(const std::vector<DirectX::XMFLOAT3>& pos, const std::vector<DirectX::XMFLOAT3>& normal, const std::vector<DirectX::XMFLOAT2>& uv, const std::vector<int>& vertexindex, const std::vector<int>& drawindex, const std::string& texpath) {

			m_PosList = pos;
			m_NormalList = normal;
			m_uvList = uv;
			m_VertexIndexList = vertexindex;
			m_DrawIndexList = drawindex;
			m_TextruePath = texpath;
		}

		FbxOneMesh::~FbxOneMesh() {
		}

	}

	namespace Skeleton {

		const DirectX::XMFLOAT4X4& FbxOneBone::GetInitMatrix() const{
			return m_InitMatrix;
		}

		const DirectX::XMFLOAT4X4& FbxOneBone::GetOffsetMatrix() const{
			return m_OffsetMatrix;
		}

		const int& FbxOneBone::GetBoneNumber() const{
			return m_BoneNumber;
		}

		FbxOneBone::FbxOneBone(const DirectX::XMFLOAT4X4& initmat, const DirectX::XMFLOAT4X4& offsetmat, int bonenumber, const std::vector<std::string>& childnames){
			
			m_InitMatrix = initmat;
			m_OffsetMatrix = offsetmat;
			m_BoneNumber = bonenumber;
			m_ChildNameList = childnames;
		}

		void FbxSkeletonData::AddBone(std::string bonename, Skeleton::FbxOneBone onebone){
			m_Bones.emplace(bonename, onebone);
		}

		void FbxSkeletonData::AddIndexWeight(std::string meshname, int vertexindex, const std::vector<Skeleton::FbxOneBone::IndexWeight>& weight){
			m_IndexBoneWeightList[meshname][vertexindex] = weight;
		}

		const std::unordered_map<std::string, class FbxOneBone>& FbxSkeletonData::GetBones() const{
			return m_Bones;
		}

		const std::unordered_map<std::string, std::unordered_map<int, std::vector<Skeleton::FbxOneBone::IndexWeight>>>& FbxSkeletonData::GetIndexBoneWeightList() const{
			return m_IndexBoneWeightList;
		}

		FbxSkeletonData::FbxSkeletonData(){
		}

		FbxSkeletonData::~FbxSkeletonData(){
		}

		void FbxAnimationData::AddAnimationMatrix(std::string bonename, const std::vector<DirectX::XMFLOAT4X4>& animmatrixs){
			m_AnimationMatrix.emplace(bonename, animmatrixs);
		}
		void FbxAnimationData::SetRootBoneName(const std::string& rootbonename){
			m_RootBoneName = rootbonename;
		}
		const std::unordered_map<std::string, std::vector<DirectX::XMFLOAT4X4>>& FbxAnimationData::GetAnimationMatrix() const{
			return m_AnimationMatrix;
		}

		const std::string& FbxAnimationData::GetRootBoneName() const{
			return m_RootBoneName;
		}

		FbxAnimationData::FbxAnimationData(){
		}

		FbxAnimationData::~FbxAnimationData(){
		}
	}

	void FbxMyFormatManager::MeshLoad(const char* fbxmybinaly){

		LoadMesh(fbxmybinaly);
	}

	void FbxMyFormatManager::AnimationLoad(const char* animfbxmybinaly){

		LoadAnimation(animfbxmybinaly);
	}

	const std::unordered_map<std::string, class Model::Mesh::FbxOneMesh>& FbxMyFormatManager::GetMeshese() const{
		return m_Meshese;
	}

	const Model::Skeleton::FbxSkeletonData& FbxMyFormatManager::GetSkeletonData() const	{
		return m_SkeletonData;
	}

	const Model::Skeleton::FbxAnimationData& FbxMyFormatManager::GetAnimationData() const{
		return m_AnimationData;
	}

	void FbxMyFormatManager::LoadMesh(const char* fbxmybinaly) {

		// ファイルを開く
		fopen_s(&m_pFile, fbxmybinaly, "rb");

		// char型の固定数値
		const int namesize = 50;

		// Meshの数を取得する
		int meshsize = 0;
		fread(&meshsize, sizeof(meshsize), 1, m_pFile);

		for (int i = 0; i < meshsize; i++) {

			std::string m_MeshName;                      // メッシュの名前
			std::vector<DirectX::XMFLOAT3> m_PosList;    // 頂点
			std::vector<DirectX::XMFLOAT3> m_NormalList; // 法線
			std::vector<DirectX::XMFLOAT2> m_uvList;     // UV
			std::vector<int> m_VertexIndexList;          // 頂点番号インデックス
			std::vector<int> m_DrawIndexList;            // 描画用インデックス
			std::string m_TextruePath;                   // テクスチャパス

			{
				// Meshの名前の取得
				char meshname[namesize];
				fread(&meshname[0], sizeof(meshname[0]), namesize, m_pFile);
				m_MeshName = meshname;
			}

			{
				// Posの取得
				int possize = 0;
				fread(&possize, sizeof(possize), 1, m_pFile);
				for (int i = 0; i < possize; i++) {
					m_PosList.emplace_back();
				}
				fread(&m_PosList[0], sizeof(m_PosList[0]), possize, m_pFile);
			}

			{
				// Normalの取得
				int normalsize = 0;
				fread(&normalsize, sizeof(normalsize), 1, m_pFile);
				for (int i = 0; i < normalsize; i++) {
					m_NormalList.emplace_back();
				}
				fread(&m_NormalList[0], sizeof(m_NormalList[0]), normalsize, m_pFile);
			}

			{
				// uvの取得
				int uvsize = 0;
				fread(&uvsize, sizeof(uvsize), 1, m_pFile);
				for (int i = 0; i < uvsize; i++) {
					m_uvList.emplace_back();
				}
				fread(&m_uvList[0], sizeof(m_uvList[0]), uvsize, m_pFile);
			}

			{
				// 頂点インデックスの取得
				int vertexindexsize = 0;
				fread(&vertexindexsize, sizeof(vertexindexsize), 1, m_pFile);
				for (int i = 0; i < vertexindexsize; i++) {
					m_VertexIndexList.emplace_back();
				}
				fread(&m_VertexIndexList[0], sizeof(m_VertexIndexList[0]), vertexindexsize, m_pFile);
			}

			{
				// 描画インデックスの取得
				int drawindexsize = 0;
				fread(&drawindexsize, sizeof(drawindexsize), 1, m_pFile);
				for (int i = 0; i < drawindexsize; i++) {
					m_DrawIndexList.emplace_back();
				}
				fread(&m_DrawIndexList[0], sizeof(m_DrawIndexList[0]), drawindexsize, m_pFile);
			}

			{
				// テクスチャパスの取得
				char texpathname[namesize];
				fread(&texpathname[0], sizeof(texpathname[0]), namesize, m_pFile);
				m_TextruePath = texpathname;
			}

			// 追加
			m_Meshese.emplace(m_MeshName, Model::Mesh::FbxOneMesh(m_PosList, m_NormalList, m_uvList, m_VertexIndexList, m_DrawIndexList, m_TextruePath));
		}

		// Boneの数を取得する
		int BoneSize = 0;
		fread(&BoneSize, sizeof(BoneSize), 1, m_pFile);

		{
			for (int i = 0; i < BoneSize; i++) {

				char bonename[namesize];
				DirectX::XMFLOAT4X4 initmat;
				DirectX::XMFLOAT4X4 offsetmat;
				int bonenumber;

				fread(&bonename[0], sizeof(bonename[0]), namesize, m_pFile);
				fread(&initmat, sizeof(initmat), 1, m_pFile);
				fread(&offsetmat, sizeof(offsetmat), 1, m_pFile);
				fread(&bonenumber, sizeof(bonenumber), 1, m_pFile);


				// 子供のボーンの数を取得
				int ChildSize = 0;
				fread(&ChildSize, sizeof(ChildSize), 1, m_pFile);
				std::vector<std::string>ChildNametemp;
				for (int i = 0; i < ChildSize; i++) {
					char ChildName[namesize];
					fread(&ChildName[0], sizeof(ChildName[0]), namesize, m_pFile);
					ChildNametemp.emplace_back(ChildName);
				}

				m_SkeletonData.AddBone(bonename, Model::Skeleton::FbxOneBone(initmat, offsetmat, bonenumber, ChildNametemp));
			}
		}

		{
			// Meshの数を取得
			int meshize = 0;
			fread(&meshize, sizeof(meshize), 1, m_pFile);

			for (int i = 0; i < meshize; i++) {

				// weithtのMeshの名前を取得
				char meshname[namesize];
				fread(&meshname[0], sizeof(meshname[0]), namesize, m_pFile);

				// 頂点番号の数値を取得する
				int meshVertexindexSize = 0;
				fread(&meshVertexindexSize, sizeof(meshVertexindexSize), 1, m_pFile);

				// 頂点数分回す
				for (int i = 0; i < meshVertexindexSize; i++) {

					// 影響する頂点の番号を取得する
					int VertexIndex = 0;
					fread(&VertexIndex, sizeof(VertexIndex), 1, m_pFile);

					// 重みの最大数を取得
					int VertexIndexSize = 0;
					fread(&VertexIndexSize, sizeof(VertexIndexSize), 1, m_pFile);
					std::vector<Model::Skeleton::FbxOneBone::IndexWeight> weighttemp;
					for (int i = 0; i < VertexIndexSize; i++) {
						weighttemp.emplace_back();
					}

					fread(&weighttemp[0], sizeof(weighttemp[0]), VertexIndexSize, m_pFile);

					// 追加
					m_SkeletonData.AddIndexWeight(meshname, VertexIndex, weighttemp);
				}
			}

		}

		// ファイルを閉じる
		fclose(m_pFile);
	}

	void FbxMyFormatManager::LoadAnimation(const char* animfbxmybinaly){

		// ファイルを開く
		fopen_s(&m_pFile, animfbxmybinaly, "rb");

		// char型の固定数値
		const int namesize = 50;

		// Boneの最大数を取得する
		int BoneSize = 0;
		fread(&BoneSize, sizeof(BoneSize), 1, m_pFile);

		// Animaionの最大フレーム数を取得する
		int AnimFreamSize = 0;
		fread(&AnimFreamSize, sizeof(AnimFreamSize), 1, m_pFile);

		// RootBoneの名前を取得する
		char rootbonename[namesize];
		fread(&rootbonename[0], sizeof(rootbonename[0]), namesize, m_pFile);
		m_AnimationData.SetRootBoneName(rootbonename);

		// Animationのフレーム数だけデータを取り出す
		for (int i = 0; i < BoneSize; i++) {

			// AnimationのBoneの名前を取得する
			char bonename[namesize];
			fread(&bonename[0], sizeof(bonename[0]), namesize, m_pFile);

			std::vector<DirectX::XMFLOAT4X4> animmatrixtemp;
			for (int i = 0; i < AnimFreamSize; i++) {
				animmatrixtemp.emplace_back();
			}

			// フレームの数だけ行列を取り出す
			fread(&animmatrixtemp[0], sizeof(animmatrixtemp[0]), AnimFreamSize, m_pFile);

			// 追加
			m_AnimationData.AddAnimationMatrix(bonename, animmatrixtemp);
		}

		fclose(m_pFile);
	}
}

