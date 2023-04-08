#include "ActorManager.h"

void ActorManager::Update(){

	// Actor�̍X�V
	ActorUpdate();

	// �ǉ�����������Actor�̓���Ȃ���
	ReInsert();

	// Actor�̍폜
	DeadActorDelete();
}

void ActorManager::Draw(){

	for (auto&& actor : m_pActorList) {
		actor->Draw();
	}
}

void ActorManager::AddActor(Actor* actor){

	// Actor��Update���ɒǉ����ꂽ��ꎞ�ʂ̔z��ɕۑ�����
	if (m_IsUpdatetingActor == true) {
		m_pPendingActorList.emplace_back(actor);
	}
	else {
		m_pActorList.emplace_back(std::move(actor));
	}
}

const std::vector<std::unique_ptr<class Actor>>& ActorManager::GetActorList() const{
	return m_pActorList;
}

void ActorManager::ActorUpdate(){

	// Actor�̍X�V���ɕʂ�Actor���ǉ������for���������Ȃ��悤�ɂ���
	m_IsUpdatetingActor = true;

	for (auto&& actor : m_pActorList) {
		actor->Update();
	}

	m_IsUpdatetingActor = false;
}

void ActorManager::ReInsert(){

	//�ǉ�����������Actor��pActor�ɒǉ�����
	for (auto&& pending : m_pPendingActorList) {

		//�X�}�[�g�|�C���^�z��ɓ���Ă���
		m_pActorList.emplace_back(std::move(pending));
	}

	//���̒�����ɂ���
	m_pPendingActorList.clear();
}

void ActorManager::DeadActorDelete(){

	//Actor��State��Dead�ɂȂ�����폜���Ă���
	for (auto iter = m_pActorList.begin(); iter != m_pActorList.end();) {

		if ((*iter)->GetState() == Actor::State::Dead) {

			iter = m_pActorList.erase(iter);
		}
		else {
			++iter;
		}
	}
}

ActorManager::ActorManager(Scene* scene) :
	m_pOwnerScene(scene),
	m_IsUpdatetingActor(false)
{
}
