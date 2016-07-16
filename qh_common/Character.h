#pragma once

#include "CharacterInterface.h"

class Character : public CharacterInterface
{
public:
	Character(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation);
	virtual ~Character();

protected:
	virtual void Ask(std::wstring strMessage, light::view::Gui::Callback callback, DWORD dwTooltipTick);
};
