#include "stdafx.h"
#include "QuizManager.h"

#include "XMLParser.h"

#include "DirectoryUtil.h"
#include "Quiz.h"

QuizManager::QuizManager()
{

}

QuizManager::~QuizManager()
{

}

bool QuizManager::Load()
{
	std::wstring strName = _T("Quiz\\Quiz.xml");

	light::XMLParser parser;
	if( false == parser.read_file(strName))
		return false;

	if( false == parser.execute(_T("/QuizList")))
		return false;

	if( false == parser.bind_elem(_T("Category")))
		return false;

	std::wstring strMainCategory, strSubCategory;
	if( false == parser.bind_attrib(_T("MainCategory"), strMainCategory))
		return false;

	if( false == parser.bind_attrib(_T("SubCategory"), strSubCategory))
		return false;

	int nLevel = 0;
	if( false == parser.bind_attrib(_T("Level"), nLevel))
		return false;

	while(parser.next())
	{
		if( false == parser.bind_elem(_T("Quiz")))
			return false;

		std::wstring strQuestion, strDate, strImageFile, strSoundFile;
		if( false == parser.bind_attrib(_T("Question"), strQuestion))
			return false;

		if( false == parser.bind_attrib(_T("Date"), strDate))
			return false;

		if( false == parser.bind_attrib(_T("ImageFile"), strImageFile))
			return false;

		if( false == parser.bind_attrib(_T("SoundFile"), strSoundFile))
			return false;

		int nCorrect = 0;
		if( false == parser.bind_attrib(_T("Correct"), nCorrect))
			return false;

		std::wstring strAnswer1, strAnswer2, strAnswer3, strAnswer4;
		if( false == parser.bind_attrib(_T("Answer1"), strAnswer1))
			return false;

		if( false == parser.bind_attrib(_T("Answer2"), strAnswer2))
			return false;

		if( false == parser.bind_attrib(_T("Answer3"), strAnswer3))
			return false;

		if( false == parser.bind_attrib(_T("Answer4"), strAnswer4))
			return false;

		while(parser.next())
		{
			Quiz::VECTOR_ANSWER vectorAnswer;
			vectorAnswer.push_back(strAnswer1);
			vectorAnswer.push_back(strAnswer2);
			vectorAnswer.push_back(strAnswer3);
			vectorAnswer.push_back(strAnswer4);

			AddQuiz(strMainCategory, strSubCategory, nLevel, Quiz(strQuestion, strDate, vectorAnswer, nCorrect));
		}
	}
	return true;
}

bool QuizManager::AddQuiz(const std::wstring& strMainCategory, const std::wstring& strSubCategory, int nLevel, const Quiz& quiz)
{
	--nLevel; //Level은 1부터고, 배열인덱스는 0부터 이므로 보정.
	if(nLevel < 0 || MAX_QUIZ_LEVEL < nLevel)
	{
		LOG_ERROR(_T("%s. %d Level is not  permission. "), __FUNCTIONW__, nLevel);
		return false;
	}

	std::pair<std::wstring, std::wstring> key(strMainCategory, strSubCategory);
	MAP_QUIZ::iterator it = m_mapQuiz[nLevel].find(key);
	if(it == m_mapQuiz[nLevel].end())
	{
		VECTOR_QUIZ vector_Quiz;
		vector_Quiz.push_back(quiz);
		m_mapQuiz[nLevel].insert(MAP_QUIZ::value_type(key, vector_Quiz));
	}
	else
	{
		VECTOR_QUIZ& _vector_Quiz = it->second;
		_vector_Quiz.push_back(quiz);
	}

	return true;
}

const Quiz* QuizManager::get(const std::wstring& strMainCategory, const std::wstring& strSubCategory, int nLevel)
{
	--nLevel; //Level은 1부터고, 배열인덱스는 0부터 이므로 보정.
	if(nLevel < 0 || MAX_QUIZ_LEVEL < nLevel)
	{
		LOG_INFO(_T("%s. %d Level is not  permission. "), __FUNCTIONW__, nLevel);
		return NULL;
	}

	std::pair<std::wstring, std::wstring> key(strMainCategory, strSubCategory);
	MAP_QUIZ::iterator it = m_mapQuiz[nLevel].find(key);
	if(it == m_mapQuiz[nLevel].end())
	{
		LOG_INFO(_T("%s. %d Notfound Leveldata. [%s, %s]"), __FUNCTIONW__, nLevel, strMainCategory.c_str(), strSubCategory.c_str());
		return NULL;
	}

	VECTOR_QUIZ& _vector_Quiz = it->second;
	return &_vector_Quiz[rand() % _vector_Quiz.size()];
}

const Quiz* QuizManager::Random(int nLevel)
{
	--nLevel; //Level은 1부터고, 배열인덱스는 0부터 이므로 보정.
	if(nLevel < 0 || MAX_QUIZ_LEVEL <= nLevel)
	{
		LOG_INFO(_T("%s. %d level is not  permission."), __FUNCTIONW__, nLevel);
		return NULL;
	}

	if(m_mapQuiz[nLevel].empty())
	{
		LOG_INFO(_T("%s. %d leveldata is empty."), __FUNCTIONW__, nLevel);
		return NULL;
	}

	MAP_QUIZ::iterator it = m_mapQuiz[nLevel].begin();
	int nRand = rand() % m_mapQuiz[nLevel].size();
	for(int n = 0; n < nRand; n++)
	{
		++it;
	}

	if(it == m_mapQuiz[nLevel].end())
	{
		LOG_INFO(_T("%s. %d find error."), __FUNCTIONW__, nLevel);
		return NULL;
	}

	VECTOR_QUIZ& _vector_Quiz = it->second;
	return &_vector_Quiz[rand() % _vector_Quiz.size()];
}
