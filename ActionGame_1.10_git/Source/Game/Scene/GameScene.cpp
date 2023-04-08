#include "GameScene.h"
#include "../Component/ComponentList.h"
#include "../UniqeClass/UniqeClassList.h"

GameScene::GameScene(SceneManager* manager):
	Scene(manager)
{
	new FloorActor(this, "FloorActor");
	new PlayerActor(this, "playerActor");
}
