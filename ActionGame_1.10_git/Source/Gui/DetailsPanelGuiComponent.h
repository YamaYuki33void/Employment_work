#pragma once
#include "GuiComponent.h"

class DetailsPanelGuiComponent :
    public GuiComponent
{
public:
	// 詳細コンポーネントの選択
	void SetSelectComponent(class Component* comp);

	// 詳細パネルの追加
	void AddTreeComponent(class TreeComponent* comp);

private:
	void Update()override;
	void Draw()override;

private:
	// 詳細パネルのTreeリスト
	std::vector<std::unique_ptr<class TreeComponent>> m_pTreeComponentList;

public:
	DetailsPanelGuiComponent(class GuiManager* manager);
	~DetailsPanelGuiComponent()override {};
};

