#include "PlayerAnimationStateComponent.h"
#include "../../Actor/Actor.h"
#include "../../Component/ComponentList.h"
#include "../UniqeClassList.h"

void PlayerAnimationStateComponent::SetMaxSpeed(float speed){

	auto* move = GetActor()->GetComponentManager()->GetComponent<CharactorMoveComponent>();
	if (move != nullptr) {
		move->SetMaxSpeed(speed);
	}
}

void PlayerAnimationStateComponent::Conditionlist(){

	auto& actor = *static_cast<PlayerActor*>(GetActor());

	if (actor.m_IsSward == false) {
		if (GetLstickLength() <= 0.0f) {
			ChangeState("StateIdle");
		}
		else if (0.0f < GetLstickLength() && GetLstickLength() < 0.4f) {
			ChangeState("StateWalk");
		}
		else if (0.8f < GetLstickLength()) {
			ChangeState("StateRun");
		}
	}
	else {
		if (GetLstickLength() <= 0.0f) {
			ChangeState("StateSwardIdle");
		}
		else if (0.0f < GetLstickLength() && GetLstickLength() < 0.4f) {
			ChangeState("StateSwardWalk");
		}
		else if (0.8f < GetLstickLength()) {
			ChangeState("StateSwardRun");
		}
	}
}

const float PlayerAnimationStateComponent::GetLstickLength() const{
	return m_LstickLength;
}

AnimationLerp* PlayerAnimationStateComponent::GetAnimLerp() const{
	return GetAnimController()->GetAnimLerp();
}

void PlayerAnimationStateComponent::AnimationStateUpdate(){
	m_LstickLength = GamePad::GetInstance()->GetLStickLength();
}

PlayerAnimationStateComponent::PlayerAnimationStateComponent(AnimationControllerComponent* comp, const std::string& ComponentName):
	AnimationStateComponent(comp,ComponentName)
{
	// ステート追加
	new PlayerStateIdle(this, "StateIdle");
	new PlayerStateWalk(this, "StateWalk");
	new PlayerStateRun (this, "StateRun");
	new PlayerSwardStateIdle(this, "StateSwardIdle");
	new PlayerSwardStateWalk(this, "StateSwardWalk");
	new PlayerSwardStateRun (this, "StateSwardRun");
}
