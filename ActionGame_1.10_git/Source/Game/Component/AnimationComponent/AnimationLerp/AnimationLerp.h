#pragma once
#include "../../../../System/DirectX/DirectX_Simple.h"

class AnimationLerp{
public:
	// ��ԊJ�n
	void StartLerp(const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* nextbone, float lerptime = 0.2f);

	// ��ԍX�V
	bool LerpUpdate();

private:
	// ��ԏ��߂̃{�[��
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_StartBone;
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_NextBone;
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_LerpBone;

private:
	// ��ԃt���O
	bool m_IsLerp;

	// �N�����v�l
	float m_Clump;

	// ��Ԏ���
	float m_Lerptime;

	// �o�ߎ���
	float m_ElapsedTime;

	// SkData
	class SkeletonData* m_pSkeletonData;

public:
	AnimationLerp(class SkeletonData* skdata);
	~AnimationLerp() {};
};

