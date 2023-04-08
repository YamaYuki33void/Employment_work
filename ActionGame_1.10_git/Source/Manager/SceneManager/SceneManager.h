#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Scene/Scene.h"

class SceneManager{
public:
	// �V�[���̃��X�g
	enum class SceneList {
		Game,
	};

	void Update();
	void Draw();

	// �V�[���؂�ւ�
	void ChangeScene(const SceneList scene);

	// Getter
	class Scene* GetScene()const;

private:
	// ���݂̃V�[���|�C���^
	std::unique_ptr<class Scene> m_pScene;

public:
	SceneManager(class Application* app);
	~SceneManager() {};
};

