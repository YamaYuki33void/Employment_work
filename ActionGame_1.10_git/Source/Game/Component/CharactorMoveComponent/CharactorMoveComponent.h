#pragma once
#include "../ModelComponent/ModelComponent.h"
#include "../../Actor/CharactorActor.h"

//-----------------------------------------------
// �J�����̕����x�N�g���ɏ��炵���ړ�
//-----------------------------------------------

class CharactorMoveComponent:
	public Component
{
public:
	// ���ړ�
	void AddMoveInput(const DirectX::SimpleMath::Vector2& vec2);

	// �ő呬�x�ݒ�
	void SetMaxSpeed(float speed);

private:
	// �ő�X�s�[�h
	float m_MaxSpeed;

	// ��]���̕�ԌW��
	float m_RotatonLerpValue;

	// ���f���R���|�[�l���g
	class ModelComponent* m_pModel;

	// �J�����R���|�l���g
	class CameraComponent* m_pCamera;

public:
	CharactorMoveComponent(class ModelComponent* comp, class CameraComponent*comp1 = nullptr, const std::string& ComponentName = "CharactorMoveComponent");
	~CharactorMoveComponent() override{};
};

