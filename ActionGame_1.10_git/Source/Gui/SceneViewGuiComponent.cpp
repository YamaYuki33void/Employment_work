#include "SceneViewGuiComponent.h"
#include "../System/Window/Window.h"
#include "../System/Camera/Camera.h"

void SceneViewGuiComponent::Update(){

	// ����̌��Ԃ𖄂߂�
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin(m_WindowName.c_str(), NULL, ImGuiWindowFlags_NoScrollbar);

	ImVec2 ViewPortPanelSize = ImGui::GetContentRegionAvail();

	// �A�X����v�Z���ēK�؂ȃT�C�Y�ɂ���
	Camera::GetInstance()->SetAspect(ViewPortPanelSize.x, ViewPortPanelSize.y);
	Camera::GetInstance()->CreateProjectionMatrix();

	// Model��`�悷��
	ImGui::Image((void*)m_pRenderTargetTexture->GetShaderResourceView().Get(), ViewPortPanelSize, ImVec2(-1, 0), ImVec2(0, 1));

	ImGui::PopStyleVar();
	ImGui::End();
}

void SceneViewGuiComponent::Draw(){

	float Color[] = { 1.f,0.2f,0.f,1.0f };
	m_pRenderTargetTexture->BeforeRender(Color);
	m_pRenderTargetTexture->SetRenderTarget();
}

SceneViewGuiComponent::SceneViewGuiComponent(GuiManager* manager, const std::string& windowname) :
	GuiComponent(manager),
	m_WindowName(windowname),
	m_pRenderTargetTexture(std::make_unique<DirectX_RenderTargetTexture>())
{
	// ���f����`�悷�邽�߂̃����_�[�^�[�Q�b�g�̍쐬
	float width  = static_cast<float>(Window::GetInstance()->GetScreanWidth());
	float height = static_cast<float>(Window::GetInstance()->GetScreanHeight());
	m_pRenderTargetTexture->CreateRenderTargetView(width, height);
}
