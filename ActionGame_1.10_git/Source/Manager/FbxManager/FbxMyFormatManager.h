#pragma once
#include <DirectXMath.h>
#include <unordered_map>
#include <string>
#include <vector>

namespace Model {

	namespace Mesh {

		class  FbxOneMesh {
		public:
			// Getter
			const std::vector<DirectX::XMFLOAT3>& GetPosList()const;
			const std::vector<DirectX::XMFLOAT3>& GetNormalList()const;
			const std::vector<DirectX::XMFLOAT2>& GetuvList()const;
			const std::vector<int>& GetVertexIndexList()const;
			const std::vector<int>& GetDrawIndexList()const;
			const std::string& GetTextruPath()const;

		private:
			std::vector<DirectX::XMFLOAT3> m_PosList;    // 頂点
			std::vector<DirectX::XMFLOAT3> m_NormalList; // 法線
			std::vector<DirectX::XMFLOAT2> m_uvList;     // UV
			std::vector<int> m_VertexIndexList;          // 頂点番号インデックス
			std::vector<int> m_DrawIndexList;            // 描画用インデックス
			std::string m_TextruePath;                   // テクスチャパス

		public:

			FbxOneMesh(const std::vector<DirectX::XMFLOAT3>& pos,
				const std::vector<DirectX::XMFLOAT3>& normal,
				const std::vector<DirectX::XMFLOAT2>& uv,
				const std::vector<int>& vertexindex,
				const std::vector<int>& drawindex,
				const std::string& texpath);

			~FbxOneMesh();
		};
	}

	namespace Skeleton {

		class FbxOneBone {
		public:
			//Weight構造体
			struct IndexWeight {
				int   BoneNunber = -1;
				float Weight = 0.0f;
			};

			// Getter
			const DirectX::XMFLOAT4X4& GetInitMatrix()const;
			const DirectX::XMFLOAT4X4& GetOffsetMatrix()const;
			const int& GetBoneNumber()const;

		private:
			DirectX::XMFLOAT4X4 m_InitMatrix;
			DirectX::XMFLOAT4X4 m_OffsetMatrix;
			int m_BoneNumber;

		private:
			// 子供の名前リスト
			std::vector<std::string>m_ChildNameList;

		public:
			FbxOneBone(const DirectX::XMFLOAT4X4& initmat, 
				       const DirectX::XMFLOAT4X4& offsetmat, 
				       int bonenumber, 
				       const std::vector<std::string>& childnames);

			~FbxOneBone() {};
		};

		class FbxSkeletonData {
		public:
			// Boneの追加
			void AddBone(std::string bonename, class Skeleton::FbxOneBone onebone);

			// Weight値の追加
			void AddIndexWeight(std::string meshname, int vertexindex, const std::vector<Skeleton::FbxOneBone::IndexWeight>& weight);

			// Getter
			const std::unordered_map<std::string, class FbxOneBone>& GetBones()const;
			const std::unordered_map<std::string, std::unordered_map<int, std::vector<Skeleton::FbxOneBone::IndexWeight>>>& GetIndexBoneWeightList()const;

		private:
			// Boneリスト
			std::unordered_map<std::string, class FbxOneBone>m_Bones;

			// 頂点に対する重みリスト
			std::unordered_map<std::string, std::unordered_map<int, std::vector<Skeleton::FbxOneBone::IndexWeight>>> m_IndexBoneWeightList;
		
		public:
			FbxSkeletonData();
			~FbxSkeletonData();
		};

		class FbxAnimationData {
		public:
			// Animationの追加
			void AddAnimationMatrix(std::string bonename, const std::vector<DirectX::XMFLOAT4X4>& animmatrixs);

			// RootBone名前設定
			void SetRootBoneName(const std::string& rootbonename);

			// Getter
			const std::unordered_map<std::string, std::vector<DirectX::XMFLOAT4X4>>& GetAnimationMatrix()const;
			const std::string& GetRootBoneName()const;

		private:
			// Animation行列
			std::unordered_map<std::string, std::vector<DirectX::XMFLOAT4X4>>m_AnimationMatrix;

			// Animationの最大フレーム数
			int AnimationMaxFreame;

			// RootBoneの名前
			std::string m_RootBoneName;

		public:
			FbxAnimationData();
			~FbxAnimationData();
		};
	}

	// Fbxを独自バイナリに変換したデータを読むクラス
	class FbxMyFormatManager {
	public:
		// バイナリの読み込み
		void MeshLoad(const char* fbxmybinaly);
		void AnimationLoad(const char* animfbxmybinaly);

		// Getter
		const std::unordered_map<std::string, class Model::Mesh::FbxOneMesh>& GetMeshese()const;
		const class Model::Skeleton::FbxSkeletonData& GetSkeletonData()const;
		const class Model::Skeleton::FbxAnimationData& GetAnimationData()const;

	private:
		// モードによって読み込み方法を変える
		void LoadMesh(const char* fbxmybinaly);
		void LoadAnimation(const char* animfbxmybinaly);

	private:
		// メッシュリスト
		std::unordered_map<std::string, class Model::Mesh::FbxOneMesh>m_Meshese;

		// Bone情報
		class Model::Skeleton::FbxSkeletonData m_SkeletonData;

		// Animationデータ
		class Model::Skeleton::FbxAnimationData m_AnimationData;

		// ファイルポインタ
		FILE* m_pFile;
	};
}
