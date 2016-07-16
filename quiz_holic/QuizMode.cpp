#include "stdafx.h"
#include "QuizMode.h"

#include "BgmPlayer.h"
#include "QuizGame.h"
#include "WindowUtil.h"

QuizMode::QuizMode(light::weak_raw_ptr<light::view::DirectX> directX)
: light::view::Mode(SCENE_NO::QUIZ, directX)
{
	m_Animation.Load(m_direct_x, _T("QuizMode\\Back.ani"));
}

QuizMode::~QuizMode()
{
	
}

void QuizMode::Begin()
{
	m_Animation.reset();
	QuizGame::Instance()->Begin();
}

void QuizMode::End()
{
	QuizGame::Instance()->End();
}

void QuizMode::Render()
{
	m_Animation.DrawLoop();
	QuizGame::Instance()->Render();
}

void QuizMode::RenderPostUI()
{
	
}

void QuizMode::Logic()
{
	if(KEY_DOWN(VK_ESCAPE))
	{
		ChangeMode(SCENE_NO::SELECTCHARACTER);
	}
	else
	{
		QuizGame::Instance()->Logic();
	}
}