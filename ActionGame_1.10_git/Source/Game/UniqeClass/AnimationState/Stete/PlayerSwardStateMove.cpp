#include "PlayerSwardStateMove.h"
#include "../../../Component/ComponentList.h"
#include "../../Actor/PlayerActor.h"
#include "../../UniqeClassList.h"

AnimationPlayer* Sward_Idle, * Sward_Run, * Sward_Walk;

void PlayerSwardStateIdle::OnEnter() {

	Sward_Idle->AnimationReset();
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Sward_Idle->GetAnimationNowKeyFream());
}


void PlayerSwardStateIdle::Update(){

	if (0.0f < m_pOwnerAnimState->GetLstickLength() && m_pOwnerAnimState->GetLstickLength() < 0.4f) {
		ChangeState("StateSwardWalk");
	}
	else if (0.8f < m_pOwnerAnimState->GetLstickLength()) {
		ChangeState("StateSwardRun");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Sward_Idle->AnimationUpdate();
		SetAnimation(Sward_Idle);
	}
}

PlayerSwardStateIdle::PlayerSwardStateIdle(PlayerAnimationStateComponent* comp, const std::string& statename):
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Sward_Idle = new AnimationPlayer("Sward_Idle", this);
}

void PlayerSwardStateWalk::OnEnter(){

	m_pOwnerAnimState->SetMaxSpeed(200);
	Sward_Walk->AnimationReset();
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Sward_Walk->GetAnimationNowKeyFream());
}

void PlayerSwardStateWalk::Update(){

	if (m_pOwnerAnimState->GetLstickLength() <= 0.0f) {
		ChangeState("StateSwardIdle");
	}
	else if (0.8f < m_pOwnerAnimState->GetLstickLength()) {
		ChangeState("StateSwardRun");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Sward_Walk->AnimationUpdate();
		SetAnimation(Sward_Walk);
	}
}

PlayerSwardStateWalk::PlayerSwardStateWalk(PlayerAnimationStateComponent* comp, const std::string& statename):
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Sward_Walk = new AnimationPlayer("Sward_Walk", this);
}

void PlayerSwardStateRun::OnEnter(){

	auto& actor = *static_cast<PlayerActor*>(m_pOwnerAnimState->GetActor());
	actor.m_pGASComponent->AddGameplayTags("player.State.SwardDash");
	
	m_pOwnerAnimState->SetMaxSpeed(500);
	Sward_Run->AnimationReset(15.0f);
	m_pOwnerAnimState->GetAnimLerp()->StartLerp(Sward_Run->GetAnimationNowKeyFream());
}

void PlayerSwardStateRun::OnExit(){
	auto& actor = *static_cast<PlayerActor*>(m_pOwnerAnimState->GetActor());
	actor.m_pGASComponent->RemoveGameplayTags("player.State.SwardDash");
}

void PlayerSwardStateRun::Update(){

	if (m_pOwnerAnimState->GetLstickLength() <= 0.0f) {
		ChangeState("StateSwardIdle");
	}
	else  if (0.0f < m_pOwnerAnimState->GetLstickLength() && m_pOwnerAnimState->GetLstickLength() < 0.4f) {
		ChangeState("StateSwardWalk");
	}

	if (!m_pOwnerAnimState->GetAnimLerp()->LerpUpdate()) {
		Sward_Run->AnimationUpdate();
		SetAnimation(Sward_Run);
	}
}

PlayerSwardStateRun::PlayerSwardStateRun(PlayerAnimationStateComponent* comp, const std::string& statename):
	State(comp, statename),
	m_pOwnerAnimState(comp)
{
	Sward_Run = new AnimationPlayer("Sward_Run", this);
}
