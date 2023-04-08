#pragma once
#include "GuiComponent.h"

class ActorHierarchyGuiComponent :
    public GuiComponent
{
private:
	 void Update()override;

	 void ObjectComponentHierarhy(const std::vector<std::unique_ptr<class Component>>& list);
	 void FuncComponentHierarhy(const std::vector<std::unique_ptr<class Component>>& list);

public:
	ActorHierarchyGuiComponent(class GuiManager* manager);
	~ActorHierarchyGuiComponent()override {};
};

