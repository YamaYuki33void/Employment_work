#pragma once
#include "../../../../Assets/AnimationAssets/AnimationAssets.h"
#include "../../Component.h"
#include "State.h"

class AnimationStateComponent:
	public Component
{
public:
	// �X�e�[�g�̕ύX
	void ChangeState(const std::string& name);

	// �X�e�[�g�̒ǉ�
	void AddState(class State* state);

	// �����ꗗ
	virtual void Conditionlist() = 0;

	// Getter
	const class AnimationData* GetAnimationData(const std::string& animname)const;
	class AnimationControllerComponent* GetAnimController()const;

private:
	virtual void AnimationStateUpdate() = 0;
	void UniqeUpdate()override;
	void StateUpdate();

private:
	// ���݂̃X�e�[�g
	class State* m_pNowState;

	// �X�e�[�g���X�g
	std::unordered_map<std::string, std::unique_ptr<class State>>m_pStateList;

	// �X�P���g���̖��O
	std::string m_SkeletonName;

	// �X�P���g���l�[���Ɋ�Â����A�j���[�V�����f�[�^�̃��X�g
	const std::unordered_map<std::string, std::unique_ptr<class AnimationData>>* m_pAnimationList;

	// �I�[�i�[
	class AnimationControllerComponent* m_pOwnerAnimController;

public:
	AnimationStateComponent(class AnimationControllerComponent* comp, const std::string& ComponentName = "AnimStateComponent");
	virtual ~AnimationStateComponent() override {};
};

