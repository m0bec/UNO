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
	static const auto gray = DxLib::GetColor(128, 128, 128);
	int old_mouse_x, old_mouse_y;
	GetMousePoint(&old_mouse_x, &old_mouse_y);
	int box_lx = 2, box_ly = 2, box_rx = 40, box_ry = 40;
	bool on_mouse_drag = false;
	while (DxLib::ProcessMessage() == 0 && DxLib::CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		DxLib::DrawBox(box_lx, box_ly, box_rx, box_ry, gray, true);
		int mouse_x, mouse_y;
		GetMousePoint(&mouse_x, &mouse_y);
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (mouse_x > box_lx && mouse_x < box_rx && mouse_y > box_ly && mouse_y < box_ry) on_mouse_drag = true;
		}
		else {
			on_mouse_drag = false;
		}
		if (on_mouse_drag) {
			box_lx += mouse_x - old_mouse_x;
			box_ly += mouse_y - old_mouse_y;
			box_rx += mouse_x - old_mouse_x;
			box_ry += mouse_y - old_mouse_y;
		}
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;
		::Sleep(20);//Win32API
		DxLib::ScreenFlip();
	}
	return 0;
}
