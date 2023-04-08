#include "TreeComponent.h"
#include "../DetailsPanelGuiComponent.h"

void TreeComponent::SetComponentInfo(Component* comp){
	m_pSelectComponent = comp;
}

Component& TreeComponent::GetSelectComponent() const{
	return *m_pSelectComponent;
}

TreeComponent::TreeComponent(DetailsPanelGuiComponent* comp):
	m_pSelectComponent(nullptr)
{
	comp->AddTreeComponent(this);
}

