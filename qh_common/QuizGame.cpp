#include "stdafx.h"
#include "QuizGame.h"
#include "CharacterManager.h"

#include <time.h>
#include <boost/bind.hpp>

QuizGame::QuizGame(light::weak_raw_ptr<light::view::DirectX> directX)
: m_direct_x(directX)
, m_GameState(GAMESTATE_NONE)
, m_CorrectButtonIdx(-1)
, m_Level(0)
{
	m_Question.Create(m_direct_x, _T("Quiz\\Sprite\\Question.spr"), NULL, light::POSITION_INT(520, 220));

	{
		using namespace std::tr1::placeholders;
		m_Answer[0].Create(m_direct_x, _T("Quiz\\Sprite\\Answer.spr"), boost::bind(&QuizGame::Answer, this, &m_Answer[0]), light::POSITION_INT(520, 360));
		m_Answer[1].Create(m_direct_x, _T("Quiz\\Sprite\\Answer.spr"), boost::bind(&QuizGame::Answer, this, &m_Answer[1]), light::POSITION_INT(520, 440));
		m_Answer[2].Create(m_direct_x, _T("Quiz\\Sprite\\Answer.spr"), boost::bind(&QuizGame::Answer, this, &m_Answer[2]), light::POSITION_INT(520, 520));
		m_Answer[3].Create(m_direct_x, _T("Quiz\\Sprite\\Answer.spr"), boost::bind(&QuizGame::Answer, this, &m_Answer[3]), light::POSITION_INT(520, 600));
	}
}

QuizGame::~QuizGame()
{

}

void QuizGame::Init()
{
	CharacterManager::Instance()->Release();
}

void QuizGame::Render()
{
	CharacterManager::Instance()->Draw();
}

void QuizGame::Begin()
{
	CharacterManager::Instance()->Set();

	m_GameState = GAMESTATE_WAIT;
	StateProcess();
}

void QuizGame::End()
{
	CharacterManager::Instance()->Release();
}

void QuizGame::SelectCharacter(int nIdx)
{
	m_Character = CharacterManager::Instance()->CreateCharacter(m_direct_x, nIdx, light::POSITION_INT(700, 80));
	SelectRandomMc();
}

void QuizGame::SelectRandomMc()
{
	m_Mc = CharacterManager::Instance()->CreateMc(m_direct_x, CharacterManager::Instance()->GetRandomCharacterIdx(), light::POSITION_INT(50, 20));
}

bool QuizGame::NextState()
{
	m_GameState = (GAME_STATE)(m_GameState + 1);;
	return StateProcess();
}

bool QuizGame::Answer(const light::view::Gui* pGuiButton)
{
	for(int i = 0; i < ANSWER_COUNT; ++i)
		m_Answer[i].Hide();

	if(&m_Answer[m_CorrectButtonIdx] == pGuiButton)
	{
		using namespace std::tr1::placeholders;
		m_Mc->Ask(_T("정답 입니다~"), boost::bind(&QuizGame::NextState, this));
		CorrectProcess(true);
	}
	else
	{
		using namespace std::tr1::placeholders;
		m_Mc->Ask(_T("틀렸습니다~"), boost::bind(&QuizGame::NextState, this));
		CorrectProcess(false);
	}
	return true;
}
