#include "CameraArmComponent.h"

using namespace DirectX::SimpleMath;

void CameraArmComponent::AddRotaionYawInput(float axis){

	// YŽ²Žü‚è‚Ì‰ñ“]
	GetTransformComponent()->AddWorldRotation(Vector3(0, axis, 0));
}

void CameraArmComponent::AddRotaionPichInput(float axis){

	// XŽ²‰ñ‚è‚Ì‰ñ“]
	GetTransformComponent()->AddLocalRotation(Vector3(axis, 0, 0));
}

void CameraArmComponent::SetAttachRootComponent(TransformComponent* rootcomponent){
	m_pRootComponent = rootcomponent;
}

void CameraArmComponent::UniqeUpdate(){

	if (m_pRootComponent != nullptr) {
		GetTransformComponent()->SetWorldLocation(m_pRootComponent->GetWorldLocation());
	}
}

CameraArmComponent::CameraArmComponent(Actor* actor, const std::string& ComponentName):
	Component(actor,ComponentType::ObjectType,ComponentName)
{
}
