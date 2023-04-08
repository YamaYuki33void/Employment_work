#include "AnimationMontageAssets.h"

void AnimationMontageAssets::LoadInitalize(){

	{
		// RollingMontage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Rolling");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationRootPosSpeed(DirectX::SimpleMath::Vector3(0, 0, 2.0f));
		temp->AnimationStartFream(30.0f);
		temp->AnimationEndFreamDelete(10.0f);
		temp->AddNotify("EnableInput", 90.0f);
		temp->AddNotify("StartNextRolling", 110.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Rolling"].reset(temp);
	}

	{
		// Sward_Attack1 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack1");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(10.0f);
		temp->AddNotify("EnableInput", 30.0f);
		temp->AddNotify("StartNextAttack", 50.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack1"].reset(temp);
	}

	{
		// Sward_Attack2 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack2");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(35.0f);
		temp->AddNotify("EnableInput", 50.0f);
		temp->AddNotify("StartNextAttack", 70.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack2"].reset(temp);
	}

	{
		// Sward_Attack3 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack3");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationRootPosSpeed(DirectX::SimpleMath::Vector3(1.0, 0, 1.5));
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack3"].reset(temp);
	}

	{
		// Sward_Attack4 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack4");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(17.0f);
		temp->AddNotify("EnableInput", 25.0f);
		temp->AddNotify("StartNextAttack", 60.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack4"].reset(temp);
	}

	{
		// Sward_Attack5 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack5");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(20.0f);
		temp->AddNotify("EnableInput", 30.0f);
		temp->AddNotify("StartNextAttack", 80.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack5"].reset(temp);
	}

	{
		// Sward_Attack6 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack6");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(18.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack6"].reset(temp);
	}

	{
		// Sward_Attack7 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack7");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationRootPosSpeed(DirectX::SimpleMath::Vector3(0, 0, 1.5));
		temp->AddNotify("EnableInput", 40.0f);
		temp->AddNotify("StartNextAttack", 110.0f);
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack7"].reset(temp);
	}

	{
		// Sward_Attack8 Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_Attack8");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationStartFream(20.0f);
		temp->AnimationEndFreamDelete(20.0f);
		temp->AnimationRootPosSpeed(DirectX::SimpleMath::Vector3(0, 1, 1));
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_Attack8"].reset(temp);
	}

	{
		// Sward_Dash_Attack Montage
		auto* temp = new AnimationMontageData("Maria_Skeleton", "Sward_DashAttack");
		temp->AnimationRootMode(AnimationMontageData::AnimMode::Motion_To_Pos);
		temp->AnimationRootPosSpeed(DirectX::SimpleMath::Vector3(0, 0, 3));
		m_pAnimationMontageDataList["Maria_Skeleton"]["M_Sward_DashAttack"].reset(temp);
	}
}

AnimationMontageData* AnimationMontageAssets::GetAnimationMontage(const std::string& skeletalename, const std::string& montagename){

#ifdef _DEBUG

	// ÉÇÉìÉ^Å[ÉWÉÖÇÃåüçı
	if (m_pAnimationMontageDataList.count(skeletalename) != 0) {

		if (m_pAnimationMontageDataList.at(skeletalename).count(montagename) != 0) {

			return m_pAnimationMontageDataList.at(skeletalename).at(montagename).get();

		}
		else {
			MessageBoxA(nullptr, std::string(skeletalename + "  " + montagename + "  Not MongageData").c_str(), nullptr, MB_OK);
		}
	}
	else {
		MessageBoxA(nullptr, std::string(skeletalename + "  Not SkeletonName").c_str(), nullptr, MB_OK);
	}

#else

	return m_pAnimationMontageDataList.at(skeletalename).at(montagename).get();

#endif
}
