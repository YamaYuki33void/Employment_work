#pragma once
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Manager/GuiManager/GuiManager.h"

//-------------------------------
// Application�̗����\���N���X
//-------------------------------

class Application{
public:
	// Application�̋N��
	void Run();

	// Getter
	class SceneManager& GetSceneManager();


private:
	void Init();    // ������
	void Release(); // ���
	void Roop();    // ���[�v

	void Input();	// ����	  
	void Update();	// �X�V
	void Draw();    // �`��

	// �V�[���}�l�[�W���[�쐬
	class SceneManager m_SceneManager;

	// Gui�}�l�[�W���[�쐬
	std::unique_ptr<class GuiManager> m_pGuiManager;

public:
	Application();
};

