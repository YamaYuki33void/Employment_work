#pragma once
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Manager/GuiManager/GuiManager.h"

//-------------------------------
// Applicationの流れを表すクラス
//-------------------------------

class Application{
public:
	// Applicationの起動
	void Run();

	// Getter
	class SceneManager& GetSceneManager();


private:
	void Init();    // 初期化
	void Release(); // 解放
	void Roop();    // ループ

	void Input();	// 入力	  
	void Update();	// 更新
	void Draw();    // 描画

	// シーンマネージャー作成
	class SceneManager m_SceneManager;

	// Guiマネージャー作成
	std::unique_ptr<class GuiManager> m_pGuiManager;

public:
	Application();
};

