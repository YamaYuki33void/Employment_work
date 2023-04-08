#include "AnimationControllerComponent.h"
#include "../../ComponentList.h"

void AnimationControllerComponent::SetAnimState(AnimationStateComponent* state){
	m_pAnimState = state;
}

AnimationStateComponent* AnimationControllerComponent::GetAnimState() const{
	return m_pAnimState;
}

AnimationMontageComponent* AnimationControllerComponent::GetAnimMontage() const{
	return m_pAnimMontage;
}

SkeletalMeshComponent* AnimationControllerComponent::GetSkeletalMesh() const{
	return m_pOwnerSkeletalMesh;
}

AnimationLerp* AnimationControllerComponent::GetAnimLerp() const{
	return m_pAnimationLerp.get();
}

AnimationControllerComponent::AnimationControllerComponent(class SkeletalMeshComponent* comp,const std::string& ComponentName):
	Component(comp->GetActor(), ComponentType::FuncType, ComponentName),
	m_pAnimationLerp(std::make_unique<AnimationLerp>(comp->GetModelData()->GetSkeletonData())),
	m_pOwnerSkeletalMesh(comp)
{
	// モンタージュコンポーネントの作成
	m_pAnimMontage = new AnimationMontageComponent(this);
}
