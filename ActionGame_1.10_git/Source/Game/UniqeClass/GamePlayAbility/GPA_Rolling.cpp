#include "GPA_Rolling.h"
#include "../../../Game/Component/ComponentList.h"
#include "../../../Game/Actor/CharactorActor.h"

void GPA_Rolling::UniqueActivAbility(){

	auto& skmesh = static_cast<CharactorActor*>(GetGASComponent().GetActor())->m_pMesh;
	auto& montage = *skmesh->GetAnimController()->GetAnimMontage();

	auto endfunction = [&] {
		EndAbility();
	};

	auto OnNotifyBegin = [&] {

		for (auto&& notifyname : montage.GetNotifyNameList()) {

			if (notifyname == "EnableInput") {
				GetGASComponent().AddGameplayTags("player.Motion.EnableInput");
			}

			if (notifyname == "StartNextRolling") {
				GetGASComponent().AddGameplayTags("player.Motion.StartNextRolling");
			}
		}
	};

	montage.PlayMontage("M_Rolling",1.5f);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Completed);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Interrupted);
	montage.AddFanction(OnNotifyBegin, AnimationMontageComponent::NotifyType::NotifyBegin);
}

void GPA_Rolling::UniqueEndAbility(){

	GetGASComponent().RemoveGameplayTags("player.Motion.EnableInput");
	GetGASComponent().RemoveGameplayTags("player.Motion.StartNextRolling");
}

GPA_Rolling::GPA_Rolling(GameplayAbilitySystemComponent* Comp) :
	GamePlayAbility(Comp)
{
	AddAbilityTags("player.Motion.Rolling");
	AddActrivateOwnerTags("player.State.Rolling");

	AddActrivateBlockedTags("player.State.Rolling");
	AddActrivateBlockedTags("player.Attack");
}
