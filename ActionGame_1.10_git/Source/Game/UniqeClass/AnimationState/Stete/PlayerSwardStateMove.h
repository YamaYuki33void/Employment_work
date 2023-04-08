#pragma once
#include "../../../Component/AnimationComponent/AnimationStateComponent/State.h"

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
class PlayerSwardStateIdle :
	public State
{
private:
	void OnEnter()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerSwardStateIdle(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerSwardStateIdle()override {};
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

class PlayerSwardStateWalk :
	public State
{
private:
	void OnEnter()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerSwardStateWalk(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerSwardStateWalk()override {};
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

class PlayerSwardStateRun :
	public State
{
private:
	void OnEnter()override;
	void OnExit()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerSwardStateRun(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerSwardStateRun()override {};
};

//------------------------------------------------------------------