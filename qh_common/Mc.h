#pragma once

#include "CharacterInterface.h"

class Mc : public CharacterInterface
{
public:
	Mc(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation);
	virtual ~Mc();

protected:
	virtual void Ask(std::wstring strMessage, light::view::Gui::Callback callback, DWORD dwTooltipTick);
};
