#pragma once
#include "../../Component/AnimationComponent/AnimationStateComponent/AnimationStateComponent.h"

class PlayerAnimationStateComponent:
	public AnimationStateComponent
{
public:
	// 最大速度スピード設定
	void SetMaxSpeed(float speed);

	// 条件一覧
	void Conditionlist()override;

	// Getter
	const float GetLstickLength()const;
	class AnimationLerp* GetAnimLerp()const;

private:
	void AnimationStateUpdate()override;

private:
	float m_LstickLength;

public:
	PlayerAnimationStateComponent(class AnimationControllerComponent* comp, const std::string& ComponentName = "AnimStateComponent");
	~PlayerAnimationStateComponent() override {};
};

