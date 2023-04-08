#pragma once
#include "GPA_Attack_Base.h"

class GPA_Sward_DashAttack :
	public GamePlayAbility
{
private:
	void UniqueActivAbility()override;
	void UniqueEndAbility() override;

public:
	GPA_Sward_DashAttack(class GameplayAbilitySystemComponent* Comp);
	~GPA_Sward_DashAttack()override {};
};

