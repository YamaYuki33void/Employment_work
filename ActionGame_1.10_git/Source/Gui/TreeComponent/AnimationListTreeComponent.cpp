#include "AnimationListTreeComponent.h"
#include "../../Assets/AnimationAssets/AnimationAssets.h"
#include "../../System/Camera/Camera.h"

void AnimationListTreeComponent::SetComponentInfo(Component* comp){

	if (dynamic_cast<AnimationControllerComponent*>(comp)) {
		m_pSelectComponent = comp;

		auto& controller = *static_cast<AnimationControllerComponent*>(m_pSelectComponent);
		m_pAnimViewSkeletalMesh->SetModelData(controller.GetSkeletalMesh()->GetModelDataName());
	}
	else {
		m_pSelectComponent = nullptr;
		m_pAnimationData = nullptr;
	}
}

void AnimationListTreeComponent::TreeUpdate(){

	if (m_pSelectComponent == nullptr) {
		return;
	}

	auto& controller = *static_cast<AnimationControllerComponent*>(m_pSelectComponent);

	auto flg = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth;
	if (ImGui::TreeNodeEx("AnimationList", flg)) {

		auto& skdata = *controller.GetSkeletalMesh()->GetModelData()->GetSkeletonData();
		if (ImGui::TreeNodeEx(skdata.GetSkeletonName().c_str(), flg)) {
			const auto& animlist = AnimationAssets::GetInstance()->GetSkeletonToAnimData(skdata.GetSkeletonName());

			// アニメションのリスト表示
			for (auto&& anim : *animlist) {
				if (ImGui::TreeNodeEx(anim.first.c_str())) {

					if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
						m_pAnimationData = anim.second.get();
						m_AnimNowFream = 0.0f;
					}

					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}

	TimeLine();

	if (m_pAnimViewGuiComponent != nullptr) {
		m_pAnimViewGuiComponent->Update();
	}

	if (m_pAnimViewCamera != nullptr) {
		m_pAnimViewCamera->Update();
	}
}

void AnimationListTreeComponent::TreeDraw(){

	Camera::GetInstance()->Transform_Update(m_pAnimViewCamera->GetEye(), m_pAnimViewCamera->GetLock(), m_pAnimViewCamera->GetUp());

	if (m_pAnimViewGuiComponent != nullptr) {
		m_pAnimViewGuiComponent->Draw();
	}

	if (m_pAnimViewSkeletalMesh != nullptr) {
		m_pAnimViewSkeletalMesh->Draw();
	}
}

void AnimationListTreeComponent::TimeLine(){

	if (m_pAnimationData == nullptr) {
		return;
	}

	ImGui::Begin("AnimTimeLine");

	float maxfream = m_pAnimationData->GetMaxFream();
	ImGui::Text(std::string("MaxFream : " + std::to_string(maxfream)).c_str());
	ImGui::Text("");

	auto& skdata = *m_pAnimViewSkeletalMesh->GetModelData()->GetSkeletonData();
	skdata.SetAnimationBone(&m_pAnimationData->GetKeyFreamData().GetAnimationKeyFreamMatrix(m_AnimNowFream));

	static bool isplay = false;
	if (ImGui::Button("Play", ImVec2(60, 40))) {
		isplay = true;
	}

	ImGui::SameLine(); ImGui::SameLine();

	if (ImGui::Button("Stop", ImVec2(60, 40))) {
		isplay = false;
	}

	ImGui::Text("");

	ImGui::SliderFloat("KeyFream", &m_AnimNowFream, 0 , maxfream - 1);

	if (m_AnimNowFream < maxfream - 1) {

		if (isplay == true) {
			m_AnimNowFream++;
		}
	}
	else {
		m_AnimNowFream = 0.0f;
	}

	ImGui::End();
}

AnimationListTreeComponent::AnimationListTreeComponent(DetailsPanelGuiComponent* comp):
	TreeComponent(comp)
{
	// Sceranの作成
	m_pAnimViewGuiComponent.reset(new SceneViewGuiComponent(nullptr,"AnimationView"));
	m_pAnimViewSkeletalMesh.reset(new SkeletalMeshComponent(nullptr));
	m_pAnimViewCamera.reset(new CameraComponent(nullptr));

	m_pAnimViewCamera->SetTargetView();
	m_pAnimViewCamera->GetTransformComponent()->SetWorldRotation(DirectX::SimpleMath::Vector3(0, 180, 0));
	m_pAnimViewCamera->GetTransformComponent()->SetWorldLocation(DirectX::SimpleMath::Vector3(0, 100, 700));
}
