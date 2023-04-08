#pragma once
#include <functional>
#include "../../../../System/DirectX/DirectX_Simple.h"
#include "../../Component.h"
#include "../../../../Assets/AnimationMontageAssets/AnimationMontageData.h"
#include "../easing.h"

class AnimationMontageComponent:
	public Component
{
public:
	enum class NotifyType {
		Completed, Interrupted, NotifyBegin, NotifyEnd
	};

	// �����^�[�W���Đ�
	void PlayMontage(const std::string& montagename, float late = 1.0f, easing_functions easing = easing_functions::EaseNone);

	// �֐��|�C���^�̒ǉ�
	void AddFanction(std::function<void()> fanc, NotifyType type);

	// Getter
	const bool GetIsPlay()const;
	const std::vector<std::string>& GetNotifyNameList()const;

private:
	void UniqeUpdate();

	// �ʒm�̍X�V
	void NotifyUpdate(float nowfream);

	// �֐��|�C���^�폜
	void FunctionListAllDelete();

	// �֐��|�C���^���s
	void OnCompletedListActivation();
	void OnInterruptedActivation();
	void OnNotifyBeginActivation();
	void OnNotifyEndActivation();

private:
	
	// �A�j���[�V�����f�[�^
	class AnimationMontageData m_MontageData;

	// ���݂̃t���[���J�E���g
	float m_AnimNowFreamCnt;

	// �Đ��t���O
	bool m_IsPlay;

	//�@�Đ����[�g
	float m_late;

	// �A�j���[�V�����J�[�u
	easing_functions m_Ease;

	// �֐��|�C���^�i�[
	std::vector<std::function<void()>> m_OnCompletedList;
	std::vector<std::function<void()>> m_OnInterruptedList;
	std::vector<std::function<void()>> m_OnNotifyBeginList;
	std::vector<std::function<void()>> m_OnNotifyEndList;
	std::vector<std::string> m_NotifyNameList;

	// �I�[�i
	class AnimationControllerComponent* m_pOwnerAnimController;

public:
	AnimationMontageComponent(class AnimationControllerComponent* comp, const std::string& ComponentName = "AnimMontageComponent");
	~AnimationMontageComponent() override {};
};

