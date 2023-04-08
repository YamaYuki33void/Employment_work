#pragma once
#include "../../../../../System/DirectX/DirectX_Simple.h"

class AnimationPlayer{
public:
	enum class AnimMode {
		NoRootMotion,
		Motion_To_Pos,
		Motion_Only,
	};

	// アニメーションの更新
	void AnimationUpdate(bool isupdate = true);

	// アニメーションのフレームカウント変更
	void AnimationReset(float resetfream = 0.0f);

	// アニメーションのスピード倍率変更
	void AnimationSpeed(float speed);

	// ルートモーション時の移動倍率変更
	void AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed);

	// ルートモーションの設定
	void AnimationRootMode(const AnimMode mode);

	// Getter
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* GetAnimationNowKeyFream()const;
	const DirectX::SimpleMath::Vector3* GetAnimationRootposNowKeyFream()const;
	const AnimMode GetAnimMode()const;

private:
	void AnimModeSwich(float nowfream);

private:
	// アニメーションデータ
	const class AnimationData* m_pAnimationData;

	// 現在のアニメーションのKeyFream
	std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_AnimationNowKeyFream;

	// ルートモーション使用時の時のオフセット位置
	DirectX::SimpleMath::Vector3 m_AnimationRootposNowKeyFream;

	// ルートモーション時のオフセット移動地の倍率
	DirectX::SimpleMath::Vector3 m_RootPosMgnification;

	// アニメーションのスピード
	float m_Speed;

	// アニメーションカウント
	float m_AnimNowCnt;

	// ルートモーションのモード
	AnimMode m_AnimMode;

	// オーナー
	class State* m_pOwnerState;

public:
	AnimationPlayer(const std::string& animname, class State* state);
	~AnimationPlayer() {};
};

