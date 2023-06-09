#include "GuiComponent.h"

GuiManager& GuiComponent::GetGuiManager() const{
	return *m_pOwnerGuiManager;
}

GuiComponent::GuiComponent(GuiManager* manager):
	m_pOwnerGuiManager(manager)
{
	//　GuiManagerに追加する
	if (manager != nullptr) {
		manager->AddGuiComponent(this);
	}
}
