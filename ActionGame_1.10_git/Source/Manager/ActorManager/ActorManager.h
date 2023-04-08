#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Actor/Actor.h"

//------------------------------------------------
// シーンごとに持っているActorの管理
// 追加・削除など
//------------------------------------------------

class ActorManager{
public:
	void Update();
	void Draw();

	// Actorの追加
	void AddActor(class Actor* actor);

	// Getter
	const std::vector<std::unique_ptr<class Actor>>& GetActorList()const;

private:
	// Actorの更新
	void ActorUpdate();

	// 追加を延期したActorをリストに入れなおす
	void ReInsert();

	// Actorの状態がDeadになった時リストから削除する
	void DeadActorDelete();

private:
	// Actorのリスト
	std::vector<std::unique_ptr<class Actor>> m_pActorList;

	// Actorの一時保管リスト
	std::vector<class Actor*>m_pPendingActorList;

	// 更新中フラグ
	bool m_IsUpdatetingActor;

	// SceneOwnerポインタ
	class Scene* m_pOwnerScene;

public:
	ActorManager(class Scene* scene);
	~ActorManager() {};
};

