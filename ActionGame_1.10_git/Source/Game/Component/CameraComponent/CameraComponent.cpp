#include "CameraComponent.h"
#include "../../../System/Camera/Camera.h"
#include "../../Actor/Actor.h"
#include "../../Scene/Scene.h"

using namespace DirectX::SimpleMath;

// カメラコンポーネントリスト
std::vector<class CameraComponent*>CameraComponent::m_pCameraComponentList;

void CameraComponent::SetTargetView(const CameraComponent* camera){

	// 全部のカメラの有効化を切る
	for (auto&& cam : m_pCameraComponentList) {
		cam->m_IsValid = false;
	}

	for (auto&& cam : m_pCameraComponentList) {
		if (cam == camera) {
			cam->m_IsValid = true;
			cam->GetActor()->GetScene()->SetIsValidCamera(cam);
		}
	}
}

void CameraComponent::SetTargetView(){

	// 全部のカメラの有効化を切る
	for (auto&& cam : m_pCameraComponentList) {
		cam->m_IsValid = false;
	}

	m_IsValid = true;
	GetActor()->GetScene()->SetIsValidCamera(this);
}

const CameraComponent* CameraComponent::GetValidCamera(){

	for (auto&& cam : m_pCameraComponentList) {
		if (cam->m_IsValid == true) {
			return cam;
		}
	}

	MessageBoxA(nullptr, "Now IsValid Not Camera", nullptr, MB_OK);
	return nullptr;
}

const DirectX::SimpleMath::Vector3& CameraComponent::GetEye() const{
	return m_Eye;
}

const DirectX::SimpleMath::Vector3& CameraComponent::GetLock() const{
	return m_Lock;
}

const DirectX::SimpleMath::Vector3& CameraComponent::GetUp() const{
	return m_Up;
}

void CameraComponent::UniqeUpdate(){

	auto* trans = GetTransformComponent();
	auto* camera = Camera::GetInstance();

	if (m_IsValid) {

		m_Eye = trans->GetWorldLocation();
		m_Lock = trans->GetWorldLocation() + trans->GetWorldMatrix().Backward();
		m_Up = trans->GetWorldMatrix().Up();
	}
}

CameraComponent::CameraComponent(Actor* actor, const std::string& ComponentName):
	Component(actor,ComponentType::ObjectType,ComponentName),
	m_IsValid(false)
{
}
