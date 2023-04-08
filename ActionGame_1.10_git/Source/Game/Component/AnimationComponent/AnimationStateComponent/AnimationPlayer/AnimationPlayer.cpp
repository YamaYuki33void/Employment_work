#include "AnimationPlayer.h"
#include "../../../ComponentList.h"

void AnimationPlayer::AnimationUpdate(bool isupdate){

	// 引数の更新フラグがfalseであればアニメーションの更新をせずにこの関数を抜ける
	if (isupdate == false) {
		return;
	}

	AnimModeSwich(m_AnimNowCnt);
}

void AnimationPlayer::AnimationReset(float resetfream){

	m_AnimNowCnt = resetfream;

	switch (m_AnimMode) {
	case AnimationPlayer::AnimMode::NoRootMotion:

		for (auto&& animbone : m_pAnimationData->GetKeyFreamData().GetAnimationKeyFreamMatrix(m_AnimNowCnt)) {
			m_AnimationNowKeyFream.at(animbone.first) = animbone.second;
		}

		break;

	case AnimationPlayer::AnimMode::Motion_To_Pos:
	case AnimationPlayer::AnimMode::Motion_Only:

		for (auto&& animbone : m_pAnimationData->GetKeyFreamData().GetRootAnimationKeyFreamMatrix(m_AnimNowCnt)) {
			m_AnimationNowKeyFream.at(animbone.first) = animbone.second;
		}

		break;
	}
}

void AnimationPlayer::AnimationSpeed(float speed){
	m_Speed = speed;
}

void AnimationPlayer::AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed){
	m_RootPosMgnification = speed;
}

void AnimationPlayer::AnimationRootMode(const AnimMode mode){
	m_AnimMode = mode;
}

const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* AnimationPlayer::GetAnimationNowKeyFream() const{
	return &m_AnimationNowKeyFream;
}

const DirectX::SimpleMath::Vector3* AnimationPlayer::GetAnimationRootposNowKeyFream() const{
	return &m_AnimationRootposNowKeyFream;
}

const AnimationPlayer::AnimMode AnimationPlayer::GetAnimMode() const{
	return m_AnimMode;
}

void AnimationPlayer::AnimModeSwich(float nowfream){

	// 引数がtrueの時アニメーションの更新をする
	auto animmaxfream = static_cast<float>(m_pAnimationData->GetMaxFream());
	auto* meshtrans = m_pOwnerState->GetAnimState()->GetAnimController()->GetSkeletalMesh()->GetTransformComponent();

	switch (m_AnimMode){
	case AnimationPlayer::AnimMode::NoRootMotion:
		for (auto&& animbone : m_pAnimationData->GetKeyFreamData().GetAnimationKeyFreamMatrix(nowfream)) {
			m_AnimationNowKeyFream.at(animbone.first) = animbone.second;
		}
		break;

	case AnimationPlayer::AnimMode::Motion_To_Pos:
		for (auto&& animbone : m_pAnimationData->GetKeyFreamData().GetRootAnimationKeyFreamMatrix(nowfream)) {
			m_AnimationNowKeyFream.at(animbone.first) = animbone.second;
		}

		m_AnimationRootposNowKeyFream = m_pAnimationData->GetKeyFreamData().GetRootMotionOffsetPos(nowfream) * m_RootPosMgnification;

		break;
	case AnimationPlayer::AnimMode::Motion_Only:
		for (auto&& animbone : m_pAnimationData->GetKeyFreamData().GetRootAnimationKeyFreamMatrix(nowfream)) {
			m_AnimationNowKeyFream.at(animbone.first) = animbone.second;
		}
		break;
	}

	if (m_AnimNowCnt < animmaxfream - 1) {
		m_AnimNowCnt += (1.0f * m_Speed);
	}
	else {
		m_AnimNowCnt = 0;
	}
}

AnimationPlayer::AnimationPlayer(const std::string& animname, State* state):
	m_pAnimationData(state->GetAnimState()->GetAnimationData(animname)),
	m_pOwnerState(state),
	m_AnimationNowKeyFream(m_pAnimationData->GetKeyFreamData().GetAnimationKeyFreamMatrix(0)),
	m_Speed(1.0f),
	m_RootPosMgnification(1, 1, 1),
	m_AnimMode(AnimationPlayer::AnimMode::NoRootMotion)
{
	// アニメーションの追加
	state->AddAnimationPlayer(this);
}
