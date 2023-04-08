#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "TransformComponent/TransformComponent.h"

class Component{
public:
	// �R���|�[�l���g�^�C�v
	enum class ComponentType {
		ObjectType,
		FuncType
	};

	void Update();
	void Draw();

	// Setter
	void SetIsVisible(const bool visible);

	// Getter
	class Actor* GetActor()const;
	const std::string& GetComponentName()const;
	const ComponentType GetComponentType()const;
	class TransformComponent* GetTransformComponent()const;

private:
	virtual void UniqeUpdate() {};
	virtual void UniqeDraw() {};

private:
	// �g�����X�t�H�[��
	std::unique_ptr<class TransformComponent> m_pTransformComponent;

	// ComponentName
	std::string m_ComponentName;

	// ComponentType
	ComponentType m_Type;

	// �`��t���O
	bool m_IsVisible;

	// Owenr
	class Actor* m_pActor;

public:
	Component(class Actor* actor, const ComponentType type, const std::string& ComponentName = "Component");
	virtual~Component() {};
};

