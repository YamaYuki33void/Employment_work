#pragma once
#include "../Component.h"

class CameraComponent:
	public Component
{
public:
	// カメラを有効にする
	static void SetTargetView(const class CameraComponent* camera);
	void SetTargetView();

	// 現在有効なカメラを取得する
	static const class CameraComponent* GetValidCamera();

	// Getter
	const DirectX::SimpleMath::Vector3& GetEye()const;
	const DirectX::SimpleMath::Vector3& GetLock()const;
	const DirectX::SimpleMath::Vector3& GetUp()const;

private:
	void UniqeUpdate()override;

private:
	// カメラ変数
	DirectX::SimpleMath::Vector3 m_Eye, m_Lock, m_Up;

	// 有効フラグ
	bool m_IsValid;

	// カメラコンポーネントリスト
	static std::vector<class CameraComponent*> m_pCameraComponentList;

public:
	CameraComponent(class Actor* actor, const std::string& ComponentName = "CameraComponent");
	~CameraComponent() override{};
};

