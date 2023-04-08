#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Scene/Scene.h"

class SceneManager{
public:
	// シーンのリスト
	enum class SceneList {
		Game,
	};

	void Update();
	void Draw();

	// シーン切り替え
	void ChangeScene(const SceneList scene);

	// Getter
	class Scene* GetScene()const;

private:
	// 現在のシーンポインタ
	std::unique_ptr<class Scene> m_pScene;

public:
	SceneManager(class Application* app);
	~SceneManager() {};
};

