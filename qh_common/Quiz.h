#pragma once

#include "Str.h"

const int ANSWER_COUNT = 4;

class Quiz
{
public:
	typedef std::vector<std::wstring> VECTOR_ANSWER;

public:
	Quiz(const std::wstring& Question, const std::wstring& Date, const VECTOR_ANSWER& vectorAnswer, const int& nCorrect);
	
	~Quiz();

	const std::wstring& GetDate()
	{
		return m_Date;
	}

	const std::wstring& GetQuestion()
	{
		return m_Question;
	}

	const std::wstring& GetAnswer(int nIdx)
	{
		return m_vectorAnswer[nIdx];
	}

	const int GetCorrect()
	{
		return m_Correct;
	}

private:
	std::wstring m_Date;

	std::wstring m_Question;

	VECTOR_ANSWER m_vectorAnswer;

	int m_Correct;
};
