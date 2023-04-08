#include "ActorManager.h"

void ActorManager::Update(){

	// Actorの更新
	ActorUpdate();

	// 追加を延期したActorの入れなおし
	ReInsert();

	// Actorの削除
	DeadActorDelete();
}

void ActorManager::Draw(){

	for (auto&& actor : m_pActorList) {
		actor->Draw();
	}
}

void ActorManager::AddActor(Actor* actor){

	// ActorのUpdate中に追加されたら一時別の配列に保存する
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

	// Actorの更新中に別のActorが追加されてfor分が落ちないようにする
	m_IsUpdatetingActor = true;

	for (auto&& actor : m_pActorList) {
		actor->Update();
	}

	m_IsUpdatetingActor = false;
}

void ActorManager::ReInsert(){

	//追加を延期したActorをpActorに追加する
	for (auto&& pending : m_pPendingActorList) {

		//スマートポインタ配列に入れていく
		m_pActorList.emplace_back(std::move(pending));
	}

	//箱の中を空にする
	m_pPendingActorList.clear();
}

void ActorManager::DeadActorDelete(){

	//ActorのStateがDeadになったら削除していく
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
