#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "Notify.h"

class AnimationMontageData{
public:
	enum class AnimMode {
		NoRootMotion,
		Motion_To_Pos,
		Motion_Only,
	};

	// ルートモーションの設定
	void AnimationRootMode(const AnimMode mode);

	// ルートモーション時の移動倍率変更
	void AnimationRootPosSpeed(const DirectX::SimpleMath::Vector3& speed);

	// けつからフレームを消すオフセット値の設定
	void AnimationEndFreamDelete(const float offset);

	// スタートフレームの設定
	void AnimationStartFream(const float fream);

	// 通知の追加
	void AddNotify(const std::string& notifyname, float notifyfream);
	void AddNotify(const std::string& beginname,  float beginfream, const std::string& endname, float endfream);

	// Getter
	const AnimMode GetAnimMode()const;
	const float GetAnimMaxFream()const;
	const float GetAnimStartFream()const;
	std::vector<class Notify>& GetNotifyList();
	std::vector<class NotifyWindow>& GetNotifyWindowList();
	const std::unordered_map<std::string, DirectX::SimpleMath::Matrix>* GetAnimationKeyFreamMatrix(float nowfream)const;
	const DirectX::SimpleMath::Vector3* GetAnimationRootPosKeyFream(float nowfream)const;

private:
	// 通知リスト
	std::vector<class Notify>       m_NotifyList;
	std::vector<class NotifyWindow> m_NotifyWindowList;

	// 現在のアニメーションのKeyFream
	mutable std::unordered_map<std::string, DirectX::SimpleMath::Matrix> m_AnimationFreamMatrix;

	// ルートモーション時のオフセット位置
	mutable DirectX::SimpleMath::Vector3 m_AnimationRootPosKeyFream;

	// ルートモーション時のオフセット移動地の倍率
	DirectX::SimpleMath::Vector3 m_RootPosMgnification;

	// 開始フレームの値
	float m_StartFream;

	// けつからフレームを消すオフセット値
	float m_EndfreamDeleteOffset;

	// 最大フレーム
	float m_MaxFream;
	
	// アニメーションデータ
	const class AnimationData* m_pAnimationData;

	// ルートモード
	AnimMode m_AnimMode;

public:
	AnimationMontageData& operator=(const AnimationMontageData& masterdata);
	AnimationMontageData(const std::string& skeletonname, const std::string& animname);
	AnimationMontageData() {};
	~AnimationMontageData() {};
};
