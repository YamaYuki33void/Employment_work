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

	// �Q�[�����[�v
	while (Window::GetInstance()->ExecMessage()) {

		if (FpsControl::GetInstance()->Update() == true) {
			continue;
		}
		else {
			Input();   //���͏���
			Update();  //�X�V����
			Draw();    //�`�揈��

			//Fps�̕\��
			Window::GetInstance()->SetMyWindowText(FpsControl::GetInstance()->GetFps().c_str());
		}

		FpsControl::GetInstance()->StartSubEnd();
	}
}

void Application::Init() {

	// �eAssets�̓ǂݍ���
	ShaderAssets::GetInstance()->LoadInitalize();
	ModelAssets::GetInstance()->LoadInitalize();
	AnimationAssets::GetInstance()->LoadInitalize();
	AnimationMontageAssets::GetInstance()->LoadInitalize();

	// ���[���h�ϊ��s��N���X�̏�����
	WorldTransformation::GetInstance()->Initalize();

	// �V�[���̑I��
	m_SceneManager.ChangeScene(SceneManager::SceneList::Game);

	m_pGuiManager = std::make_unique<GuiManager>(this);
}

void Application::Input(){

	// ���̓f�o�C�X�X�V
	DirectInput::GetInstance()->KeyBufferUpdate();
	GamePad::GetInstance()->KeyBufferUpdate();
}

void Application::Update(){

	// Gui�̍X�V
	m_pGuiManager->Update();

	// �V�[���̍X�V
	m_SceneManager.Update();
}

void Application::Draw(){      

	// ��ʃN���A
	float ClearColer[] = { 1.f,0.2f,0.f };
	SimepleD3D::DX11SetNormalRenderTarget();
	SimepleD3D::DX11ClearRender(ClearColer);

	// Gui�̕`��
	m_pGuiManager->Draw();

	// �V�[���̕`��
	m_SceneManager.Draw();

	// ��ʃt���b�v
	SimepleD3D::DX11FlipRender();
}

void Application::Release(){
}
