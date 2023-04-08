#include "Application.h"
#include "../Window/Window.h"
#include "../FpsControl/FpsControl.h"
#include "../Camera/Camera.h"

#include "../DirectX/DirectX_Simple.h"

#include "../../Assets/ShaderAssets/ShaderAssets.h"
#include "../../Assets/ModelAssets/ModelAssets.h"
#include "../../Assets/AnimationAssets/AnimationAssets.h"
#include "../../Assets/AnimationMontageAssets/AnimationMontageAssets.h"

Application::Application():
	m_SceneManager(this)
{
}

void Application::Run(){
	Init();
	Roop();
	Release();
}

SceneManager& Application::GetSceneManager(){
	return m_SceneManager;
}

void Application::Roop(){

	// ゲームループ
	while (Window::GetInstance()->ExecMessage()) {

		if (FpsControl::GetInstance()->Update() == true) {
			continue;
		}
		else {
			Input();   //入力処理
			Update();  //更新処理
			Draw();    //描画処理

			//Fpsの表示
			Window::GetInstance()->SetMyWindowText(FpsControl::GetInstance()->GetFps().c_str());
		}

		FpsControl::GetInstance()->StartSubEnd();
	}
}

void Application::Init() {

	// 各Assetsの読み込み
	ShaderAssets::GetInstance()->LoadInitalize();
	ModelAssets::GetInstance()->LoadInitalize();
	AnimationAssets::GetInstance()->LoadInitalize();
	AnimationMontageAssets::GetInstance()->LoadInitalize();

	// ワールド変換行列クラスの初期化
	WorldTransformation::GetInstance()->Initalize();

	// シーンの選択
	m_SceneManager.ChangeScene(SceneManager::SceneList::Game);

	m_pGuiManager = std::make_unique<GuiManager>(this);
}

void Application::Input(){

	// 入力デバイス更新
	DirectInput::GetInstance()->KeyBufferUpdate();
	GamePad::GetInstance()->KeyBufferUpdate();
}

void Application::Update(){

	// Guiの更新
	m_pGuiManager->Update();

	// シーンの更新
	m_SceneManager.Update();
}

void Application::Draw(){      

	// 画面クリア
	float ClearColer[] = { 1.f,0.2f,0.f };
	SimepleD3D::DX11SetNormalRenderTarget();
	SimepleD3D::DX11ClearRender(ClearColer);

	// Guiの描画
	m_pGuiManager->Draw();

	// シーンの描画
	m_SceneManager.Draw();

	// 画面フリップ
	SimepleD3D::DX11FlipRender();
}

void Application::Release(){
}
