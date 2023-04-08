#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../../Game/Component/Component.h"

class ComponentManager{
public:
	void Update();
	void Draw();

	// コンポーネントの追加
	void AddComponent(class Component* component);

	// コンポーネントの取得
	template<typename T>
	T* GetComponent()const;

	template<typename T>
	std::vector<T> GetComponents()const;

	// Getter
	const std::vector<std::unique_ptr<class Component>>& GetComponentList()const;
	class Actor* GetActor()const;

private:
	// ComponentList
	std::vector<std::unique_ptr<class Component>> m_pComponentList;

	// OwnerActor
	class Actor* m_pOwnerActor;

public:
	ComponentManager(class Actor* actor);
	~ComponentManager() {};
};

template<typename T>
inline T* ComponentManager::GetComponent() const{
	
	for (auto&& comp : m_pComponentList) {
		if (dynamic_cast<T*>(comp.get())) {
			return static_cast<T*>(comp.get());
		}
	}

	MessageBoxA(nullptr, "Not GetComponent", nullptr, MB_OK);
	return nullptr;
}

template<typename T>
inline std::vector<T> ComponentManager::GetComponents() const{

	std::vector<T*> list;
	for (auto&& comp : m_pComponentList) {
		if (dynamic_cast<T*>(comp.get())) {
			static_cast<T*>(list.emplace_back(comp.get()));
		}
	}

	return list;
}
