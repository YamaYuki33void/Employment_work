#pragma once
#include "TreeComponent.h"
#include "../../Game/Component/ComponentList.h"
#include "../GuiComponentList.h"

class AnimationListTreeComponent :
    public TreeComponent
{
private:
	void SetComponentInfo(class Component* comp)override;

	void TreeUpdate()override;
	void TreeDraw()override;

	void TimeLine();

private:
	class AnimationData* m_pAnimationData;
	float m_AnimNowFream;

private:
	std::unique_ptr<class SceneViewGuiComponent> m_pAnimViewGuiComponent;
	std::unique_ptr<class SkeletalMeshComponent> m_pAnimViewSkeletalMesh;
	std::unique_ptr<class CameraComponent> m_pAnimViewCamera;

public:
	AnimationListTreeComponent(class DetailsPanelGuiComponent* comp);
	~AnimationListTreeComponent() override{};
};

