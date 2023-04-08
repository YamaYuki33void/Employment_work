#pragma once
#include "GPA_Attack_Base.h"

//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//

class GPA_Sward_Attack1 :
	public GPA_Attack_Base
{
public:
	GPA_Sward_Attack1(class GameplayAbilitySystemComponent* Comp);
	~GPA_Sward_Attack1()override {};
};

//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//

class GPA_Sward_Attack2 :
	public GPA_Attack_Base
{
public:
	GPA_Sward_Attack2(class GameplayAbilitySystemComponent* Comp);
	~GPA_Sward_Attack2()override {};
};

//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//

class GPA_Sward_Attack3 :
	public GPA_Attack_Base
{
public:
	GPA_Sward_Attack3(class GameplayAbilitySystemComponent* Comp);
	~GPA_Sward_Attack3()override {};
};
