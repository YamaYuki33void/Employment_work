#pragma once
#include "Scene.h"

class GameScene :
    public Scene
{
public:
	GameScene(class SceneManager* manager);
	~GameScene()override {};
};

