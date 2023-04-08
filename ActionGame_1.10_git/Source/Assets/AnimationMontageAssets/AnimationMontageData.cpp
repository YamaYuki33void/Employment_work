#include "AnimationMontageData.h"
#include "../../Assets/AnimationAssets/AnimationAssets.h"

void AnimationMontageData::AnimationRootMode(const AnimMode mode){
	m_AnimMode = mode;
}

void AnimationMontageData::AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed){
	m_RootPosMgnification = speed;
}

void AnimationMontageData::AnimationEndFreamDelete(const float offset){
	m_EndfreamDeleteOffset = offset;
}

void AnimationMontageData::AnimationStartFream(const float fream){
	m_StartFream = fream;
}

void AnimationMontageData::AddNotify(const std::string& notifyname, float notifyfream){
	m_NotifyList.emplace_back(Notify(notifyname, notifyfream));
}

void AnimationMontageData::AddNotify(const std::string& beginname, float beginfream, const std::string& endname, float endfream){
	m_NotifyWindowList.emplace_back(NotifyWindow(beginname, beginfream, endname, endfream));
}

const AnimationMontageData::AnimMode AnimationMontageData::GetAnimMode() const{
	return m_AnimMode;
}

const float AnimationMontageData::GetAnimMaxFream() const{
	return m_MaxFream - m_EndfreamDeleteOffset;
}

const float AnimationMontageData::GetAnimStartFream() const{
	return m_StartFream;
}

std::vector<class Notify>& AnimationMontageData::GetNotifyList(){
	return m_NotifyList;
}

std::vector<class NotifyWindow>& AnimationMontageData::GetNotifyWindowList(){
	return m_NotifyWindowList;
}

const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* AnimationMontageData::GetAnimationKeyFreamMatrix(float nowfream) const{

	switch (m_AnimMode){
	case AnimationMontageData::AnimMode::NoRootMotion:
		for (auto&& bone : m_pAnimationData->GetKeyFreamData().GetAnimationKeyFreamMatrix(nowfream)) {
			m_AnimationFreamMatrix.at(bone.first) = bone.second;
		}
		break;
	case AnimationMontageData::AnimMode::Motion_To_Pos:
	case AnimationMontageData::AnimMode::Motion_Only:
		for (auto&& bone : m_pAnimationData->GetKeyFreamData().GetRootAnimationKeyFreamMatrix(nowfream)) {
			m_AnimationFreamMatrix.at(bone.first) = bone.second;
		}
		break;
	} 

	return &m_AnimationFreamMatrix;
}

const DirectX::SimpleMath::Vector3* AnimationMontageData::GetAnimationRootPosKeyFream(float nowfream) const{
	m_AnimationRootPosKeyFream = m_pAnimationData->GetKeyFreamData().GetRootMotionOffsetPos(nowfream) * m_RootPosMgnification;

	return &m_AnimationRootPosKeyFream;
}

AnimationMontageData& AnimationMontageData::operator=(const AnimationMontageData& masterdata){

	this->m_pAnimationData             = masterdata.m_pAnimationData;
	this->m_AnimationFreamMatrix       = masterdata.m_AnimationFreamMatrix;
	this->m_AnimMode                   = masterdata.m_AnimMode;
	this->m_MaxFream               = masterdata.m_MaxFream;
	this->m_RootPosMgnification        = masterdata.m_RootPosMgnification;
	this->m_EndfreamDeleteOffset       = masterdata.m_EndfreamDeleteOffset;
	this->m_StartFream                 = masterdata.m_StartFream;
	this->m_NotifyList                 = masterdata.m_NotifyList;
	this->m_NotifyWindowList           = masterdata.m_NotifyWindowList;

	return *this;
}

AnimationMontageData::AnimationMontageData(const std::string& skeletonname, const std::string& animname) :
	m_pAnimationData(AnimationAssets::GetInstance()->GetAnimData(skeletonname, animname)->get()),
	m_AnimMode(AnimationMontageData::AnimMode::NoRootMotion),
	m_RootPosMgnification(1,1,1),
	m_EndfreamDeleteOffset(0),
	m_StartFream(0)
{
	m_MaxFream = static_cast<float>(m_pAnimationData->GetMaxFream());

	// ƒLƒƒƒbƒVƒ…‚ðì‚Á‚Ä‚¨‚­
	for (auto&& bone : m_pAnimationData->GetAnimationMatrixList()) {
		m_AnimationFreamMatrix[bone.first];
	}
}