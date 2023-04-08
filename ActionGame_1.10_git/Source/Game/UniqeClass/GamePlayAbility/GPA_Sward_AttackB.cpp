#include "GPA_Sward_AttackB.h"

GPA_Sward_Attack4::GPA_Sward_Attack4(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.B.1");
	AddActrivateOwnerTags("player.Attack.B.1");
	AddActrivateBlockedTags("player.Attack");

	m_IsWaitTag = false;
	m_MontageName = "M_Sward_Attack4";
	m_MontageSpeed = 1.1f;
}

GPA_Sward_Attack5::GPA_Sward_Attack5(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.B.2");
	AddActrivateOwnerTags("player.Attack.B.2");
	AddActrivateRequiredTags("player.Attack.B.1");
	AddActrivateRequiredTags("player.Attack.EnableInput");
	AddActrivateBlockedTags("player.Attack.B.2");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack5";
	m_MontageSpeed = 1.3f;
}

GPA_Sward_Attack6::GPA_Sward_Attack6(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.B.3");
	AddActrivateOwnerTags("player.Attack.B.3");
	AddActrivateRequiredTags("player.Attack.B.2");
	AddActrivateRequiredTags("player.Attack.EnableInput");
	AddActrivateBlockedTags("player.Attack.B.3");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack6";
	m_MontageSpeed = 1.2f;
}
