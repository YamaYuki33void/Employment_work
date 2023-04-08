#pragma once
#include "../../../Component/AnimationComponent/AnimationStateComponent/State.h"

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
class PlayerStateIdle :
	public State
{
private:
	void OnEnter()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerStateIdle(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerStateIdle()override {};
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

class PlayerStateWalk :
	public State
{
private:
	void OnEnter()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerStateWalk(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerStateWalk()override {};
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//

class PlayerStateRun :
	public State
{
private:
	void OnEnter()override;
	void Update()override;

private:
	// Owner
	class PlayerAnimationStateComponent* m_pOwnerAnimState;

public:
	PlayerStateRun(class PlayerAnimationStateComponent* comp, const std::string& statename);
	~PlayerStateRun()override {};
};

//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//