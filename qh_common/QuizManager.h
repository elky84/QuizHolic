#pragma once

#include "Singleton.h"
#include "Quiz.h"

#include <vector>
#include <map>

const int MAX_QUIZ_LEVEL = 5;

class QuizManager : public light::Singleton<QuizManager>
{
private:
	typedef std::vector<Quiz> VECTOR_QUIZ;

	typedef std::map< std::pair<std::wstring, std::wstring> ,VECTOR_QUIZ > MAP_QUIZ;

public:
	QuizManager();

	~QuizManager();

	bool Load();

	const Quiz* get(const std::wstring& strMainCategory, const std::wstring& strSubCategory, int nLevel);

	const Quiz* Random(int nLevel);

private:
	bool AddQuiz(const std::wstring& strMainCategory, const std::wstring& strSubCategory, int nLevel, const Quiz& quiz);

private:
	MAP_QUIZ m_mapQuiz[MAX_QUIZ_LEVEL];
};
