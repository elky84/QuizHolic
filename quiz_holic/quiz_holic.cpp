#include "stdafx.h"
#include "Main.h"
#include "WindowUtil.h"
#include "resource.h"
#include "EnvironmentDirectX.h"

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	const std::wstring strClassName = _T("quiz_holic");
	if(false == light::WindowUtil::register_class(strClassName, CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW, ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_QUIZHOLIC))))
		return FALSE;

	RECT rect = {0, 0, 1024, 768};
	RUN_MAIN_DIRECTX(Main, strClassName, strClassName, rect);
	return 0;
}
