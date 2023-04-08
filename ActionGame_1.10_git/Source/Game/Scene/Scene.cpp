#include "Scene.h"
#include "../../System/Camera/Camera.h"
#include "../Component/ComponentList.h"

void Scene::Update(){
	m_pActorManager->Update();
}

void Scene::Draw(){

	auto* cam = m_pIsValidCamera;
	Camera::GetInstance()->Transform_Update(cam->GetEye(), cam->GetLock(), cam->GetUp());

	m_pActorManager->Draw();
}

void Scene::SetIsValidCamera(const CameraComponent* camera){
	m_pIsValidCamera = camera;
}

const CameraComponent* Scene::GetValidCamera() const{
	return m_pIsValidCamera;
}

SceneManager* Scene::GetSceneManager() const{
	return m_pOwnerSceneManager;
}

ActorManager* Scene::GetActorManager() const{
	return m_pActorManager.get();
}

Scene::Scene(SceneManager* manager):
	m_pOwnerSceneManager(manager),
	m_pActorManager(std::make_unique<ActorManager>(this))
{
}
