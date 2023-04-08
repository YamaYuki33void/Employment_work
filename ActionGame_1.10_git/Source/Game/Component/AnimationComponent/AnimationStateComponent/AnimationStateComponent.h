#pragma once
#include "../../../../Assets/AnimationAssets/AnimationAssets.h"
#include "../../Component.h"
#include "State.h"

class AnimationStateComponent:
	public Component
{
public:
	// ステートの変更
	void ChangeState(const std::string& name);

	// ステートの追加
	void AddState(class State* state);

	// 条件一覧
	virtual void Conditionlist() = 0;

	// Getter
	const class AnimationData* GetAnimationData(const std::string& animname)const;
	class AnimationControllerComponent* GetAnimController()const;

private:
	virtual void AnimationStateUpdate() = 0;
	void UniqeUpdate()override;
	void StateUpdate();

private:
	// 現在のステート
	class State* m_pNowState;

	// ステートリスト
	std::unordered_map<std::string, std::unique_ptr<class State>>m_pStateList;

	// スケルトンの名前
	std::string m_SkeletonName;

	// スケルトンネームに基づいたアニメーションデータのリスト
	const std::unordered_map<std::string, std::unique_ptr<class AnimationData>>* m_pAnimationList;

	// オーナー
	class AnimationControllerComponent* m_pOwnerAnimController;

public:
	AnimationStateComponent(class AnimationControllerComponent* comp, const std::string& ComponentName = "AnimStateComponent");
	virtual ~AnimationStateComponent() override {};
};

