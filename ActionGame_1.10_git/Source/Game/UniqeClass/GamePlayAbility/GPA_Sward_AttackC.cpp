#include "GPA_Sward_AttackC.h"

GPA_Sward_Attack7::GPA_Sward_Attack7(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.C.1");
	AddActrivateOwnerTags("player.Attack.C.1");

	AddActrivateRequiredTags("player.Attack.A.1");
	AddActrivateRequiredTags("player.Attack.EnableInput");

	AddActrivateBlockedTags("player.Attack.C.1");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack7";
	m_MontageSpeed = 1.6f;
}

GPA_Sward_Attack8::GPA_Sward_Attack8(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.C.2");
	AddActrivateOwnerTags("player.Attack.C.2");

	AddActrivateRequiredTags("player.Attack.C.1");
	AddActrivateRequiredTags("player.Attack.EnableInput");

	AddActrivateBlockedTags("player.Attack.C.2");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack8";
	m_MontageSpeed = 1.6f;
}
