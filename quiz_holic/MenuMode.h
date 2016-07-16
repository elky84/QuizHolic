#pragma once

#include "Mode.h"
#include "Animation2D.h"
#include "GuiButton.h"

class MenuMode : public light::view::Mode
{
public:
	MenuMode(light::weak_raw_ptr<light::view::DirectX> directX);
	virtual ~MenuMode();

	virtual void Begin();

	virtual void End();

	virtual void Render();

	virtual void RenderPostUI();

	virtual void Logic();

public:
	bool OnStartButtonClick();

private:
	light::view::GuiButton	m_Button_Start;

	light::view::Animation2D m_Animation;
};
