#pragma once
#include "../../Actor/Actor.h"

class FloorActor:
	public Actor
{
private:
	void UniqeUpdate()override {};

public:
	FloorActor(class Scene* scene, const std::string& ActorName = "CharactorActor");
	~FloorActor()override {};
};

