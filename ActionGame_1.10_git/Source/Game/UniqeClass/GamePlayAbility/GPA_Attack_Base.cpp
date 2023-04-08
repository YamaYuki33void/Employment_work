#include "GPA_Attack_Base.h"
#include "../../../Game/Component/ComponentList.h"
#include "../../../Game/Actor/CharactorActor.h"
#include "../Actor/PlayerActor.h"

void GPA_Attack_Base::UniqueActivAbility(){

	auto& actor = *static_cast<PlayerActor*>(GetGASComponent().GetActor());
	auto& skmesh = *actor.m_pMesh;
	auto& montage = *skmesh.GetAnimController()->GetAnimMontage();

	GetGASComponent().RemoveGameplayTags("player.Attack.EnableInput");

	if (m_IsWaitTag == true) {

		auto montageplayFunc = [&] {
			MontagePlay();
		};

		GetGASComponent().WaitGamePlayTagAdd("player.Attack.StartNextAttack", montageplayFunc);
	}
	else {
		MontagePlay();
	}
}

void GPA_Attack_Base::UniqueEndAbility(){

	GetGASComponent().RemoveGameplayTags("player.Attack.EnableInput");
	GetGASComponent().RemoveGameplayTags("player.Attack.StartNextAttack");
}

void GPA_Attack_Base::MontagePlay(){

	auto& actor = *static_cast<PlayerActor*>(GetGASComponent().GetActor());
	auto& skmesh = *static_cast<PlayerActor*>(GetGASComponent().GetActor())->m_pMesh;
	auto& montage = *skmesh.GetAnimController()->GetAnimMontage();

	actor.m_IsSward = true;
	actor.m_pSward->SetIsVisible(true);

	auto endfunction = [&] {
		EndAbility();
	};

	auto OnNotifyBegin = [&] {

		for (auto&& notifyname : montage.GetNotifyNameList()) {

			if (notifyname == "EnableInput") {
				GetGASComponent().AddGameplayTags("player.Attack.EnableInput");
			}

			if (notifyname == "StartNextAttack") {
				GetGASComponent().AddGameplayTags("player.Attack.StartNextAttack");
			}
		}
	};

	auto OnNextState = [&] {
		skmesh.GetAnimController()->GetAnimState()->ChangeState("StateSwardIdle");
	};

	montage.PlayMontage(m_MontageName, m_MontageSpeed,m_Easing);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Completed);
	montage.AddFanction(OnNextState, AnimationMontageComponent::NotifyType::Completed);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Interrupted);
	montage.AddFanction(OnNextState, AnimationMontageComponent::NotifyType::Interrupted);
	montage.AddFanction(OnNotifyBegin, AnimationMontageComponent::NotifyType::NotifyBegin);
}

GPA_Attack_Base::GPA_Attack_Base(GameplayAbilitySystemComponent* Comp):
	GamePlayAbility(Comp),
	m_IsWaitTag(false),
	m_MontageSpeed(1.0f)
{
}
