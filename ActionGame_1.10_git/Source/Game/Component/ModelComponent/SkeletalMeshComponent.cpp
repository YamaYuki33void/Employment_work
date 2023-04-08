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

	// ���f���f�[�^�𓮓I�Ɋm�ۂ�Assets�f�[�^����f�B�[�v�R�s�[����
	if (m_pModelData != nullptr) {
		m_pModelData.reset();
	}

	m_pModelData = std::make_unique<SkeletalMeshData>(*ModelAssets::GetInstance()->GetSkeletalMeshData(modelname));
	m_ModelDataName = modelname;

	// Owner�̕t���ւ�
	m_pModelData->SetOwnerComponent(this);
	m_pModelData->GetSkeletonData()->SetOwner(m_pModelData.get());
	m_pModelData->GetSkeletonData()->UpdateCBufferSkeleton();

	// �A�j���[�V�����R���|�[�l���g�̐���
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
