#include "stdafx.h"

#include "MenuMode.h"

#include "BgmPlayer.h"

#include "SpeedQuiz.h"
#include "WindowUtil.h"

#include <boost/bind.hpp>

MenuMode::MenuMode(light::weak_raw_ptr<light::view::DirectX> directX)
: light::view::Mode(SCENE_NO::MENU, directX)
{
	m_Animation.Load(m_direct_x, _T("Menu\\back.ani"));
	m_Button_Start.Create(m_direct_x, _T("Menu\\Button_Start.spr"), boost::bind(&MenuMode::OnStartButtonClick, this), light::POSITION_INT(430, 520), _T("Sound\\GUI\\Click.wav"), _T("Sound\\GUI\\Over.wav"));
}

MenuMode::~MenuMode()
{
	
}

void MenuMode::Begin()
{
	light::view::BgmPlayer::Instance()->Play(1);
	m_Button_Start.Set();
	m_Button_Start.Message(_T("START"), 20, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void MenuMode::End()
{
}

void MenuMode::Render()
{
	m_Animation.DrawLoop();
	DrawString(_T("Quiz Holic"), light::POSITION_INT(200, 120), 128, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void MenuMode::RenderPostUI()
{
	
}

void MenuMode::Logic()
{
	

	if(KEY_DOWN(VK_ESCAPE))
	{
		ChangeMode(SCENE_NO::LOGO);
	}
}

bool MenuMode::OnStartButtonClick()
{
	new SpeedQuiz(m_direct_x);
	ChangeMode(SCENE_NO::SELECTCHARACTER);
	return true;
}