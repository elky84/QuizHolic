#include "stdafx.h"

#include "LogoMode.h"
#include "BgmPlayer.h"

#include "Input.h"

LogoMode::LogoMode(light::weak_raw_ptr<light::view::DirectX> directX)
	: light::view::Mode(SCENE_NO::LOGO, directX)
{
	m_Click.Load(_T("Sound\\GUI\\Click.wav"));

	m_Animation.Load(m_direct_x, _T("Logo\\Logo.ani"));
}

LogoMode::~LogoMode()
{

}

void LogoMode::Begin()
{
	m_Animation.reset();
}

void LogoMode::End()
{
	m_Animation.reset();
}

void LogoMode::Render()
{
	m_Animation.Update();
	m_Animation.Draw();

	if(false == m_Animation.NowPlaying())
	{
		ChangeMode(SCENE_NO::MENU);
	}
}

void LogoMode::RenderPostUI()
{
	
}

void LogoMode::Logic()
{
	if ( light::Input::Mouse::LButtonClick())
	{
		m_Click.Play();
		ChangeMode(SCENE_NO::MENU);
	}
}
