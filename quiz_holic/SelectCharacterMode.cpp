#include "stdafx.h"

#include "SelectCharacterMode.h"
#include "BgmPlayer.h"

#include "QuizGame.h"
#include "WindowUtil.h"
#include "DirectoryUtil.h"

#include "CharacterManager.h"

#include <boost/bind.hpp>

SelectCharacterMode::SelectCharacterMode(light::weak_raw_ptr<light::view::DirectX> directX)
: light::view::Mode(SCENE_NO::SELECTCHARACTER, directX)
{
	m_Animation.Load(m_direct_x, _T("SelectCharacterMode\\back.ani"));
}

SelectCharacterMode::~SelectCharacterMode()
{
}

void SelectCharacterMode::Begin()
{
	QuizGame::Instance()->Init();

	CharacterManager::MAP_CHARACTER_INFORMATION& mapInformation = CharacterManager::Instance()->MapCharacterInformation();

	light::POSITION_INT GuiPosition(200, 250);

	m_Button.resize(mapInformation.size());
	int i = 0;
	for each(CharacterManager::MAP_CHARACTER_INFORMATION::value_type pair in mapInformation)
	{
		CHARACTER_INFORMATION& info = pair.second;

		using namespace std::tr1::placeholders;

		m_Button[i].Create(m_direct_x, _T("Character\\MiniTemplate.spr"), light::get_file_name_without_path(info.MiniTexture()), boost::bind(&SelectCharacterMode::OnClickButton, this, &m_Button[i]),
			GuiPosition, _T("Sound\\GUI\\Click.wav"), _T("Sound\\GUI\\Over.wav"));

		GuiPosition += light::POSITION_INT(120, 0);
		++i;
	}

	for(size_t n = 0; n < m_Button.size(); ++n)
		m_Button[n].Set();
}

void SelectCharacterMode::End()
{
}

void SelectCharacterMode::Render()
{
	m_Animation.DrawLoop();
	DrawString(_T("Select Character"), light::POSITION_INT(250, 120), 72, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void SelectCharacterMode::RenderPostUI()
{
	
}

void SelectCharacterMode::Logic()
{
	

	if(KEY_DOWN(VK_ESCAPE))
	{
		SAFE_DELETE_SINGLETON(QuizGame);
		ChangeMode(SCENE_NO::MENU);
	}
}

bool SelectCharacterMode::OnClickButton(const light::view::GuiButton* pGuiButton)
{
	for(size_t i = 0; i < m_Button.size(); ++i)
	{
		if(&m_Button[i] == pGuiButton)
		{
			QuizGame::Instance()->SelectCharacter(i + 1);
			ChangeMode(SCENE_NO::QUIZ);
			return true;
		}
	}
	return true;
}
