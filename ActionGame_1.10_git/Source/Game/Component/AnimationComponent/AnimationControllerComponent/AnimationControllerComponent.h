#pragma once
#include "../../Component.h"

class AnimationControllerComponent:
	public Component
{
public:
	// ステートコンポーネントのセット
	void SetAnimState(class AnimationStateComponent* state);

	// Getter
	class AnimationStateComponent* GetAnimState()const;
	class AnimationMontageComponent* GetAnimMontage()const;
	class SkeletalMeshComponent* GetSkeletalMesh()const;
	class AnimationLerp* GetAnimLerp()const;

private:
	// ステートコンポーネント
	class AnimationStateComponent* m_pAnimState;

	// モンタージュコンポーネント
	class AnimationMontageComponent* m_pAnimMontage;

	// アニメーションの補間
	std::unique_ptr<class AnimationLerp> m_pAnimationLerp;

	// オーナー
	class SkeletalMeshComponent* m_pOwnerSkeletalMesh;

public:
	AnimationControllerComponent(class SkeletalMeshComponent* comp,const std::string& ComponentName = "AnimControllerComponent");
	~AnimationControllerComponent()override {};
};

