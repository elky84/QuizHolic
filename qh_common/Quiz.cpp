#include "stdafx.h"

#include "Quiz.h"

Quiz::Quiz(const std::wstring& Question, const std::wstring& Date, const VECTOR_ANSWER& vectorAnswer, const int& nCorrect)
: m_Question(Question)
, m_Date(Date)
, m_vectorAnswer(vectorAnswer)
, m_Correct(nCorrect)
{
}

Quiz::~Quiz()
{

}
