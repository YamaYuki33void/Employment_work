#include "CharactorMoveComponent.h"
#include "../ComponentList.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CharactorMoveComponent::AddMoveInput(const DirectX::SimpleMath::Vector2& vec2){

	// 入力値の受け取り
	auto m_InputAxis = vec2;

	if (m_InputAxis.x == 0.0f && m_InputAxis.y == 0.0f) {
		return;
	}

	// 斜め入力の補正
	if (m_InputAxis.x * m_InputAxis.x + m_InputAxis.y * m_InputAxis.y > 0.000001f) {
		float a = (fabs(m_InputAxis.x) >= fabs(m_InputAxis.y)) ? m_InputAxis.y / m_InputAxis.x : m_InputAxis.x / m_InputAxis.y;       //絶対値の小さい方を大きい方で割る
		float b = 1.0f / sqrt(1.0f + a * a);

		m_InputAxis.x *= b;
		m_InputAxis.y *= b;
	}

	float StickAngle = 0.0f;

	// カメラのy軸の値を取得
	if (m_pCamera != nullptr) {
		float roty = m_pCamera->GetTransformComponent()->GetWorldRotation().y;

		// 入力値から角度(Deg)を取得
		StickAngle = XMConvertToDegrees(atan2f(m_InputAxis.x, m_InputAxis.y)) + roty;
		if (StickAngle < 0) {
			StickAngle += 360;
		}
	}

	// スティックの角度にカメラアームの回転角度を足した角度のQtを作る
	Quaternion CharaRotQt = Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), XMConvertToRadians(StickAngle));
	auto* MeshTransfrom = m_pModel->GetTransformComponent();
	MeshTransfrom->SetWorldRotation(Quaternion::Slerp(MeshTransfrom->GetWorldQtRotation(), CharaRotQt, m_RotatonLerpValue));
	MeshTransfrom->AddLocalOffset(XMFLOAT3(0, 0, (m_MaxSpeed / 60)));
}

void CharactorMoveComponent::SetMaxSpeed(float speed){
	m_MaxSpeed = speed;
}

CharactorMoveComponent::CharactorMoveComponent(class ModelComponent* comp, class CameraComponent* comp1, const std::string& ComponentName):
	Component(comp->GetActor(), ComponentType::FuncType, ComponentName),
	m_RotatonLerpValue(0.25f),
	m_MaxSpeed(600),
	m_pModel(comp),
	m_pCamera(comp1)
{
}
