#include "Actor.h"
#include "../../Game/Scene/Scene.h"

void Actor::Update(){

	// コンポーネントの更新
	m_pComponentManager->Update();

	// Actor固有の更新処理
	UniqeUpdate();
}

void Actor::Draw(){

	// コンポーネントの描画
	m_pComponentManager->Draw();
}

const Actor::State Actor::GetState() const{
	return m_State;
}

const std::string& Actor::GetActorName() const{
	return m_ActorName;
}

ComponentManager* Actor::GetComponentManager() const{
	return m_pComponentManager.get();
}

Scene* Actor::GetScene() const{
	return m_pOwnerScene;
}

Actor::Actor(Scene* scene, const std::string& ActorName):
	m_pOwnerScene(scene),
	m_ActorName(ActorName),
	m_pComponentManager(std::make_unique<ComponentManager>(this))
{
	// Actorの追加
	scene->GetActorManager()->AddActor(this);
}
