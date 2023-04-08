#include "State.h"
#include "../../ComponentList.h"

void State::ChangeState(const std::string& statename){
	m_pOwnerAnimState->ChangeState(statename);
}

void State::AddAnimationPlayer(AnimationPlayer* data){
	m_pAnimationPlayerList.emplace_back(std::move(data));
}

const std::string& State::GetStateName() const{
	return m_StateName;
}

AnimationStateComponent* State::GetAnimState() const{
	return m_pOwnerAnimState;
}

void State::SetAnimation(AnimationPlayer* animadata){

	auto* skmesh = m_pOwnerAnimState->GetAnimController()->GetSkeletalMesh();
	skmesh->GetModelData()->GetSkeletonData()->SetAnimationBone(animadata->GetAnimationNowKeyFream());

	if (animadata->GetAnimMode() == AnimationPlayer::AnimMode::Motion_To_Pos) {
		skmesh->GetTransformComponent()->AddLocalOffset(*animadata->GetAnimationRootposNowKeyFream());
	}
}

State::State(AnimationStateComponent* comp, const std::string& statename):
	m_pOwnerAnimState(comp),
	m_StateName(statename)
{
	// ステートの追加
	comp->AddState(this);
}
