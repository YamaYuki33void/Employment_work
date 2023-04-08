#include "GuiComponent.h"

GuiManager& GuiComponent::GetGuiManager() const{
	return *m_pOwnerGuiManager;
}

GuiComponent::GuiComponent(GuiManager* manager):
	m_pOwnerGuiManager(manager)
{
	//@GuiManager‚É’Ç‰Á‚·‚é
	if (manager != nullptr) {
		manager->AddGuiComponent(this);
	}
}
