#pragma once

#include "Mode.h"
#include "Animation2D.h"

class QuizMode : public light::view::Mode
{
public:
	QuizMode(light::weak_raw_ptr<light::view::DirectX> directX);
	virtual ~QuizMode();

	virtual void Begin();

	virtual void End();

	virtual void Render();

	virtual void RenderPostUI();

	virtual void Logic();

private:
	light::view::Animation2D m_Animation;
};
