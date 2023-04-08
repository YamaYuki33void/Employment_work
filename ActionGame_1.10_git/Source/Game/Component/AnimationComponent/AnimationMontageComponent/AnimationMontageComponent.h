#pragma once
#include <functional>
#include "../../../../System/DirectX/DirectX_Simple.h"
#include "../../Component.h"
#include "../../../../Assets/AnimationMontageAssets/AnimationMontageData.h"
#include "../easing.h"

class AnimationMontageComponent:
	public Component
{
public:
	enum class NotifyType {
		Completed, Interrupted, NotifyBegin, NotifyEnd
	};

	// モンタージュ再生
	void PlayMontage(const std::string& montagename, float late = 1.0f, easing_functions easing = easing_functions::EaseNone);

	// 関数ポインタの追加
	void AddFanction(std::function<void()> fanc, NotifyType type);

	// Getter
	const bool GetIsPlay()const;
	const std::vector<std::string>& GetNotifyNameList()const;

private:
	void UniqeUpdate();

	// 通知の更新
	void NotifyUpdate(float nowfream);

	// 関数ポインタ削除
	void FunctionListAllDelete();

	// 関数ポインタ実行
	void OnCompletedListActivation();
	void OnInterruptedActivation();
	void OnNotifyBeginActivation();
	void OnNotifyEndActivation();

private:
	
	// アニメーションデータ
	class AnimationMontageData m_MontageData;

	// 現在のフレームカウント
	float m_AnimNowFreamCnt;

	// 再生フラグ
	bool m_IsPlay;

	//　再生レート
	float m_late;

	// アニメーションカーブ
	easing_functions m_Ease;

	// 関数ポインタ格納
	std::vector<std::function<void()>> m_OnCompletedList;
	std::vector<std::function<void()>> m_OnInterruptedList;
	std::vector<std::function<void()>> m_OnNotifyBeginList;
	std::vector<std::function<void()>> m_OnNotifyEndList;
	std::vector<std::string> m_NotifyNameList;

	// オーナ
	class AnimationControllerComponent* m_pOwnerAnimController;

public:
	AnimationMontageComponent(class AnimationControllerComponent* comp, const std::string& ComponentName = "AnimMontageComponent");
	~AnimationMontageComponent() override {};
};

