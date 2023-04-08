#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

class Actor{
public:
	// ���
	enum class State {
		Activ, Dead,
	};

	// ���ʍX�V
	void Update();
	void Draw();

	// Getter
	const State GetState()const;
	const std::string& GetActorName()const;
	class Scene* GetScene()const;
	class ComponentManager* GetComponentManager()const;

private:
	// �p�����Actor�̌ŗL�X�V
	virtual void UniqeUpdate() = 0;

private:
	// �I�u�W�F�N�g�̏�ԕϐ�
	State m_State;

	// Actor�̖��O
	std::string m_ActorName;

	// �R���|�[�l���g�}�l�[�W���[
	std::unique_ptr<class ComponentManager> m_pComponentManager;

	// SceneOwner�|�C���^
	class Scene* m_pOwnerScene;

public:
	Actor(class Scene* scene, const std::string& ActorName = "Actor");
	virtual ~Actor() {};
};

