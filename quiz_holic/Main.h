#pragma once

#include "EnvironmentManager.h"
#include "Direct2D.h"

#include "CharacterManager.h"
#include "QuizManager.h"

#include "Mode.h"

class Main : public light::EnvironmentManager
{
public:
	Main(const std::wstring& strProgramName);
	virtual ~Main();

	virtual bool initialize();
	virtual void on_update();
	virtual void release();

private:
	light::view::Direct2D m_direct_x;

	std::unique_ptr<QuizManager> m_QuizManager;

	std::unique_ptr<CharacterManager> m_CharacterManager;

	light::view::Animation2D m_BeginAnimation;

	light::view::Animation2D m_EndAnimation;
};
