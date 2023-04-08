#include "AnimationMontageComponent.h"
#include "../../../../Assets/AnimationMontageAssets/AnimationMontageAssets.h"
#include "../../ComponentList.h"

void AnimationMontageComponent::PlayMontage(const std::string& montagename,float late, easing_functions easing){

	// �Đ����r���Œ��f���ꂽ��֐��|�C���^����
	if (m_IsPlay == true) {
		OnInterruptedActivation();
	}

	// �����^�[�W���f�[�^�̃Z�b�g
	auto* skdata = m_pOwnerAnimController->GetSkeletalMesh()->GetModelData()->GetSkeletonData();
	m_MontageData = *AnimationMontageAssets::GetInstance()->GetAnimationMontage(skdata->GetSkeletonName(), montagename);

	// �Đ��t���O�𗧂Ă�
	m_IsPlay = true;

	// �Đ����[�g�Z�b�g
	m_late = late;

	// �J�E���g�̃��Z�b�g
	m_AnimNowFreamCnt = m_MontageData.GetAnimStartFream();

	// �A�j���V�����J�[�u�̐ݒ�
	m_Ease = easing;

	// �֐����X�g��S�폜
	FunctionListAllDelete();

	// �⊮�̊J�n
	m_pOwnerAnimController->GetAnimLerp()->StartLerp(m_MontageData.GetAnimationKeyFreamMatrix(m_AnimNowFreamCnt));
}

void AnimationMontageComponent::AddFanction(std::function<void()> fanc, NotifyType type){

	// �����^�[�W���Đ����ɋN�����R�[���o�b�N�֐�
	switch (type) {
	case AnimationMontageComponent::NotifyType::Completed:

		m_OnCompletedList.emplace_back(fanc);
		break;
	case AnimationMontageComponent::NotifyType::Interrupted:

		m_OnInterruptedList.emplace_back(fanc);
		break;
	case AnimationMontageComponent::NotifyType::NotifyBegin:

		m_OnNotifyBeginList.emplace_back(fanc);
		break;
	case AnimationMontageComponent::NotifyType::NotifyEnd:

		m_OnNotifyEndList.emplace_back(fanc);
		break;
	}
}

const bool AnimationMontageComponent::GetIsPlay() const{
	return m_IsPlay;
}

const std::vector<std::string>& AnimationMontageComponent::GetNotifyNameList() const{
	return m_NotifyNameList;
}

void AnimationMontageComponent::UniqeUpdate(){

	if (m_IsPlay == false) {
		return;
	}

	// �����ϐ�
	auto* skdata = m_pOwnerAnimController->GetSkeletalMesh()->GetModelData()->GetSkeletonData();
	auto* trans = m_pOwnerAnimController->GetSkeletalMesh()->GetTransformComponent();
	float animmaxfream = m_MontageData.GetAnimMaxFream() - 1.0f;

	if (!m_pOwnerAnimController->GetAnimLerp()->LerpUpdate()) {

		if (m_IsPlay == true) {

			if (m_AnimNowFreamCnt < animmaxfream) {

				float clump = m_AnimNowFreamCnt / animmaxfream;
				auto easingFunction = getEasingFunction(m_Ease);
				float progress = static_cast<float>(easingFunction(clump));

				 auto* animlist = m_MontageData.GetAnimationKeyFreamMatrix(progress * animmaxfream);
				 auto* rootpos = m_MontageData.GetAnimationRootPosKeyFream(progress * animmaxfream);

				skdata->SetAnimationBone(animlist);
				if (m_MontageData.GetAnimMode() == AnimationMontageData::AnimMode::Motion_To_Pos) {
					trans->AddLocalOffset(*rootpos);
				}

				m_AnimNowFreamCnt += (1.0f * m_late);

				// �ʒm�̍X�V
				NotifyUpdate(m_AnimNowFreamCnt);
			}
			else {
				m_AnimNowFreamCnt = 0;
				m_IsPlay = false;

				// �Ō�܂ŃA�j���[�V�����̍Đ������ꂽ��֐��|�C���^����
				OnCompletedListActivation();

				// �X�e�[�g�ɖ߂�
				m_pOwnerAnimController->GetAnimState()->Conditionlist();
			}
		}
	}
}

void AnimationMontageComponent::NotifyUpdate(float nowfream){

	m_NotifyNameList.clear();

	// Notify
	for (auto&& notify : m_MontageData.GetNotifyList()) {
		notify.NotifyUpdate(nowfream);

		if (notify.GetIsNotify() == true) {

			// �ʒm��������֐��|�C���^����
			m_NotifyNameList.emplace_back(notify.GetNotifyName());
			OnNotifyBeginActivation();
		}
	}

	// NotiryWindow
	for (auto&& notify : m_MontageData.GetNotifyWindowList()) {
		notify.NotifyWindowUpdate(nowfream);

		if (notify.GetIsBeginNotify() == true) {

			// �J�n�ʒm��������֐��|�C���^����
			m_NotifyNameList.emplace_back(notify.GetBeginNotifyName());
			OnNotifyBeginActivation();
		}

		if (notify.GetIsEndNotify() == true) {

			// �I���ʒm��������֐��|�C���^����
			m_NotifyNameList.emplace_back(notify.GetEndNotifyName());
			OnNotifyEndActivation();
		}
	}
}

void AnimationMontageComponent::FunctionListAllDelete(){

	// �֐��|�C���^���X�g
	m_OnCompletedList.clear();
	m_OnInterruptedList.clear();
	m_OnNotifyBeginList.clear();
	m_OnNotifyEndList.clear();
	m_NotifyNameList.clear();
}

void AnimationMontageComponent::OnCompletedListActivation(){


	for (auto&& fanc : m_OnCompletedList) {
		fanc();
	}
}

void AnimationMontageComponent::OnInterruptedActivation(){

	for (auto&& fanc : m_OnInterruptedList) {
		fanc();
	}
}

void AnimationMontageComponent::OnNotifyBeginActivation(){

	for (auto&& fanc : m_OnNotifyBeginList) {
		fanc();
	}
}

void AnimationMontageComponent::OnNotifyEndActivation(){

	for (auto&& fanc : m_OnNotifyEndList) {
		fanc();
	}
}

AnimationMontageComponent::AnimationMontageComponent(AnimationControllerComponent* comp, const std::string& ComponentName):
	Component(comp->GetActor(), ComponentType::FuncType, ComponentName),
	m_pOwnerAnimController(comp),
	m_IsPlay(false)
{
}
