#pragma once

#include "Singleton.h"
#include "CharacterInterface.h"

#include <set>
#include <map>
#include <vector>
#include <memory>

class CharacterManager : public light::Singleton<CharacterManager>
{
public:
	typedef std::map< int, CHARACTER_INFORMATION> MAP_CHARACTER_INFORMATION;

private:
	typedef std::map< int, std::shared_ptr<CharacterInterface> > MAP_CHARACTER_INTERFACE;
	typedef std::set<int> SET_CHARACTER_IDX;
	typedef std::vector<int> VECTOR_CHARACTER_IDX;

public:
	CharacterInterface* CreateCharacter(light::weak_raw_ptr<light::view::DirectX> directX, const int &nIdx, const light::POSITION_INT& pos);

	CharacterInterface* CreateMc(light::weak_raw_ptr<light::view::DirectX> directX,  const int &nIdx, const light::POSITION_INT& pos);

	int GetRandomCharacterIdx();

	bool Load();

	void Draw();

	void Set();

	void Release();

	MAP_CHARACTER_INFORMATION& MapCharacterInformation()
	{
		return m_mapCharacterInformation;
	}

private:
	void InsertCharacter(CharacterInterface* pCharacterInterface);
	CHARACTER_INFORMATION* GetCharacterInformation(int nIdx);
	bool isAlreadySelectCharacter(int nIdx);

private:
	MAP_CHARACTER_INFORMATION m_mapCharacterInformation;

	MAP_CHARACTER_INTERFACE m_mapCharacterInterface;

	VECTOR_CHARACTER_IDX m_vectorNonSelectCharacterIdx;

	SET_CHARACTER_IDX m_set_SelectCharacterIdx;
};
