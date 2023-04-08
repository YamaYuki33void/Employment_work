#include "FloorActor.h"
#include "../../Component/ComponentList.h"

FloorActor::FloorActor(Scene* scene, const std::string& ActorName) :
	Actor(scene, ActorName)
{
	auto* temp = new StaticMeshComponent(this);
	temp->SetModelData("Floor");
	temp->GetTransformComponent()->AddWorldRotation(DirectX::SimpleMath::Vector3(-90, 0, 0));
}
