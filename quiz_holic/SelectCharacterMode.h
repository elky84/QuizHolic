#pragma once

#include "Mode.h"

#include "GuiButton.h"
#include "Animation2D.h"

class SelectCharacterMode : public light::view::Mode
{
public:
	SelectCharacterMode(light::weak_raw_ptr<light::view::DirectX> directX);
	virtual ~SelectCharacterMode();

	virtual void Begin();

	virtual void End();

	virtual void Render();

	virtual void RenderPostUI();

	virtual void Logic();

private:
	bool OnClickButton(const light::view::GuiButton* pGuiButton);

private:
	light::view::Animation2D m_Animation;

	std::vector<light::view::GuiButton> m_Button;
};
