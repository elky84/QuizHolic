#pragma once

#include "Mode.h"
#include "FmodEx.h"
#include "Animation2D.h"

class LogoMode : public light::view::Mode
{
public:
	LogoMode(light::weak_raw_ptr<light::view::DirectX> directX);
	virtual ~LogoMode();

	virtual void Begin();

	virtual void End();

	virtual void Render();

	virtual void RenderPostUI();

	virtual void Logic();

private:
	light::view::FmodEx m_Click;

	light::view::Animation2D m_Animation;
};
