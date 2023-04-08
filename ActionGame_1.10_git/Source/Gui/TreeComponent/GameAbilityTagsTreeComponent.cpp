#include "GameAbilityTagsTreeComponent.h"

void GameAbilityTagsTreeComponent::SetComponentInfo(Component* comp){

	if (dynamic_cast<GameplayAbilitySystemComponent*>(comp)) {
		m_pSelectComponent = comp;
	}
	else {
		m_pSelectComponent = nullptr;
	}
}

void GameAbilityTagsTreeComponent::TreeUpdate(){

	if (m_pSelectComponent == nullptr) {
		return;
	}

	ImGui::Text("ActtivationRequwirTags");
	ImGui::Text("");

	auto& gascomp = *static_cast<GameplayAbilitySystemComponent*>(m_pSelectComponent);

	for (auto&& tags : gascomp.GetAbilityTags()) {
		ImGui::Text(tags.c_str());
	}
}

GameAbilityTagsTreeComponent::GameAbilityTagsTreeComponent(DetailsPanelGuiComponent* comp):
	TreeComponent(comp)
{
}
