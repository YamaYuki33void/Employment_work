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
			std::vector<DirectX::XMFLOAT3> m_PosList;    // ���_
			std::vector<DirectX::XMFLOAT3> m_NormalList; // �@��
			std::vector<DirectX::XMFLOAT2> m_uvList;     // UV
			std::vector<int> m_VertexIndexList;          // ���_�ԍ��C���f�b�N�X
			std::vector<int> m_DrawIndexList;            // �`��p�C���f�b�N�X
			std::string m_TextruePath;                   // �e�N�X�`���p�X

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
			//Weight�\����
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
			// �q���̖��O���X�g
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
			// Bone�̒ǉ�
			void AddBone(std::string bonename, class Skeleton::FbxOneBone onebone);

			// Weight�l�̒ǉ�
			void AddIndexWeight(std::string meshname, int vertexindex, const std::vector<Skeleton::FbxOneBone::IndexWeight>& weight);

			// Getter
			const std::unordered_map<std::string, class FbxOneBone>& GetBones()const;
			const std::unordered_map<std::string, std::unordered_map<int, std::vector<Skeleton::FbxOneBone::IndexWeight>>>& GetIndexBoneWeightList()const;

		private:
			// Bone���X�g
			std::unordered_map<std::string, class FbxOneBone>m_Bones;

			// ���_�ɑ΂���d�݃��X�g
			std::unordered_map<std::string, std::unordered_map<int, std::vector<Skeleton::FbxOneBone::IndexWeight>>> m_IndexBoneWeightList;
		
		public:
			FbxSkeletonData();
			~FbxSkeletonData();
		};

		class FbxAnimationData {
		public:
			// Animation�̒ǉ�
			void AddAnimationMatrix(std::string bonename, const std::vector<DirectX::XMFLOAT4X4>& animmatrixs);

			// RootBone���O�ݒ�
			void SetRootBoneName(const std::string& rootbonename);

			// Getter
			const std::unordered_map<std::string, std::vector<DirectX::XMFLOAT4X4>>& GetAnimationMatrix()const;
			const std::string& GetRootBoneName()const;

		private:
			// Animation�s��
			std::unordered_map<std::string, std::vector<DirectX::XMFLOAT4X4>>m_AnimationMatrix;

			// Animation�̍ő�t���[����
			int AnimationMaxFreame;

			// RootBone�̖��O
			std::string m_RootBoneName;

		public:
			FbxAnimationData();
			~FbxAnimationData();
		};
	}

	// Fbx��Ǝ��o�C�i���ɕϊ������f�[�^��ǂރN���X
	class FbxMyFormatManager {
	public:
		// �o�C�i���̓ǂݍ���
		void MeshLoad(const char* fbxmybinaly);
		void AnimationLoad(const char* animfbxmybinaly);

		// Getter
		const std::unordered_map<std::string, class Model::Mesh::FbxOneMesh>& GetMeshese()const;
		const class Model::Skeleton::FbxSkeletonData& GetSkeletonData()const;
		const class Model::Skeleton::FbxAnimationData& GetAnimationData()const;

	private:
		// ���[�h�ɂ���ēǂݍ��ݕ��@��ς���
		void LoadMesh(const char* fbxmybinaly);
		void LoadAnimation(const char* animfbxmybinaly);

	private:
		// ���b�V�����X�g
		std::unordered_map<std::string, class Model::Mesh::FbxOneMesh>m_Meshese;

		// Bone���
		class Model::Skeleton::FbxSkeletonData m_SkeletonData;

		// Animation�f�[�^
		class Model::Skeleton::FbxAnimationData m_AnimationData;

		// �t�@�C���|�C���^
		FILE* m_pFile;
	};
}
