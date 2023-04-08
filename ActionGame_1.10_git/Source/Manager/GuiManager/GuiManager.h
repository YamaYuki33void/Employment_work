#pragma once
#include "../../System/Imgui/imgui.h"
#include "../../System/Imgui/imgui_impl_dx11.h"
#include "../../System/Imgui/imgui_impl_win32.h"
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Gui/GuiComponent.h"

class GuiManager{
public:
	void Update();
	void Draw();

	// Gui�̒ǉ�
	void AddGuiComponent(class GuiComponent* comp);

	// Getter
	class Application& GetApplication()const;
	class DetailsPanelGuiComponent& GetDetailsPanelGuiComponent()const;

private:
	void ImGuiInitalize();
	void ImGuiUpdate();
	void ImGuiDraw();
	void ImGuiFinalize();

private:
	// GuiComponent���X�g
	std::vector<std::unique_ptr<class GuiComponent>> m_pGuiComponentList;

	// �ڍ׃p�l���R���|�[�l���g
	class DetailsPanelGuiComponent* m_pDetailsPanelGuiComponent;

	// Owner
	class Application* m_pOwnerApplication;

public:
	GuiManager(class Application* app);
	~GuiManager();
};

