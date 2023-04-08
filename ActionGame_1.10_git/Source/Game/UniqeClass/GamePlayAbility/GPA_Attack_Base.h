#pragma once
#include "../../../Game/Component/GameAblilitySystemComponent/GamePlayAbility.h"
#include "../../Component/AnimationComponent/easing.h"

class GPA_Attack_Base :
	public GamePlayAbility
{
private:
	void UniqueActivAbility()override;
	void UniqueEndAbility() override;

	void MontagePlay();

protected:
	bool m_IsWaitTag;
	std::string m_MontageName;
	float m_MontageSpeed;
	easing_functions m_Easing;
	
public:
	GPA_Attack_Base(class GameplayAbilitySystemComponent* Comp);
	~GPA_Attack_Base()override {};
};



