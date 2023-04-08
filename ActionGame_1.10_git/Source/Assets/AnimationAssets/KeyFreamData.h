#pragma once
#include "../../System/DirectX/DirectX_Simple.h"

//----------------------------------------------------------------
// �t���[���w��ł̃A�j���[�V�����f�[�^�̎��o��
//----------------------------------------------------------------

class KeyFreamData{
public:
	// Getter
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>& GetAnimationKeyFreamMatrix(float fream)const;
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>& GetRootAnimationKeyFreamMatrix(float fream)const;
	const DirectX::SimpleMath::Vector3& GetRootMotionOffsetPos(float fream) const;

private:
	// �A�j���V�����s��̕��
	const DirectX::SimpleMath::Matrix& CreateLerpMatrix(const std::string& bonename,float fream)const;

private:
	// �L���b�V��
	mutable std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_kyashMatList;
	mutable DirectX::SimpleMath::Matrix m_kyashMat;
	mutable DirectX::SimpleMath::Vector3 m_kyashVec;

	// Owner
	class AnimationData* m_pOwnerAnimationData;

public:
	KeyFreamData(class AnimationData* data);
	~KeyFreamData() {};
};

