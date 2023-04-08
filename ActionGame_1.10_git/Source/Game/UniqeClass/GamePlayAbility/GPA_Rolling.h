#pragma once
#include "../../../Game/Component/GameAblilitySystemComponent/GamePlayAbility.h"

class GPA_Rolling :
	public GamePlayAbility 
{
private:
	void UniqueActivAbility()override;
	void UniqueEndAbility() override;

public:
	GPA_Rolling(class GameplayAbilitySystemComponent* Comp);
	~GPA_Rolling()override {};
};

