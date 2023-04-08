#include "DetailsPanelGuiComponent.h"
#include "GuiComponentList.h"

void DetailsPanelGuiComponent::SetSelectComponent(Component* comp){

	for (auto&& tree : m_pTreeComponentList) {
		tree->SetComponentInfo(comp);
	}
}

void DetailsPanelGuiComponent::AddTreeComponent(TreeComponent* comp){
	m_pTreeComponentList.emplace_back(comp);
}

void DetailsPanelGuiComponent::Update(){

	//　選択したComponentの詳細パネル
	ImGui::Begin("DetailsPanel");

	for (auto&& tree : m_pTreeComponentList) {

		if (&tree->GetSelectComponent() != nullptr) {
			tree->TreeUpdate();
		}
	}

	ImGui::End();
}

void DetailsPanelGuiComponent::Draw(){

	for (auto&& tree : m_pTreeComponentList) {

		if (&tree->GetSelectComponent() != nullptr) {
			tree->TreeDraw();
		}
	}
}

DetailsPanelGuiComponent::DetailsPanelGuiComponent(GuiManager* manager):
	GuiComponent(manager)
{
	// TransformTreeの追加
	new TransformTreeComponent(this);
	
	// AnimationListの表示
	//new AnimationListTreeComponent(this);

	//// GamePlayAblityの表示
	new GameAbilityTagsTreeComponent(this);
}
