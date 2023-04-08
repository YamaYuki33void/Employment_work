#pragma once
#include "../../Component/AnimationComponent/AnimationStateComponent/AnimationStateComponent.h"

class PlayerAnimationStateComponent:
	public AnimationStateComponent
{
public:
	// �ő呬�x�X�s�[�h�ݒ�
	void SetMaxSpeed(float speed);

	// �����ꗗ
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

