/*
Copyright © 2016 m0bec
Copyright © 2016 yumetodo
Copyright © 2016 kagucho_kamioda
Released under the MIT license
https://github.com/YukinobuKurata/YouTubeMagicBuyButton/blob/master/MIT-LICENSE.txt
*/
#if !defined(CINTERFACE) && defined(__c2__) &&  __clang_major__ == 3 && __clang_minor__ == 8
//To avoid compile error
//C:\Program Files (x86)\Windows Kits\8.1\Include\um\combaseapi.h(229,21): error : unknown type name 'IUnknown'
//          static_cast<IUnknown*>(*pp);    // make sure everyone derives from IUnknown
#define CINTERFACE
#endif
#include <DxLib.h>
int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	DxLib::SetOutApplicationLogValidFlag(FALSE);
	DxLib::SetGraphMode(720, 408, 16);
	DxLib::ChangeWindowMode(TRUE);
	DxLib::SetBackgroundColor(255, 255, 255);
	if (DxLib::DxLib_Init() == -1)return -1;// エラーが起きたら直ちに終了
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	DxLib::ClearDrawScreen();
	while (DxLib::ProcessMessage() == 0 && DxLib::CheckHitKeyAll() == 0 && DxLib::GetMouseWheelRotVol() == 0 && DxLib::GetMouseInput() == 0) {
		ClearDrawScreen();
		DxLib::DrawBox(2, 2, 40, 40, DxLib::GetColor(128, 128, 128), true);
		::Sleep(20);//Win32API
		DxLib::ScreenFlip();
	}
	return 0;
}
