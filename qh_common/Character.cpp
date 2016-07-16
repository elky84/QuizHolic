#include "stdafx.h"
#include "Character.h"

#include "DirectoryUtil.h"

Character::Character(light::weak_raw_ptr<light::view::DirectX> directX, const int& nIdx, const light::POSITION_INT& pos, const CHARACTER_INFORMATION& CharacterInformation)
: CharacterInterface(directX, nIdx, pos, CharacterInformation)
{
	m_Button.Create(m_direct_x, _T("Character\\MiniTemplate.spr"), light::get_file_name_without_path(CharacterInformation.MiniTexture()), NULL, pos);
	m_ToolTipAsk.Create(m_direct_x, _T("Common\\Mini_ToolTip.spr"));
	m_BackToolTip.Create(m_direct_x, _T("Common\\Mini_Back_ToolTip.spr"), NULL, light::POSITION_INT(m_Button.GetRect().Right() + m_Pos.X(), m_Pos.Y()));
}

Character::~Character()
{

}

void Character::Ask(std::wstring strMessage, light::view::Gui::Callback callback, DWORD dwTooltipTick)
{
	m_ToolTipAsk.SetCallback(callback);
	m_ToolTipAsk.Show( strMessage, light::POSITION_INT(m_Button.GetRect().Right() + m_Pos.X(), m_Pos.Y()), 15, dwTooltipTick, D3DCOLOR_RGBA(255, 255, 255, 255));
}