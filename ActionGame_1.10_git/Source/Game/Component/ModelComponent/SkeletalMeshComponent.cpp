#include "SkeletalMeshComponent.h"
#include "../../../Assets/ModelAssets/ModelAssets.h"
#include "../ComponentList.h"

const std::string& SkeletalMeshComponent::GetModelDataName() const{
	return m_ModelDataName;
}

SkeletalMeshData* SkeletalMeshComponent::GetModelData() const{
	return m_pModelData.get();
}

AnimationControllerComponent* SkeletalMeshComponent::GetAnimController() const{
	return m_pAnimControllerComponent;
}

void SkeletalMeshComponent::SetModelData(const std::string& modelname){

	// モデルデータを動的に確保しAssetsデータからディープコピーする
	if (m_pModelData != nullptr) {
		m_pModelData.reset();
	}

	m_pModelData = std::make_unique<SkeletalMeshData>(*ModelAssets::GetInstance()->GetSkeletalMeshData(modelname));
	m_ModelDataName = modelname;

	// Ownerの付け替え
	m_pModelData->SetOwnerComponent(this);
	m_pModelData->GetSkeletonData()->SetOwner(m_pModelData.get());
	m_pModelData->GetSkeletonData()->UpdateCBufferSkeleton();

	// アニメーションコンポーネントの生成
	if (m_pAnimControllerComponent == nullptr) {
		m_pAnimControllerComponent = new AnimationControllerComponent(this);
	}
}

void SkeletalMeshComponent::UniqeDraw(){

	if (m_pModelData != nullptr) {
		m_pModelData->Draw(GetTransformComponent()->GetWorldMatrix());
	}
}

SkeletalMeshComponent::SkeletalMeshComponent(Actor* actor, const std::string& ComponentName):
	ModelComponent(actor,ComponentName)
{
}
