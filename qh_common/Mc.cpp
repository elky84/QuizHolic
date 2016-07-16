#include "stdafx.h"
#include "Mc.h"

#include "DirectoryUtil.h"

Mc::Mc(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation)
: CharacterInterface(directX, nIdx, pos, CharacterInformation)
{
	m_Button.Create(m_direct_x, _T("Character\\BigTemplate.spr"), light::get_file_name_without_path(CharacterInformation.BigTexture()), NULL, pos);
	m_ToolTipAsk.Create(m_direct_x, _T("Common\\ToolTip.spr"));
	m_BackToolTip.Create(m_direct_x, _T("Common\\Back_ToolTip.spr"), NULL, light::POSITION_INT(m_Pos.X(), m_Button.GetRect().Bottom() + m_Pos.Y()));
}

Mc::~Mc()
{

}

void Mc::Ask(std::wstring strMessage, light::view::Gui::Callback callback, DWORD dwTooltipTick)
{
	m_ToolTipAsk.SetCallback(callback);
	m_ToolTipAsk.Show( strMessage, light::POSITION_INT(m_Pos.X(), m_Button.GetRect().Bottom() + m_Pos.Y()), 40, dwTooltipTick, D3DCOLOR_RGBA(255, 255, 255, 255));
}