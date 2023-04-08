#include "GPA_Sward_DashAttack.h"
#include "../../Component/ComponentList.h"
#include "../Actor/PlayerActor.h"

void GPA_Sward_DashAttack::UniqueActivAbility(){

	auto& skmesh = static_cast<CharactorActor*>(GetGASComponent().GetActor())->m_pMesh;
	auto& montage = *skmesh->GetAnimController()->GetAnimMontage();

	auto endfunction = [&] {
		EndAbility();
	};

	montage.PlayMontage("M_Sward_DashAttack", 1.1f ,EaseInSine);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Completed);
	montage.AddFanction(endfunction, AnimationMontageComponent::NotifyType::Interrupted);
}

void GPA_Sward_DashAttack::UniqueEndAbility(){
}

GPA_Sward_DashAttack::GPA_Sward_DashAttack(GameplayAbilitySystemComponent* Comp):
	GamePlayAbility(Comp)
{
	AddAbilityTags("player.Attack.D.1");

	AddActrivateOwnerTags("player.Attack.D.1");

	AddActrivateRequiredTags("player.State.SwardDash");

	AddActrivateBlockedTags("player.Attack");
	AddActrivateBlockedTags("player.State.Motion");
}
