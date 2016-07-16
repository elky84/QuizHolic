#include "stdafx.h"
#include "SpeedQuiz.h"
#include "CharacterInterface.h"
#include "QuizManager.h"
#include "Tick.h"
#include <algorithm>

#include <boost/bind.hpp>

SpeedQuiz::SpeedQuiz(light::weak_raw_ptr<light::view::DirectX> directX)
: QuizGame(directX)
, m_dwGameTick(SPEED_QUIZ_TIME)
, m_dwStartGameTick(0)

{

}

void SpeedQuiz::Init()
{
	__super::Init();
}

void SpeedQuiz::CorrectProcess(bool bCorrect)
{
	if(bCorrect)
		m_Character->AddPoint(100);
	else
		m_Character->AddPoint(-50);
}

bool SpeedQuiz::StateProcess()
{
	switch(GetGameState())
	{
	case GAMESTATE_WAIT:
		{
			using namespace std::tr1::placeholders;
			m_Mc->Ask(_T("스피드 퀴즈입니다~"), boost::bind(&QuizGame::NextState, this));
		}
		break;
	case GAMESTATE_BRIEFING:
		{
			using namespace std::tr1::placeholders;
			m_Mc->Ask(_T("최대한 시간내에 많이 맞추세요!"), boost::bind(&QuizGame::NextState, this));
			m_dwStartGameTick = GetTickCount();

			m_Character->ShowPoint();
		}
		break;
	case GAMESTATE_QUESTION:
		{
			m_Quiz = QuizManager::Instance()->Random(m_Level);
			if(m_Quiz.get() == NULL)
			{
				return false;
			}

			m_Question.Message(m_Quiz->GetQuestion(), 30, D3DCOLOR_RGBA(255, 255, 255, 255));

			std::vector<int> vector_Answer;
			for(int n = 0; n < ANSWER_COUNT; ++n)
				vector_Answer.push_back(n);

			for(int n = 0; n < ANSWER_COUNT; ++n)
			{
				std::wstringstream strAnswer;
				int nAnswer = vector_Answer[rand() % vector_Answer.size()];
				strAnswer << n + 1 << ". " << m_Quiz->GetAnswer(nAnswer);
				std::wstring strAnswerDbg = strAnswer.str();
				if(m_Quiz->GetCorrect() -1 == nAnswer)
				{
					m_CorrectButtonIdx = n;
				}

				m_Answer[n].Message(strAnswerDbg, 30, D3DCOLOR_RGBA(255, 255, 255, 255));
				vector_Answer.erase(find(vector_Answer.begin(), vector_Answer.end(), nAnswer));
			}
		}
		break;
	case GAMESTATE_ANSWER:
		{
			m_Question.Release();

			for(int i = 0; i < ANSWER_COUNT; ++i)
				m_Answer[i].Release();

			//to do work. 이거 어쩌지?
			m_GameState = GAMESTATE_BRIEFING;

			using namespace std::tr1::placeholders;
			m_Mc->Ask(_T("다음 문제 나갑니다~"), boost::bind(&QuizGame::NextState, this));
		}
		break;
	case GAMESTATE_END:
		{
			//점수 보여줘?
		}
		break;
	}
	return true;
}

void SpeedQuiz::Logic()
{
	if( GAMESTATE_BRIEFING <= m_GameState)
	{
		DWORD dwElapsedTick = GetTickCount() - m_dwStartGameTick;
		if( m_dwGameTick <  dwElapsedTick)
		{
			m_Question.Release();

			for(int i = 0; i < ANSWER_COUNT; ++i)
				m_Answer[i].Release();

			using namespace std::tr1::placeholders;
			m_Mc->Ask(_T("게임 끝났습니다~ 수고하셨어요~~"), boost::bind(&QuizGame::NextState, this));
			m_Character->ShowPoint();
			return;
		}
		else
		{
			DWORD dwDelta = light::delta<DWORD>(dwElapsedTick, m_dwGameTick);
			DWORD dwRemainedSecond = dwDelta / 1000;

			std::wstringstream strStream;
			strStream << dwRemainedSecond << _T("초 남았습니다");
			m_Character->Ask(strStream.str(), NULL);

			const float fElapsedPercentage = (float)dwElapsedTick / (float)m_dwGameTick; /// 최고가 1.
			m_Level = (int)(floor(fElapsedPercentage * MAX_QUIZ_LEVEL) + 1);
			LOG_INFO(_T("%s [%d]"), __FUNCTIONW__, m_Level);
		}
	}
}
