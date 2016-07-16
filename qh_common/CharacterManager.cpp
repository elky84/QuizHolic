#include "stdafx.h"
#include "CharacterManager.h"

#include "Character.h"
#include "Mc.h"

#include "XMLParser.h"
#include "DirectoryUtil.h"

#include <algorithm>

CharacterInterface* CharacterManager::CreateCharacter(light::weak_raw_ptr<light::view::DirectX> directX, const int &nIdx, const light::POSITION_INT& pos)
{
	if( true == isAlreadySelectCharacter(nIdx))
		return NULL;

	CHARACTER_INFORMATION* pCharacterInformation = GetCharacterInformation(nIdx);
	if(NULL == pCharacterInformation)
		return NULL;

	Character * pCharacter = new Character(directX, nIdx, pos, *pCharacterInformation);
	InsertCharacter(pCharacter);
	return pCharacter;
}

CharacterInterface* CharacterManager::CreateMc(light::weak_raw_ptr<light::view::DirectX> directX, const int &nIdx, const light::POSITION_INT& pos)
{
	if( true == isAlreadySelectCharacter(nIdx))
		return NULL;

	CHARACTER_INFORMATION* pCharacterInformation = GetCharacterInformation(nIdx);
	if(NULL == pCharacterInformation)
		return NULL;

	Mc* pMc = new Mc(directX, nIdx, pos, *pCharacterInformation);
	InsertCharacter(pMc);
	return pMc;
}

bool CharacterManager::isAlreadySelectCharacter(int nIdx)
{
	return m_set_SelectCharacterIdx.end() != m_set_SelectCharacterIdx.find(nIdx);
}

CHARACTER_INFORMATION* CharacterManager::GetCharacterInformation(int nIdx)
{
	MAP_CHARACTER_INFORMATION::iterator it = m_mapCharacterInformation.find(nIdx);
	if(it == m_mapCharacterInformation.end())
		return NULL;

	return &it->second;
}

void CharacterManager::InsertCharacter(CharacterInterface* pCharacterInterface)
{
	m_mapCharacterInterface.insert(MAP_CHARACTER_INTERFACE::value_type(pCharacterInterface->GetIdx(), std::shared_ptr<CharacterInterface>(pCharacterInterface)));
	m_vectorNonSelectCharacterIdx.erase(find(m_vectorNonSelectCharacterIdx.begin(), m_vectorNonSelectCharacterIdx.end(), pCharacterInterface->GetIdx()));
	m_set_SelectCharacterIdx.insert(pCharacterInterface->GetIdx());
}

int CharacterManager::GetRandomCharacterIdx()
{
	if(m_vectorNonSelectCharacterIdx.empty())
		return 1;

	return m_vectorNonSelectCharacterIdx[rand() % m_vectorNonSelectCharacterIdx.size()];
}

bool CharacterManager::Load()
{
	std::wstring strName = _T("Character\\Character.xml");
	light::XMLParser parser;
	if( false == parser.read_file(strName))
		return false;

	std::wstring strDirectory = light::get_path_without_file_name(strName);

	if( false == parser.execute(_T("/CharacterList")))
		return false;

	if( false == parser.bind_elem(_T("Character")))
		return false;

	long nIdx = 0;
	std::wstring strCharacterName, strMiniTexture, strBigTexture;
	if( false == parser.bind_attrib(_T("Idx"), nIdx))
		return false;

	if( false == parser.bind_attrib(_T("Name"), strCharacterName))
		return false;

	if( false == parser.bind_attrib(_T("MiniTexture"), strMiniTexture))
		return false;

	if( false == parser.bind_attrib(_T("BigTexture"), strBigTexture))
		return false;

	while(parser.next())
	{
		m_mapCharacterInformation.insert(MAP_CHARACTER_INFORMATION::value_type(nIdx, CHARACTER_INFORMATION(strCharacterName, strMiniTexture, strBigTexture)));
		m_vectorNonSelectCharacterIdx.push_back(nIdx);
	}
	return true;
}

void CharacterManager::Draw()
{
	for(auto it = m_mapCharacterInterface.begin(); it != m_mapCharacterInterface.end(); ++it)
	{
		auto character = it->second;
        character->Draw();
	}
}

void CharacterManager::Set()
{
	for(auto it = m_mapCharacterInterface.begin(); it != m_mapCharacterInterface.end(); ++it)
	{
        auto character = it->second;
        character->Set();
	}
}

void CharacterManager::Release()
{
	m_mapCharacterInterface.clear();
	for(auto it = m_set_SelectCharacterIdx.begin(); it != m_set_SelectCharacterIdx.end(); ++it)
	{
		m_vectorNonSelectCharacterIdx.push_back(*it);
	}
	m_set_SelectCharacterIdx.clear();
}
