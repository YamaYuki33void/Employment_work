#pragma once
#include "TreeComponent.h"
#include "../../Game/Component/ComponentList.h"
#include "../GuiComponentList.h"

class GameAbilityTagsTreeComponent :
	public TreeComponent
{
private:
	void SetComponentInfo(class Component* comp)override;
	void TreeUpdate()override;
	
public:
	GameAbilityTagsTreeComponent(class DetailsPanelGuiComponent* comp);
	~GameAbilityTagsTreeComponent() override {};
};

