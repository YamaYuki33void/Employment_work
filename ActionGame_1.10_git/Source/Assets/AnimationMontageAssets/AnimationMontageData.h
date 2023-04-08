#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "Notify.h"

class AnimationMontageData{
public:
	enum class AnimMode {
		NoRootMotion,
		Motion_To_Pos,
		Motion_Only,
	};

	// ���[�g���[�V�����̐ݒ�
	void AnimationRootMode(const AnimMode mode);

	// ���[�g���[�V�������̈ړ��{���ύX
	void AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed);

	// ������t���[���������I�t�Z�b�g�l�̐ݒ�
	void AnimationEndFreamDelete(const float offset);

	// �X�^�[�g�t���[���̐ݒ�
	void AnimationStartFream(const float fream);

	// �ʒm�̒ǉ�
	void AddNotify(const std::string& notifyname, float notifyfream);
	void AddNotify(const std::string& beginname,  float beginfream, const std::string& endname, float endfream);

	// Getter
	const AnimMode GetAnimMode()const;
	const float GetAnimMaxFream()const;
	const float GetAnimStartFream()const;
	std::vector<class Notify>& GetNotifyList();
	std::vector<class NotifyWindow>& GetNotifyWindowList();
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* GetAnimationKeyFreamMatrix(float nowfream)const;
	const DirectX::SimpleMath::Vector3* GetAnimationRootPosKeyFream(float nowfream)const;

private:
	// �ʒm���X�g
	std::vector<class Notify>       m_NotifyList;
	std::vector<class NotifyWindow> m_NotifyWindowList;

	// ���݂̃A�j���[�V������KeyFream
	mutable std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_AnimationFreamMatrix;

	// ���[�g���[�V�������̃I�t�Z�b�g�ʒu
	mutable DirectX::SimpleMath::Vector3 m_AnimationRootPosKeyFream;

	// ���[�g���[�V�������̃I�t�Z�b�g�ړ��n�̔{��
	DirectX::SimpleMath::Vector3 m_RootPosMgnification;

	// �J�n�t���[���̒l
	float m_StartFream;

	// ������t���[���������I�t�Z�b�g�l
	float m_EndfreamDeleteOffset;

	// �ő�t���[��
	float m_MaxFream;
	
	// �A�j���[�V�����f�[�^
	const class AnimationData* m_pAnimationData;

	// ���[�g���[�h
	AnimMode m_AnimMode;

public:
	AnimationMontageData& operator=(const AnimationMontageData& masterdata);
	AnimationMontageData(const std::string& skeletonname, const std::string& animname);
	AnimationMontageData() {};
	~AnimationMontageData() {};
};
