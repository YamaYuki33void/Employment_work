#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Component/TransformComponent/TransformComponent.h"

//-----------------------------------------------------------------
//	���f���̍��������f�[�^
//-----------------------------------------------------------------
class OneBone {
public:

	// Getter
	class TransformComponent* GetTransformComponent();
	const DirectX::SimpleMath::Matrix& GetAnsMatrix()const;
	const DirectX::SimpleMath::Matrix& GetAnimationMatrix()const;
	const int GetBoneIndex()const;

	// Owner�̐ݒ�
	void SetOwner(class SkeletonData* data);
	void SetAnimationMatrix(const DirectX::SimpleMath::Matrix& mat);

private:
	// BoneTransfrom
	class TransformComponent m_BoneMatrix;

	// AnimationBone
	DirectX::SimpleMath::Matrix m_AnimationMatrix;

	// OffsetMatrix
	DirectX::SimpleMath::Matrix m_OffsetMatrix;

	// Bone�i���o�[
	int m_BoneIndex;

	// OwnerData
	class SkeletonData* m_pOwnerSkeletonData;

public:
	OneBone(const DirectX::SimpleMath::Matrix& offsetmat, const DirectX::SimpleMath::Matrix& animmat, int boneindex, class SkeletonData* data);
	~OneBone() {};
};

class SkeletonData{
public:
	// Bone�萔�o�b�t�@�f�[�^�̍X�V
	void UpdateCBufferSkeleton();

	// Getter
	class SkeletalMeshData& GetSkeletalMeshData()const;
	const std::unordered_map <std::string, class OneBone>& GetBoneList()const;
	const std::string& GetSkeletonName()const;
	class OneBone& GetBone(const std::string& bonename);

	// Owner�̐ݒ�
	void SetOwner(class SkeletalMeshData* data);
	void SetAnimationBone(const std::unordered_map <std::string, DirectX::SimpleMath::Matrix>* animbonelist);

private:
	// Bone�f�[�^�̎��o��
	void Bone_Data_Ejection();

private:
	// �{�[���s��i�[�p�̃R���X�^���g�o�b�t�@
	struct CBufferBoneMatrix {
		DirectX::XMFLOAT4X4  mBoneMatrix[100];
	};

	// Bone��Gpu�ɑ��邽�߂̒萔�o�b�t�@
	class SimpleConstantBuffer<CBufferBoneMatrix> m_CBufferSkeleton;

	// Bone���X�g
	std::unordered_map<std::string, class OneBone> m_BoneList;

	// �X�P���g���̖��O
	std::string m_SkeletonName;

	// skeletonOwner�|�C���^
	class SkeletalMeshData* m_pOwnerSkeletonMeshData;

public:
	SkeletonData(class SkeletalMeshData* data, const std::string& skeletonname);
	SkeletonData() {};
	~SkeletonData() {};
};

