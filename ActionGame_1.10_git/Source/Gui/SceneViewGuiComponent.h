#pragma once
#include "GuiComponent.h"
#include "../System/DirectX/DirectX_RenderTargetTexture.h"

class SceneViewGuiComponent :
    public GuiComponent
{
public:
	void Update()override;
	void Draw()override;

private:
	std::unique_ptr<class DirectX_RenderTargetTexture> m_pRenderTargetTexture;

	std::string m_WindowName;

public:
	SceneViewGuiComponent(class GuiManager* manager,const std::string& windowname);
	~SceneViewGuiComponent()override {};
};

