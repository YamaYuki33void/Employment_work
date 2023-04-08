#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../InterfaceAssets.h"
#include "AnimationMontageData.h"

class AnimationMontageAssets :
	public InterfaceAssets, public Singleton<AnimationMontageAssets>
{
public:
	friend Singleton<AnimationMontageAssets>;

	// 初回ロード
	void LoadInitalize()override;

	// Getter
	class AnimationMontageData* GetAnimationMontage(const std::string& skeletalename, const std::string& montagename);

private:
	// アニメーションモンタージュデータリスト
	std::unordered_map<std::string, std::unordered_map<std::string, std::unique_ptr<class AnimationMontageData>>> m_pAnimationMontageDataList;

private:
	AnimationMontageAssets() {};
	~AnimationMontageAssets() {};
};
