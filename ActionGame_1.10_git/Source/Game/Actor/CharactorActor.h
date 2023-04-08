#pragma once
#include "Actor.h"

class CharactorActor :
    public Actor
{
public:
	class SkeletalMeshComponent* m_pMesh;
	class CharactorMoveComponent* m_pMove;
	class CameraComponent* m_pCamera;
	class CameraArmComponent* m_pCameraArm;

public:
	CharactorActor(class Scene* scene, const std::string& ActorName = "CharactorActor");
	 ~CharactorActor()override {};
};

