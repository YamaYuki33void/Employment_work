#pragma once
#include "../../../../System/DirectX/DirectX_Simple.h"
#include "AnimationPlayer/AnimationPlayer.h"

class State{
public:
	// ステート固有の動き
	virtual void Update() = 0;
	virtual void OnEnter() {};
	virtual void OnExit() {};

	// ステート変更
	void ChangeState(const std::string& statename);

	// アニメーションの追加
	void AddAnimationPlayer(class AnimationPlayer* data);

	// Getter
	const std::string& GetStateName()const;
	class AnimationStateComponent* GetAnimState()const;

	// Setter
	void SetAnimation(class AnimationPlayer* animadata);
	
private:
	// ステート名
	std::string m_StateName;

	// アニメーションの再生管理
	std::vector<std::unique_ptr<class AnimationPlayer>> m_pAnimationPlayerList;

	// オーナー
	class AnimationStateComponent* m_pOwnerAnimState;

public:
	State(class AnimationStateComponent* comp, const std::string& statename);
	virtual~State() {};
};

