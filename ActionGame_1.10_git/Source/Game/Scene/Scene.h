#pragma once
#include "../../Manager/ActorManager/ActorManager.h"

class Scene{
public:
	void Update();
	void Draw();

	// Setter
	void SetIsValidCamera(const class CameraComponent* camera);
	const class CameraComponent* GetValidCamera()const;
	
	// Getter
	class SceneManager* GetSceneManager()const;
	class ActorManager* GetActorManager()const;

private:
	// ActorManager
	std::unique_ptr<class ActorManager> m_pActorManager;

	// 現在有効になっているカメラ
	const class CameraComponent* m_pIsValidCamera;

	// SceneManagerOwnerポインタ
	class SceneManager* m_pOwnerSceneManager;

public:
	Scene(class SceneManager* manager);
	virtual ~Scene() {};
};

