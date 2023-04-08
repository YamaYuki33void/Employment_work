#include "AnimationStateComponent.h"
#include "../../ComponentList.h"

void AnimationStateComponent::ChangeState(const std::string& name){

	// 現在のステートから出る
	if (m_pNowState != nullptr) {
		m_pNowState->OnExit();
	}

	// mapからステートを探す
	if (m_pStateList.count(name) != 0) {
		m_pNowState = m_pStateList.at(name).get();
		m_pNowState->OnEnter();
	}
	else {
		MessageBoxA(nullptr, std::string(name + "  Not State").c_str(), nullptr, MB_OK);
		m_pNowState = nullptr;
	}
}

void AnimationStateComponent::AddState(State* state){
	m_pStateList.emplace(state->GetStateName(), state);
}

const AnimationData* AnimationStateComponent::GetAnimationData(const std::string& animname) const{

#ifdef _DEBUG

	if (m_pAnimationList->count(animname) != 0) {
		return m_pAnimationList->at(animname).get();
	}
	else {
		MessageBoxA(nullptr, std::string(m_SkeletonName + animname + "  NotAnimationData").c_str(), nullptr, MB_OK);
	}

#else

	return m_pAnimationList->at(animname).get();

#endif
}

AnimationControllerComponent* AnimationStateComponent::GetAnimController() const{
	return m_pOwnerAnimController;
}

void AnimationStateComponent::UniqeUpdate(){
	AnimationStateUpdate();
	StateUpdate();
}

void AnimationStateComponent::StateUpdate(){

	bool montageplayflg = m_pOwnerAnimController->GetAnimMontage()->GetIsPlay();

	if (m_pNowState != nullptr && !montageplayflg) {
		m_pNowState->Update();
	}
}

AnimationStateComponent::AnimationStateComponent(AnimationControllerComponent* comp, const std::string& ComponentName):
	Component(comp->GetActor(),ComponentType::FuncType,ComponentName),
	m_SkeletonName(comp->GetSkeletalMesh()->GetModelData()->GetSkeletonData()->GetSkeletonName()),
	m_pOwnerAnimController(comp)
{
	// スケルトンの名前に紐づくアニメーションの取得
	m_pAnimationList = AnimationAssets::GetInstance()->GetSkeletonToAnimData(m_SkeletonName);
}
