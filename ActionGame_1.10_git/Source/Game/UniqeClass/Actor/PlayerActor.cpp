#include "PlayerActor.h"
#include "../../Component/ComponentList.h"
#include "../UniqeClassList.h"

using namespace DirectX::SimpleMath;

void PlayerActor::UniqeUpdate(){

	// 移動
	Vector2 Lstick = { GamePad::GetInstance()->CheckThumbLX(), GamePad::GetInstance()->CheckThumbLY() };
	if (!m_pMesh->GetAnimController()->GetAnimMontage()->GetIsPlay()) {
		m_pMove->AddMoveInput(Lstick);
	}

	// カメラ操作
	Vector2 Rstick = { GamePad::GetInstance()->CheckThumbRX(),GamePad::GetInstance()->CheckThumbRY() };
	m_pCameraArm->AddRotaionYawInput(Rstick.x * 2.0f);
	m_pCameraArm->AddRotaionPichInput(-Rstick.y * 2.0f);

	if (GamePad::GetInstance()->CheckButtonTrigger(GAMEPAD::GAMEPAD_B)) {
		m_pGASComponent->TryActiveAbilitiesbyTag("player.Attack.A");
	}
	if (GamePad::GetInstance()->CheckButtonTrigger(GAMEPAD::GAMEPAD_Y)) {
		m_pGASComponent->TryActiveAbilitiesbyTag("player.Attack.B");
		m_pGASComponent->TryActiveAbilitiesbyTag("player.Attack.C");
	}
	if (GamePad::GetInstance()->CheckButtonTrigger(GAMEPAD::GAMEPAD_RIGHT_THUMB)) {
		m_pGASComponent->TryActiveAbilitiesbyTag("player.Attack.D");
	}

	if (GamePad::GetInstance()->CheckButtonTrigger(GAMEPAD::GAMEPAD_X)) {
		m_pGASComponent->TryActiveAbilitiesbyTag("player.Motion.Rolling");
	}
}

PlayerActor::PlayerActor(Scene* scene, const std::string& ActorName):
	CharactorActor(scene,ActorName)
{
	// モデルのセット
	m_pMesh->SetModelData("Maria");

	// カメラの有効化
	m_pCamera->GetTransformComponent()->AddWorldOffset(Vector3(0, 100, -600));
	m_pCamera->SetTargetView();
	m_pCameraArm;

	// プレイヤーステートアニメーションのセット
	m_pMesh->GetAnimController()->SetAnimState(new PlayerAnimationStateComponent(m_pMesh->GetAnimController()));
	m_pMesh->GetAnimController()->GetAnimState()->ChangeState("StateIdle");

	// 剣装備
	{
		m_pSward = new StaticMeshComponent(this, "BigSward");
		m_pSward->SetModelData("BigSward");
		m_pSward->GetMeshData()->SetModelScale(Vector3(10, 10, 7));
		m_pSward->GetMeshData()->SetModelPibotOffset(Vector3(0, 0, -180));

		auto& bone = m_pMesh->GetModelData()->GetSkeletonData()->GetBone("mixamorig:RightHand");
		m_pSward->GetTransformComponent()->SetWorldLocation(Vector3(90.0f, 145.0f, 29.0f));
		m_pSward->GetTransformComponent()->SetWorldRotation(Vector3(5.0f, -152.0f, -30.0f));
		m_pSward->GetTransformComponent()->AddLocalOffset(Vector3(0, 0, 65));
		m_pSward->GetTransformComponent()->ResistParent(bone.GetTransformComponent());
		m_pSward->SetIsVisible(false);
	}

	m_pGASComponent = new GameplayAbilitySystemComponent(this);
	m_pGASComponent->AddGameplayAbility(new GPA_Rolling(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack1(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack2(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack3(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack4(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack5(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack6(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack7(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_Attack8(m_pGASComponent));
	m_pGASComponent->AddGameplayAbility(new GPA_Sward_DashAttack(m_pGASComponent));
}
