#pragma once
#include "../ModelComponent/ModelComponent.h"
#include "../../Actor/CharactorActor.h"

//-----------------------------------------------
// カメラの方向ベクトルに遵守した移動
//-----------------------------------------------

class CharactorMoveComponent:
	public Component
{
public:
	// 軸移動
	void AddMoveInput(const DirectX::SimpleMath::Vector2& vec2);

	// 最大速度設定
	void SetMaxSpeed(float speed);

private:
	// 最大スピード
	float m_MaxSpeed;

	// 回転時の補間係数
	float m_RotatonLerpValue;

	// モデルコンポーネント
	class ModelComponent* m_pModel;

	// カメラコンポネント
	class CameraComponent* m_pCamera;

public:
	CharactorMoveComponent(class ModelComponent* comp, class CameraComponent*comp1 = nullptr, const std::string& ComponentName = "CharactorMoveComponent");
	~CharactorMoveComponent() override{};
};

