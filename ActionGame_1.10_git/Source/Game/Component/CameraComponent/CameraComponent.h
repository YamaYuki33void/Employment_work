#pragma once
#include "../Component.h"

class CameraComponent:
	public Component
{
public:
	// �J������L���ɂ���
	static void SetTargetView(const class CameraComponent* camera);
	void SetTargetView();

	// ���ݗL���ȃJ�������擾����
	static const class CameraComponent* GetValidCamera();

	// Getter
	const DirectX::SimpleMath::Vector3& GetEye()const;
	const DirectX::SimpleMath::Vector3& GetLock()const;
	const DirectX::SimpleMath::Vector3& GetUp()const;

private:
	void UniqeUpdate()override;

private:
	// �J�����ϐ�
	DirectX::SimpleMath::Vector3 m_Eye, m_Lock, m_Up;

	// �L���t���O
	bool m_IsValid;

	// �J�����R���|�[�l���g���X�g
	static std::vector<class CameraComponent*> m_pCameraComponentList;

public:
	CameraComponent(class Actor* actor, const std::string& ComponentName = "CameraComponent");
	~CameraComponent() override{};
};

