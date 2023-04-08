#pragma once
#include "../../../../System/DirectX/DirectX_Simple.h"

class AnimationLerp{
public:
	// 補間開始
	void StartLerp(const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* nextbone, float lerptime = 0.2f);

	// 補間更新
	bool LerpUpdate();

private:
	// 補間初めのボーン
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_StartBone;
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_NextBone;
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_LerpBone;

private:
	// 補間フラグ
	bool m_IsLerp;

	// クランプ値
	float m_Clump;

	// 補間時間
	float m_Lerptime;

	// 経過時間
	float m_ElapsedTime;

	// SkData
	class SkeletonData* m_pSkeletonData;

public:
	AnimationLerp(class SkeletonData* skdata);
	~AnimationLerp() {};
};

