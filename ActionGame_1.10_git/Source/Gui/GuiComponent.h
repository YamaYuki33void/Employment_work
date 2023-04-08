#pragma once
#include "../System/DirectX/DirectX_Simple.h"
#include "../Manager/GuiManager/GuiManager.h"

class GuiComponent{
public:
	virtual void Update() = 0;
	virtual void Draw() {};

	// Getter
	class GuiManager& GetGuiManager()const;

private:
	class GuiManager* m_pOwnerGuiManager;

public:
	GuiComponent(class GuiManager* manager);
	virtual~GuiComponent() {};
};

