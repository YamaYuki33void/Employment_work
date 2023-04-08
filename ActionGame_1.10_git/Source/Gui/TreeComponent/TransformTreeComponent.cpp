#include "TransformTreeComponent.h"
#include "../../Game/Component/ComponentList.h"

void TransformTreeComponent::SetComponentInfo(Component* comp) {

	if (comp->GetTransformComponent() != nullptr) {
		m_pSelectComponent = comp;
	}
	else {
		m_pSelectComponent = nullptr;
	}
}

void TransformTreeComponent::TreeUpdate() {

	if (&m_pSelectComponent == nullptr) {
		return;
	}

	auto* trans = m_pSelectComponent->GetTransformComponent();

	auto flg = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;
	if (ImGui::TreeNodeEx("TransformComponent", flg)) {

		static int radiobutton = 0;
		ImGui::RadioButton("World", &radiobutton, 0); ImGui::SameLine();
		ImGui::RadioButton("Local", &radiobutton, 1);

		// ˆÚ“®ˆ—
		float location[3] = {};
		if (ImGui::DragFloat3("Location", location)) {

			auto offsetlocation = DirectX::XMFLOAT3(location[0], location[1], location[2]);

			if (radiobutton == 0) {
				trans->AddWorldOffset(offsetlocation);
			}
			else {
				trans->AddLocalOffset(offsetlocation);
			}

		}

		// ‰ñ“]ˆ—
		float rotation[3] = {};
		if (ImGui::DragFloat3("Rotation", rotation)) {

			auto offsetrotation = DirectX::XMFLOAT3(rotation[0], rotation[1], rotation[2]);

			if (radiobutton == 0) {
				trans->AddWorldRotation(offsetrotation);
			}
			else {
				trans->AddLocalRotation(offsetrotation);
			}

		}

		// Ú×ƒf[ƒ^
		if (radiobutton == 0) {

			ImGui::Text("");
			ImGui::Text("WorldLocation");
			ImGui::Text(std::string("x : " + std::to_string(trans->GetWorldLocation().x)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("y : " + std::to_string(trans->GetWorldLocation().y)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("z : " + std::to_string(trans->GetWorldLocation().z)).c_str());

			ImGui::Text("");
			ImGui::Text("WorldRotation");
			ImGui::Text(std::string("x : " + std::to_string(trans->GetWorldRotation().x)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("y : " + std::to_string(trans->GetWorldRotation().y)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("z : " + std::to_string(trans->GetWorldRotation().z)).c_str());
		}

		if (radiobutton == 1) {

			ImGui::Text("");
			ImGui::Text("LocalLocation");
			ImGui::Text(std::string("x : " + std::to_string(trans->GetLocalLocation().x)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("y : " + std::to_string(trans->GetLocalLocation().y)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("z : " + std::to_string(trans->GetLocalLocation().z)).c_str());

			ImGui::Text("");
			ImGui::Text("LocalRotation");
			ImGui::Text(std::string("x : " + std::to_string(trans->GetLocalRotation().x)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("y : " + std::to_string(trans->GetLocalRotation().y)).c_str()); ImGui::SameLine();
			ImGui::Text(std::string("z : " + std::to_string(trans->GetLocalRotation().z)).c_str());
		}
	}

	ImGui::TreePop();
}

TransformTreeComponent::TransformTreeComponent(DetailsPanelGuiComponent* comp) :
	TreeComponent(comp)
{
}
