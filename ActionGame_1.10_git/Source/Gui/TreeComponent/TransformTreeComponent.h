#pragma once
#include "TreeComponent.h"

class TransformTreeComponent :
    public TreeComponent
{
private:
	void SetComponentInfo(class Component* comp)override;

	// Tree�̍X�V
	void TreeUpdate()override;

public:
	TransformTreeComponent(class DetailsPanelGuiComponent* comp);
	~TransformTreeComponent() override{};
};

