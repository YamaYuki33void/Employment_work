#include "SceneManager.h"
#include "../../Game/Scene/GameScene.h"

void SceneManager::Update(){

	m_pScene->Update();
}

void SceneManager::Draw(){

	m_pScene->Draw();
}

void SceneManager::ChangeScene(const SceneList scene){

	// シーンデータが入っていれば削除する
	if (m_pScene.get() != nullptr) {
		m_pScene.reset();
	}

	// 選択したシーンを作成する
	switch (scene) {
	case SceneManager::SceneList::Game:
		m_pScene = std::make_unique<GameScene>(this);

		break;
	}
}

Scene* SceneManager::GetScene() const{
	return m_pScene.get();
}

SceneManager::SceneManager(Application* app){
}
