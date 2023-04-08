#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../InterfaceAssets.h"
#include "AnimationData.h"

class AnimationAssets:
	public InterfaceAssets,public Singleton<AnimationAssets>
{
public:
	friend Singleton<AnimationAssets>;

	// ���񃍁[�h
	void LoadInitalize()override;

	// Getter
	const std::unordered_map<std::string, std::unique_ptr<class AnimationData>>* GetSkeletonToAnimData(const std::string& skeletonname)const;
	const std::unique_ptr<class AnimationData>* GetAnimData(const std::string& skeletonname, const std::string& animdata)const;

private:
	// �A�j���V�����̒ǉ�
	void AddAnimation(const std::string& skeletonname, const std::string& assetsname, const std::string& animationpath);

private:
	// �A�j���[�V�����f�[�^�̃��X�g
	std::unordered_map<std::string, std::unordered_map<std::string, std::unique_ptr<class AnimationData>>> m_AnimationList;

private:
	AnimationAssets() {};
	~AnimationAssets() {};
};

