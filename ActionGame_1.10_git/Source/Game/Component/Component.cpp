#include "Component.h"
#include "../Actor/Actor.h"

void Component::Update(){

	UniqeUpdate();
}

void Component::Draw() {

	if (m_IsVisible) {
		UniqeDraw();
	}
}

void Component::SetIsVisible(const bool visible){
	m_IsVisible = visible;
}

Actor* Component::GetActor() const{
	return m_pActor;
}

const std::string& Component::GetComponentName() const{
	return m_ComponentName;
}

const Component::ComponentType Component::GetComponentType() const{
	return m_Type;
}

TransformComponent* Component::GetTransformComponent() const{
	return m_pTransformComponent.get();
}

Component::Component(class Actor* actor, const ComponentType type, const std::string& ComponentName) :
	m_pActor(actor),
	m_Type(type),
	m_ComponentName(ComponentName),
	m_IsVisible(true)
{
	// コンポーネントの追加
	if (actor != nullptr) {
		actor->GetComponentManager()->AddComponent(this);
	}

	if (type == ComponentType::ObjectType) {
		m_pTransformComponent = std::make_unique<TransformComponent>();
	}
}
