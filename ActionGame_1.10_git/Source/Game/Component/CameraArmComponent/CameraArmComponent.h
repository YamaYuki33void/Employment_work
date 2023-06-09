#pragma once
#include "../Component.h"

class CameraArmComponent:
	public Component
{
public:
	// XY軸でのカメラの回転
	void AddRotaionYawInput(float axis);
	void AddRotaionPichInput(float axis);

	// Setter
	void SetAttachRootComponent(class TransformComponent* rootcomponent);

private:
	void UniqeUpdate()override;

private:
	// attachするobjectComponent
	class TransformComponent* m_pRootComponent;

public:
	CameraArmComponent(class Actor* actor, const std::string& ComponentName = "CameraArmComponent");
	~CameraArmComponent() override {};
};

