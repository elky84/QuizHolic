#include "stdafx.h"

#include "CharacterInterface.h"
#include "CharacterManager.h"

#include "DirectoryUtil.h"

CharacterInterface::CharacterInterface(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation)
: m_direct_x(directX)
, m_Pos(pos)
, m_Idx(nIdx)
, m_CharacterInformation(CharacterInformation)
, m_Point(0)
{
	m_ProgressBar.Create(m_direct_x, _T("Gui\\ProgressBar.spr"), light::POSITION_INT(m_Pos.X(),  m_Pos.Y() - 20), 100, 2);
	m_ProgressBar.SetProgress(1, 0);
}

CharacterInterface::~CharacterInterface()
{
}

void CharacterInterface::AddPoint(int nPoint)
{
	m_Point += nPoint;

	m_ProgressBar.SetProgress(1, m_Point / 10.0f);
	ShowPoint();
}

void CharacterInterface::ShowPoint()
{
	std::wstringstream strStream;
	strStream << _T("지금 현재 점수는 ") << m_Point << _T("입니다");
	Ask(strStream.str(), NULL);

	m_ProgressBar.Set();
}

void CharacterInterface::Set()
{
	m_Button.Set();
	m_BackToolTip.Set();
}

void CharacterInterface::Draw()
{
}

void CharacterInterface::Ask(std::wstring strMessage, light::view::Gui::Callback callback /* = NULL */, DWORD dwTooltipTick /* = 500 */)
{
	m_ToolTipAsk.SetCallback(callback);
	m_ToolTipAsk.Show( strMessage, light::POSITION_INT(m_Pos.X(), m_Button.GetRect().Bottom() + m_Pos.Y()), 15, dwTooltipTick);
}
