#include "GuiComponent.h"
#include "../Manager/GuiManager/GuiManager.h"

class CanvasGuiComponent :
	public GuiComponent
{
private:
	void Update() override;

public:
	CanvasGuiComponent(class GuiManager* manager);
	~CanvasGuiComponent() override {};
};
