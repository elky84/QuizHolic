#pragma once

#include "QuizGame.h"

const int SPEED_QUIZ_TIME = 60000;

class SpeedQuiz : public QuizGame
{
public:
	SpeedQuiz(light::weak_raw_ptr<light::view::DirectX> directX);

private:
	virtual void Init();

	virtual bool StateProcess();

	virtual void CorrectProcess(bool bCorrect);

	virtual void Logic();

private:
	DWORD m_dwGameTick;
	DWORD m_dwStartGameTick;
};
