#pragma once
#include "../../Actor/CharactorActor.h"

class PlayerActor:
	public CharactorActor
{
public:
	class StaticMeshComponent* m_pSward;
	class GameplayAbilitySystemComponent* m_pGASComponent;
	bool m_IsSward = false;

private:
	void UniqeUpdate()override;

public:
	PlayerActor(class Scene* scene, const std::string& ActorName = "CharactorActor");
	~PlayerActor()override {};
};

