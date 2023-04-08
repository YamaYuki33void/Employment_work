#include "PlayerStateMove.h"
#include "../../UniqeClassList.h"
#include "../../../Component/ComponentList.h"

AnimationPlayer *Idle, *Walk, *Run;

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

void PlayerStateIdle::OnEnter() {
	m_pOwnerAnimState->SetMaxSpeed(200.0f);
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Idle->GetAnimationNowKeyFream());
}

void PlayerStateIdle::Update() {

	if (0.0f < m_pOwnerAnimState->GetLstickLength() && m_pOwnerAnimState->GetLstickLength() < 0.4f) {
		ChangeState("StateWalk");
	}
	else if (0.8f < m_pOwnerAnimState->GetLstickLength()) {
		ChangeState("StateRun");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Idle->AnimationUpdate(m_pOwnerAnimState->GetAnimLerp()->LerpUpdate());
		SetAnimation(Idle);
	}
}

PlayerStateIdle::PlayerStateIdle(PlayerAnimationStateComponent* comp, const std::string& statename) :
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Idle = new AnimationPlayer("Idle", this);
}

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

void PlayerStateWalk::OnEnter() {
	m_pOwnerAnimState->SetMaxSpeed(250.0f);
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Walk->GetAnimationNowKeyFream());
}

void PlayerStateWalk::Update() {

	if (m_pOwnerAnimState->GetLstickLength() <= 0.0f) {
		ChangeState("StateIdle");
	}
	else if (0.8f < m_pOwnerAnimState->GetLstickLength()) {
		ChangeState("StateRun");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Walk->AnimationUpdate();
		SetAnimation(Walk);
	}
}

PlayerStateWalk::PlayerStateWalk(PlayerAnimationStateComponent* comp, const std::string& statename) :
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Walk = new AnimationPlayer("Walk", this);
}

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

void PlayerStateRun::OnEnter() {
	m_pOwnerAnimState->SetMaxSpeed(600.0f);
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Run->GetAnimationNowKeyFream());
}

void PlayerStateRun::Update() {

	if (m_pOwnerAnimState->GetLstickLength() <= 0.0f) {
		ChangeState("StateIdle");
	}
	else  if (0.0f < m_pOwnerAnimState->GetLstickLength() && m_pOwnerAnimState->GetLstickLength() < 0.4f) {
		ChangeState("StateWalk");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Run->AnimationUpdate();
		SetAnimation(Run);
	}
}

PlayerStateRun::PlayerStateRun(PlayerAnimationStateComponent* comp, const std::string& statename) :
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Run = new AnimationPlayer("Run", this);
	Run->AnimationRootMode(AnimationPlayer::AnimMode::Motion_Only);
}

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//