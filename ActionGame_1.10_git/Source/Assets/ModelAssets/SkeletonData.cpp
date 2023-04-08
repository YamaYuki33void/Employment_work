#include "SkeletonData.h"
#include "../ModelAssets/SkeletalMeshData.h"
#include "../../Game/Component/ComponentList.h"

TransformComponent* OneBone::GetTransformComponent(){

	// �E��n�̍s�������n�ɕϊ�����
	DirectX::SimpleMath::Matrix leftanimmat = m_AnimationMatrix.LeftHand();

	// Model�s������o��
	DirectX::SimpleMath::Matrix modelmat = m_pOwnerSkeletonData->GetSkeletalMeshData().GetComponent().GetTransformComponent()->GetWorldMatrix();
	
	// �{�[���̃��[���h�s����쐬����
	m_BoneMatrix.SetMatrix(leftanimmat * modelmat);

	return &m_BoneMatrix;
}

const DirectX::SimpleMath::Matrix& OneBone::GetAnsMatrix() const{
	return m_OffsetMatrix * m_AnimationMatrix;
}

const DirectX::SimpleMath::Matrix& OneBone::GetAnimationMatrix() const{
	return m_AnimationMatrix;
}

const int OneBone::GetBoneIndex() const{
	return m_BoneIndex;
}

void OneBone::SetOwner(SkeletonData* data){
	m_pOwnerSkeletonData = data;
}

void OneBone::SetAnimationMatrix(const DirectX::SimpleMath::Matrix& mat){
	m_AnimationMatrix = mat;
}

OneBone::OneBone(const DirectX::SimpleMath::Matrix& offsetmat, const DirectX::SimpleMath::Matrix& animmat, int boneindex, SkeletonData* data):
	m_OffsetMatrix(offsetmat),
	m_AnimationMatrix(animmat),
	m_BoneIndex(boneindex),
	m_pOwnerSkeletonData(data)
{
}

SkeletalMeshData& SkeletonData::GetSkeletalMeshData() const{
	return *m_pOwnerSkeletonMeshData;
}

const std::unordered_map<std::string, class OneBone>& SkeletonData::GetBoneList() const{
	return m_BoneList;
}

const std::string& SkeletonData::GetSkeletonName() const{
	return m_SkeletonName;
}

OneBone& SkeletonData::GetBone(const std::string& bonename){
	return m_BoneList.at(bonename);
}

void SkeletonData::SetOwner(SkeletalMeshData* data){
	m_pOwnerSkeletonMeshData = data;

	for (auto&& bone : m_BoneList) {
		bone.second.SetOwner(this);
	}
}

void SkeletonData::SetAnimationBone(const std::unordered_map <std::string, DirectX::SimpleMath::Matrix>* animbonelist){

	for (auto&& bone : m_BoneList) {
		bone.second.SetAnimationMatrix(animbonelist->at(bone.first));
	}
}

void SkeletonData::Bone_Data_Ejection(){

	// Bone�f�[�^�����o��
	auto& skeleton = m_pOwnerSkeletonMeshData->GetFbxManager().GetSkeletonData().GetBones();
	for (auto&& bone : skeleton) {
		m_BoneList.emplace(bone.first, OneBone(bone.second.GetOffsetMatrix(), bone.second.GetInitMatrix(), bone.second.GetBoneNumber(),this));
	}
}

void SkeletonData::UpdateCBufferSkeleton(){

	CBufferBoneMatrix cb;
	DirectX::XMFLOAT4X4 mtx;

	//�e�A�j���[�V�����{�[����Offset�{�[���̋t�s��������čs����m�肳����
	for (auto&& Bone : m_BoneList) {

		// �]�u����
		mtx = Bone.second.GetAnsMatrix().Transpose();
		cb.mBoneMatrix[Bone.second.GetBoneIndex()] = mtx;

		// �{�[���̃��[���h���W���v�Z
		Bone.second.GetTransformComponent();
	}

	m_CBufferSkeleton.CBufferUpdate(&cb);
}

SkeletonData::SkeletonData(SkeletalMeshData* data, const std::string& skeletonname):
	m_pOwnerSkeletonMeshData(data),
	m_SkeletonName(skeletonname)
{
	// Bone�f�[�^�̎��o��
	Bone_Data_Ejection();

	// �萔�o�b�t�@�̍쐬
	m_CBufferSkeleton.CreateCBuffer(7);
}
