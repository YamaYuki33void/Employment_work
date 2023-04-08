#include "SkeletonData.h"
#include "../ModelAssets/SkeletalMeshData.h"
#include "../../Game/Component/ComponentList.h"

TransformComponent* OneBone::GetTransformComponent(){

	// 右手系の行列を左手系に変換する
	DirectX::SimpleMath::Matrix leftanimmat = m_AnimationMatrix.LeftHand();

	// Model行列を取り出す
	DirectX::SimpleMath::Matrix modelmat = m_pOwnerSkeletonData->GetSkeletalMeshData().GetComponent().GetTransformComponent()->GetWorldMatrix();
	
	// ボーンのワールド行列を作成する
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

	// Boneデータを取り出す
	auto& skeleton = m_pOwnerSkeletonMeshData->GetFbxManager().GetSkeletonData().GetBones();
	for (auto&& bone : skeleton) {
		m_BoneList.emplace(bone.first, OneBone(bone.second.GetOffsetMatrix(), bone.second.GetInitMatrix(), bone.second.GetBoneNumber(),this));
	}
}

void SkeletonData::UpdateCBufferSkeleton(){

	CBufferBoneMatrix cb;
	DirectX::XMFLOAT4X4 mtx;

	//各アニメーションボーンとOffsetボーンの逆行列をかけて行列を確定させる
	for (auto&& Bone : m_BoneList) {

		// 転置する
		mtx = Bone.second.GetAnsMatrix().Transpose();
		cb.mBoneMatrix[Bone.second.GetBoneIndex()] = mtx;

		// ボーンのワールド座標を計算
		Bone.second.GetTransformComponent();
	}

	m_CBufferSkeleton.CBufferUpdate(&cb);
}

SkeletonData::SkeletonData(SkeletalMeshData* data, const std::string& skeletonname):
	m_pOwnerSkeletonMeshData(data),
	m_SkeletonName(skeletonname)
{
	// Boneデータの取り出し
	Bone_Data_Ejection();

	// 定数バッファの作成
	m_CBufferSkeleton.CreateCBuffer(7);
}
