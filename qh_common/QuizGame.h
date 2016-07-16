#pragma once

#include "Singleton.h"
#include "weak_raw_ptr.hpp"
#include "Quiz.h"
#include "GuiButton.h"

namespace light
{
	
namespace view
{

    class DirectX;

} // namespace view

} // namespace light

class CharacterInterface;

enum GAME_STATE
{
	GAMESTATE_NONE = -1, 
	GAMESTATE_WAIT = 0, //대기상태 암것도 안함.
	GAMESTATE_BRIEFING = 1,  //브리핑.
	GAMESTATE_QUESTION = 2,  //퀴즈 문제 나가는 상태
	GAMESTATE_ANSWER = 3, //채점하고 다음 상태
	GAMESTATE_END = 4,
};

class QuizGame : public light::Singleton<QuizGame>
{
public:
	QuizGame(light::weak_raw_ptr<light::view::DirectX> directX);
	virtual ~QuizGame();

	virtual void Init();

	void Render();

	virtual void Logic() = 0;

	void Begin();
	void End();

	void SelectCharacter(int nIdx);	

	void SelectRandomMc();
	
	bool NextState();

	bool Answer(const light::view::Gui* pGuiButton);

protected:
	GAME_STATE GetGameState()
	{
		return m_GameState;
	}

private:
	virtual bool StateProcess() = 0;

	virtual void CorrectProcess(bool bCorrect) = 0;

protected:
	light::view::GuiButton m_Question;

	light::view::GuiButton m_Answer[ANSWER_COUNT];

	light::weak_raw_ptr<Quiz> m_Quiz;

	GAME_STATE m_GameState;

	light::weak_raw_ptr<CharacterInterface> m_Character;

	light::weak_raw_ptr<CharacterInterface> m_Mc;

	light::weak_raw_ptr<light::view::DirectX> m_direct_x;

	int m_CorrectButtonIdx;

	int m_Level;
};
