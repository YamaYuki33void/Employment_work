#pragma once
#include "../../Manager/GuiManager/GuiManager.h"

class TreeComponent{
public:
	// �����Ƃ��Z�b�g
	virtual void SetComponentInfo(class Component* comp);

	// Tree�̍X�V
	virtual void TreeUpdate() = 0;
	virtual void TreeDraw() {};

	// Getter
	class Component& GetSelectComponent()const;

protected:
	class Component* m_pSelectComponent;

public:
	TreeComponent(class DetailsPanelGuiComponent* comp);
	virtual~TreeComponent() {};
};

