#pragma once
#include "../../../../../System/DirectX/DirectX_Simple.h"

class AnimationPlayer{
public:
	enum class AnimMode {
		NoRootMotion,
		Motion_To_Pos,
		Motion_Only,
	};

	// �A�j���[�V�����̍X�V
	void AnimationUpdate(bool isupdate = true);

	// �A�j���[�V�����̃t���[���J�E���g�ύX
	void AnimationReset(float resetfream = 0.0f);

	// �A�j���[�V�����̃X�s�[�h�{���ύX
	void AnimationSpeed(float speed);

	// ���[�g���[�V�������̈ړ��{���ύX
	void AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed);

	// ���[�g���[�V�����̐ݒ�
	void AnimationRootMode(const AnimMode mode);

	// Getter
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* GetAnimationNowKeyFream()const;
	const DirectX::SimpleMath::Vector3* GetAnimationRootposNowKeyFream()const;
	const AnimMode GetAnimMode()const;

private:
	void AnimModeSwich(float nowfream);

private:
	// �A�j���[�V�����f�[�^
	const class AnimationData* m_pAnimationData;

	// ���݂̃A�j���[�V������KeyFream
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_AnimationNowKeyFream;

	// ���[�g���[�V�����g�p���̎��̃I�t�Z�b�g�ʒu
	DirectX::SimpleMath::Vector3 m_AnimationRootposNowKeyFream;

	// ���[�g���[�V�������̃I�t�Z�b�g�ړ��n�̔{��
	DirectX::SimpleMath::Vector3 m_RootPosMgnification;

	// �A�j���[�V�����̃X�s�[�h
	float m_Speed;

	// �A�j���[�V�����J�E���g
	float m_AnimNowCnt;

	// ���[�g���[�V�����̃��[�h
	AnimMode m_AnimMode;

	// �I�[�i�[
	class State* m_pOwnerState;

public:
	AnimationPlayer(const std::string& animname, class State* state);
	~AnimationPlayer() {};
};

