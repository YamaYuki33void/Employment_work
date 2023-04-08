#pragma once
#include "GuiComponent.h"

class DetailsPanelGuiComponent :
    public GuiComponent
{
public:
	// �ڍ׃R���|�[�l���g�̑I��
	void SetSelectComponent(class Component* comp);

	// �ڍ׃p�l���̒ǉ�
	void AddTreeComponent(class TreeComponent* comp);

private:
	void Update()override;
	void Draw()override;

private:
	// �ڍ׃p�l����Tree���X�g
	std::vector<std::unique_ptr<class TreeComponent>> m_pTreeComponentList;

public:
	DetailsPanelGuiComponent(class GuiManager* manager);
	~DetailsPanelGuiComponent()override {};
};

