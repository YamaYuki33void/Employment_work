#include "CharactorActor.h"
#include "../Component/ComponentList.h"

CharactorActor::CharactorActor(Scene* scene, const std::string& ActorName):
	Actor(scene,ActorName)
{
	m_pMesh = new SkeletalMeshComponent(this);
	m_pCameraArm = new CameraArmComponent(this);
	m_pCamera = new CameraComponent(this);
	m_pMove = new CharactorMoveComponent(m_pMesh,m_pCamera);

	m_pCameraArm->SetAttachRootComponent(m_pMesh->GetTransformComponent());
	m_pCamera->GetTransformComponent()->ResistParent(m_pCameraArm->GetTransformComponent());
}
