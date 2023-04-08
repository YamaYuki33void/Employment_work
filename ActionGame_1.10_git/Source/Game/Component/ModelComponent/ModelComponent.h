#pragma once
#include "../Component.h"

class ModelComponent:
	public Component
{
public:
	ModelComponent(class Actor* actor, const std::string& ComponentName = "ModelComponent"):
		Component(actor, ComponentType::ObjectType, ComponentName)
	{
	}
	
	~ModelComponent() override{};
};

