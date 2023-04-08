#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Actor/Actor.h"

//------------------------------------------------
// �V�[�����ƂɎ����Ă���Actor�̊Ǘ�
// �ǉ��E�폜�Ȃ�
//------------------------------------------------

class ActorManager{
public:
	void Update();
	void Draw();

	// Actor�̒ǉ�
	void AddActor(class Actor* actor);

	// Getter
	const std::vector<std::unique_ptr<class Actor>>& GetActorList()const;

private:
	// Actor�̍X�V
	void ActorUpdate();

	// �ǉ�����������Actor�����X�g�ɓ���Ȃ���
	void ReInsert();

	// Actor�̏�Ԃ�Dead�ɂȂ��������X�g����폜����
	void DeadActorDelete();

private:
	// Actor�̃��X�g
	std::vector<std::unique_ptr<class Actor>> m_pActorList;

	// Actor�̈ꎞ�ۊǃ��X�g
	std::vector<class Actor*>m_pPendingActorList;

	// �X�V���t���O
	bool m_IsUpdatetingActor;

	// SceneOwner�|�C���^
	class Scene* m_pOwnerScene;

public:
	ActorManager(class Scene* scene);
	~ActorManager() {};
};

