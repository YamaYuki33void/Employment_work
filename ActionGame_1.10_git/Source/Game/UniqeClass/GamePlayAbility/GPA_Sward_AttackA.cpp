#include "GPA_Sward_AttackA.h"

GPA_Sward_Attack1::GPA_Sward_Attack1(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.A.1");
	AddActrivateOwnerTags("player.Attack.A.1");
	AddActrivateBlockedTags("player.State.Motion");
	AddActrivateBlockedTags("player.Attack");

	m_IsWaitTag = false;
	m_MontageName = "M_Sward_Attack1";
	m_MontageSpeed = 1.0f;
	m_Easing = EaseInSine;
}

GPA_Sward_Attack2::GPA_Sward_Attack2(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.A.2");
	AddActrivateOwnerTags("player.Attack.A.2");
	AddActrivateRequiredTags("player.Attack.A.1");
	AddActrivateRequiredTags("player.Attack.EnableInput");
	AddActrivateBlockedTags("player.Attack.A.2");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack2";
	m_MontageSpeed = 1.3f;
}

GPA_Sward_Attack3::GPA_Sward_Attack3(GameplayAbilitySystemComponent* Comp) :
	GPA_Attack_Base(Comp)
{
	AddAbilityTags("player.Attack.A.3");
	AddActrivateOwnerTags("player.Attack.A.3");
	AddActrivateRequiredTags("player.Attack.A.2");
	AddActrivateRequiredTags("player.Attack.EnableInput");
	AddActrivateBlockedTags("player.Attack.A.3");

	m_IsWaitTag = true;
	m_MontageName = "M_Sward_Attack3";
	m_MontageSpeed = 1.5f;
}

