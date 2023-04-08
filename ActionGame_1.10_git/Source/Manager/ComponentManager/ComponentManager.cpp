#include "ComponentManager.h"

void ComponentManager::Update(){

	for (auto&& component : m_pComponentList) {
		component->Update();
	}
}

void ComponentManager::Draw(){

	for (auto&& component : m_pComponentList) {
		component->Draw();
	}
}

void ComponentManager::AddComponent(Component* component){

	// Component‚Ì’Ç‰Á
	m_pComponentList.emplace_back(std::move(component));
}

const std::vector<std::unique_ptr<class Component>>& ComponentManager::GetComponentList() const{
	return m_pComponentList;
}

Actor* ComponentManager::GetActor() const{
	return m_pOwnerActor;
}

ComponentManager::ComponentManager(Actor* actor):
	m_pOwnerActor(actor)
{
}
