#pragma once
#include "../../Component.h"

class AnimationControllerComponent:
	public Component
{
public:
	// �X�e�[�g�R���|�[�l���g�̃Z�b�g
	void SetAnimState(class AnimationStateComponent* state);

	// Getter
	class AnimationStateComponent* GetAnimState()const;
	class AnimationMontageComponent* GetAnimMontage()const;
	class SkeletalMeshComponent* GetSkeletalMesh()const;
	class AnimationLerp* GetAnimLerp()const;

private:
	// �X�e�[�g�R���|�[�l���g
	class AnimationStateComponent* m_pAnimState;

	// �����^�[�W���R���|�[�l���g
	class AnimationMontageComponent* m_pAnimMontage;

	// �A�j���[�V�����̕��
	std::unique_ptr<class AnimationLerp> m_pAnimationLerp;

	// �I�[�i�[
	class SkeletalMeshComponent* m_pOwnerSkeletalMesh;

public:
	AnimationControllerComponent(class SkeletalMeshComponent* comp,const std::string& ComponentName = "AnimControllerComponent");
	~AnimationControllerComponent()override {};
};

