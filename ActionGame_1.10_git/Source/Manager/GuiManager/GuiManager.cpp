#include "GuiManager.h"
#include "../../System/Window/Window.h"
#include "../../Gui/GuiComponentList.h"

void GuiManager::Update(){

	ImGuiUpdate();

	for (auto&& gui : m_pGuiComponentList) {
		gui->Update();
	}
}

void GuiManager::Draw(){

	ImGuiDraw();

	for (auto&& gui : m_pGuiComponentList) {
		gui->Draw();
	}
}

void GuiManager::AddGuiComponent(GuiComponent* comp){
	m_pGuiComponentList.emplace_back(comp);
}

Application& GuiManager::GetApplication() const{
	return *m_pOwnerApplication;
}

DetailsPanelGuiComponent& GuiManager::GetDetailsPanelGuiComponent() const{
	return *m_pDetailsPanelGuiComponent;
}

void GuiManager::ImGuiInitalize(){

	// Imguiの初期処理
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(Window::GetInstance()->GetHwnd());
	ImGui_ImplDX11_Init(SimepleD3D::DX11GetDevice(), SimepleD3D::DX11GetDeviceContext());
}

void GuiManager::ImGuiUpdate(){

	// Imguiフレーム更新
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void GuiManager::ImGuiDraw(){

	// ImGuiの描画
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void GuiManager::ImGuiFinalize(){

	// Imgui解放処理
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

GuiManager::GuiManager(Application* app) :
	m_pOwnerApplication(app)
{
	ImGuiInitalize();

	// Docキャンバス
	new CanvasGuiComponent(this);

	//// Actor Component一覧
	new ActorHierarchyGuiComponent(this);

	//// 詳細パネル
	m_pDetailsPanelGuiComponent = new DetailsPanelGuiComponent(this);

	// シーンビュー
	new SceneViewGuiComponent(this, "GameView");

}

GuiManager::~GuiManager(){

	ImGuiFinalize();
}
