#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

class Actor{
public:
	// 状態
	enum class State {
		Activ, Dead,
	};

	// 共通更新
	void Update();
	void Draw();

	// Getter
	const State GetState()const;
	const std::string& GetActorName()const;
	class Scene* GetScene()const;
	class ComponentManager* GetComponentManager()const;

private:
	// 継承先のActorの固有更新
	virtual void UniqeUpdate() = 0;

private:
	// オブジェクトの状態変数
	State m_State;

	// Actorの名前
	std::string m_ActorName;

	// コンポーネントマネージャー
	std::unique_ptr<class ComponentManager> m_pComponentManager;

	// SceneOwnerポインタ
	class Scene* m_pOwnerScene;

public:
	Actor(class Scene* scene, const std::string& ActorName = "Actor");
	virtual ~Actor() {};
};

