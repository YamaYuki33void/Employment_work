#pragma once
#include "../../Manager/GuiManager/GuiManager.h"

class TreeComponent{
public:
	// 情報もとをセット
	virtual void SetComponentInfo(class Component* comp);

	// Treeの更新
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

