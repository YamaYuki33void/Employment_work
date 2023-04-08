#include "ActorHierarchyGuiComponent.h"
#include "../System/Application/Application.h"
#include "../Game/Component/ComponentList.h"
#include "../Gui/GuiComponentList.h"

void ActorHierarchyGuiComponent::Update(){

	// Actorのリストを取得
	const auto& actorlist = GetGuiManager().GetApplication().GetSceneManager().GetScene()->GetActorManager()->GetActorList();

	// Actorの列挙
	ImGui::Begin("ActorHierarchyView");

	for (auto&& actor : actorlist) {

		auto flg = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;

		// Actorの一覧

		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(250, 0, 0, 255));
		if (ImGui::TreeNodeEx(actor->GetActorName().c_str(), flg)) {
			ImGui::PopStyleColor();

			// Componentの一覧
			const auto& componentlist = actor->GetComponentManager()->GetComponentList();
			ObjectComponentHierarhy(componentlist);
			FuncComponentHierarhy(componentlist);

			ImGui::TreePop();
		}
	}

	ImGui::End();
}

void ActorHierarchyGuiComponent::ObjectComponentHierarhy(const std::vector<std::unique_ptr<class Component>>& list){

	// ObjectTypeのコンポーネントを表示

	auto flg = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
	bool open = ImGui::TreeNodeEx("ObjectComponentList", flg);

	if (!open) {
		ImGui::PopStyleColor();
	}

	if (open) {
		ImGui::PopStyleColor();

		for (int i = 0; i < list.size(); i++) {

			auto flg = ImGuiTreeNodeFlags_Leaf;
			if (list.at(i)->GetComponentType() == Component::ComponentType::ObjectType) {
				if (ImGui::TreeNodeEx(list.at(i)->GetComponentName().c_str(), flg)) {

					if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {

						// Componentの選択
						GetGuiManager().GetDetailsPanelGuiComponent().SetSelectComponent(list.at(i).get());
					}

					ImGui::TreePop();
				}
			}
		}

		ImGui::TreePop();
	}
}

void ActorHierarchyGuiComponent::FuncComponentHierarhy(const std::vector<std::unique_ptr<class Component>>& list){

	auto flg = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
	bool open = ImGui::TreeNodeEx("FuncComponentList", flg);

	if (!open) {
		ImGui::PopStyleColor();
	}

	if (open) {
		ImGui::PopStyleColor();

		for (int i = 0; i < list.size(); i++) {
			if (list.at(i)->GetComponentType() == Component::ComponentType::FuncType) {

				auto flg = ImGuiTreeNodeFlags_Leaf;
				if (ImGui::TreeNodeEx(list.at(i)->GetComponentName().c_str(), flg)) {

					if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {

						// Componentの選択
						GetGuiManager().GetDetailsPanelGuiComponent().SetSelectComponent(list.at(i).get());
					}
					ImGui::TreePop();
				}
			}
		}

		ImGui::TreePop();
	}
}


ActorHierarchyGuiComponent::ActorHierarchyGuiComponent(GuiManager* manager):
	GuiComponent(manager)
{
}
