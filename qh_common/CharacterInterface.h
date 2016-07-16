#pragma once

#include "Animation2D.h"
#include "Position.h"
#include "weak_raw_ptr.hpp"

#include "GuiTooltip.h"
#include "GuiProgressBar.h"
#include "GuiButton.h"

struct CHARACTER_INFORMATION
{
public:
	CHARACTER_INFORMATION(const std::wstring& strCharacterName, const std::wstring& strMiniTexture, const std::wstring& strBigTexture)
		: m_strCharacterName(strCharacterName)
		, m_strMiniTexture(strMiniTexture)
		, m_strBigTexture(strBigTexture)
	{

	}

	const std::wstring& MiniTexture() const 
	{
		return m_strMiniTexture;
	}

	const std::wstring& BigTexture() const 
	{
		return m_strBigTexture;
	}


private:
	std::wstring m_strCharacterName;
	std::wstring m_strMiniTexture;
	std::wstring m_strBigTexture;
};

class CharacterInterface
{
public:
	CharacterInterface(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation);
	virtual ~CharacterInterface();

	int GetIdx() {return m_Idx;}
	void Draw();

	void AddPoint(int nPoint);
	void ShowPoint();

public:
	virtual void Ask(std::wstring strMessage, light::view::Gui::Callback callback, DWORD dwTooltipTick = 500) = 0;

	virtual void Set();

protected:
	light::view::GuiButton m_Button;
	light::view::GuiTooltip m_ToolTipAsk;
	light::view::GuiButton m_BackToolTip;
	light::view::GuiProgressBar m_ProgressBar;

	const CHARACTER_INFORMATION& m_CharacterInformation;

	light::POSITION_INT m_Pos;

	int m_Point;
	const int m_Idx;

	light::weak_raw_ptr<light::view::DirectX> m_direct_x;
};
