#include "stdafx.h"
#include "Main.h"
#include "Resource.h"

#include "LogoMode.h"
#include "MenuMode.h"
#include "SelectCharacterMode.h"
#include "QuizMode.h"

#include "ModeManager.h"
#include "BgmPlayer.h"

#include "QuizGame.h"

Main::Main(const std::wstring& strProgramName) 
: light::EnvironmentManager(strProgramName)
{
}

Main::~Main()
{
}

bool Main::initialize()
{
	if( FALSE == m_direct_x.Init(get_program_name(), light::view::DEFAULT_FPS, TRUE))
	{
		LOG_ERROR(_T("DirectX::Init() Failed"));
		return false;
	}

	if( FALSE == m_direct_x.LoadFont(_T("Arita-Medium.ttf")))
	{
		LOG_ERROR(_T("DirectX::LoadFont() Failed"));
		return false;
	}

	m_CharacterManager.reset(new CharacterManager);
	m_QuizManager.reset(new QuizManager);

	m_CharacterManager->Load();

	m_QuizManager->Load();

	light::view::BgmPlayer::Instance()->Load(_T("Sound\\BGM\\BGM.xml"));

	m_BeginAnimation.Load(&m_direct_x, _T("Common\\FadeIn.ani"));
	m_EndAnimation.Load(&m_direct_x, _T("Common\\FadeOut.ani"));

	light::view::Mode::SetBeginAnimation(&m_BeginAnimation);
	light::view::Mode::SetEndAnimation(&m_EndAnimation);

	m_direct_x.RegisterMode(new LogoMode(&m_direct_x));
	m_direct_x.RegisterMode(new MenuMode(&m_direct_x));
	m_direct_x.RegisterMode(new SelectCharacterMode(&m_direct_x));
	m_direct_x.RegisterMode(new QuizMode(&m_direct_x));
	m_direct_x.ActiveMode(SCENE_NO::LOGO);

	on_complete();
	return true;
}

void Main::on_update()
{
	m_direct_x.on_update();
}

void Main::release()
{
	m_CharacterManager.reset();
	m_QuizManager.reset();
	SAFE_DELETE_SINGLETON(QuizGame);
}
