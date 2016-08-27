/*
Copyright © 2016 m0bec
Copyright © 2016 yumetodo
Copyright © 2016 kagucho_kamioda
Copyright © 2016 makuragi
Released under the MIT license
https://github.com/YukinobuKurata/YouTubeMagicBuyButton/blob/master/MIT-LICENSE.txt
*/
#ifndef UNO_INC_KEYHANDLER_HPP_
#define UNO_INC_KEYHANDLER_HPP_
#	if !defined(CINTERFACE) && defined(__c2__) &&  __clang_major__ == 3 && __clang_minor__ == 8
//To avoid compile error
//C:\Program Files (x86)\Windows Kits\8.1\Include\um\combaseapi.h(229,21): error : unknown type name 'IUnknown'
//          static_cast<IUnknown*>(*pp);    // make sure everyone derives from IUnknown
#		define CINTERFACE
#	endif
#include "no_min_max.h"
#include "DxLib.h"
#include <limits>
#include <array>
#include <vector>
#include <functional>
class key_handler_c
{
public:
	key_handler_c() noexcept : key_handler_cbuf() {
		this->fllush_stream();
	}
	key_handler_c(const key_handler_c&) = delete;
	key_handler_c(key_handler_c&&) = delete;
	key_handler_c& operator=(const key_handler_c&) = delete;
	key_handler_c& operator=(key_handler_c&&) = delete;
	bool update() noexcept {
		char buf[keybufsize];
		auto re = GetHitKeyStateAll(buf);
		if (0 != re) return false;
		for (size_t i = 0; i < keybufsize; ++i) {
			if (buf[i] && std::numeric_limits<int>::max() != this->key_handler_cbuf[i])++this->key_handler_cbuf[i];
			else this->key_handler_cbuf[i] = 0;
		}
		return true;
	}
	bool fllush() {
		if (this->fllush_stream()) return false;
		this->key_handler_cbuf.fill(0);
		return true;
	}
	int operator[](size_t n) const noexcept {
		return this->key_handler_cbuf[n];
	}

	int at(size_t n) const {
		return this->key_handler_cbuf.at(n);
	}
	bool shift() const noexcept {
		return this->lshift() || this->rshift();
	}
	bool lshift() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LSHIFT];
	}
	bool rshift() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RSHIFT];
	}
	bool ctrl() const noexcept {
		return this->lctrl() || this->rctrl();
	}
	bool lctrl() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LCONTROL];
	}
	bool rctrl() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RCONTROL];
	}
	bool esc() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_ESCAPE];
	}
	bool right() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RIGHT];
	}
	bool up() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_UP];
	}
	bool left() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LEFT];
	}
	bool down() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_DOWN];
	}
	bool enter() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RETURN];
	}
	bool space() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SPACE];
	}
	bool back() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_BACK];
	}
	bool tab() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_TAB];
	}
	bool pgup() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_PGUP];
	}
	bool pgdn() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_PGDN];
	}
	bool end() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_END];
	}
	bool home() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_HOME];
	}
	bool insert() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_INSERT];
	}
	bool del() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_DELETE];
	}
	bool f1() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F1];
	}
	bool f2() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F2];
	}
	bool f3() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F3];
	}
	bool f4() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F4];
	}
	bool f5() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F5];
	}
	bool f6() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F6];
	}
	bool f7() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F7];
	}
	bool f8() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F8];
	}
	bool f9() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F9];
	}
	bool f10() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F10];
	}
	bool f11() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F11];
	}
	bool f12() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F12];
	}
	bool a() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_A];
	}
	bool b() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_B];
	}
	bool c() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_C];
	}
	bool d() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_D];
	}
	bool e() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_E];
	}
	bool f() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_F];
	}
	bool g() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_G];
	}	
	bool h() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_H];
	}
	bool i() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_I];
	}
	bool j() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_J];
	}
	bool k() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_K];
	}
	bool l() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_L];
	}
	bool m() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_M];
	}
	bool n() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_N];
	}
	bool o() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_O];
	}
	bool p() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_P];
	}
	bool q() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_Q];
	}
	bool r() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_R];
	}
	bool s() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_S];
	}
	bool t() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_T];
	}
	bool u() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_U];
	}
	bool v() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_V];
	}
	bool w() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_W];
	}
	bool x() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_X];
	}
	bool y() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_Y];
	}
	bool z() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_Z];
	}
	bool top_zero() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_0];
	}
	bool top_one() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_1];
	}
	bool top_two() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_2];
	}
	bool top_three() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_3];
	}
	bool top_four() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_4];
	}
	bool top_five() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_5];
	}
	bool top_six() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_6];
	}
	bool top_seven() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_7];
	}
	bool top_eight() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_8];
	}
	bool top_nine() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_9];
	}
	bool numpad_zero() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD0];
	}
	bool numpad_one() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD1];
	}
	bool numpad_two() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD2];
	}
	bool numpad_three() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD3];
	}
	bool numpad_four() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD4];
	}
	bool numpad_five() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD5];
	}
	bool numpad_six() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD6];
	}
	bool numpad_seven() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD7];
	}
	bool numpad_eight() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD8];
	}
	bool numpad_nine() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPAD9];
	}
	bool zero() const noexcept {
		return this->top_zero() || this->numpad_zero();
	}
	bool one() const noexcept {
		return this->top_one() || this->numpad_one();
	}
	bool two() const noexcept {
		return this->top_two() || this->numpad_two();
	}
	bool three() const noexcept {
		return this->top_three() || this->numpad_three();
	}
	bool four() const noexcept {
		return this->top_four() || this->numpad_four();
	}
	bool five() const noexcept {
		return this->top_five() || this->numpad_five();
	}
	bool six() const noexcept {
		return this->top_six() || this->numpad_six();
	}
	bool seven() const noexcept {
		return this->top_seven() || this->numpad_seven();
	}
	bool eight() const noexcept {
		return this->top_eight() || this->numpad_eight();
	}
	bool nine() const noexcept {
		return this->top_nine() || this->numpad_nine();
	}
	bool minus() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_MINUS];
	}
	bool yen() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_YEN];
	}
	bool prevtrack() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_PREVTRACK];
	}
	bool period() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_PERIOD];
	}
	bool slash() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SLASH];
	}
	bool lalt() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LALT];
	}
	bool ralt() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RALT];
	}
	bool scroll() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SCROLL];
	}
	bool semicolon() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SEMICOLON];
	}
	bool colon() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_COLON];
	}
	bool lbracket() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LBRACKET];
	}
	bool rbracket() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RBRACKET];
	}
	bool atmark() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_AT];
	}
	bool backslash() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_BACKSLASH];
	}
	bool comma() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_COMMA];
	}
	bool kanji() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_KANJI];
	}
	bool convert() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_CONVERT];
	}
	bool noconvert() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NOCONVERT];
	}
	bool kana() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_KANA];
	}
	bool apps() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_APPS];
	}
	bool capslock() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_CAPSLOCK];
	}
	bool sysrq() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SYSRQ];
	}
	bool pause() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_PAUSE];
	}
	bool lwin() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_LWIN];
	}
	bool rwin() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_RWIN];
	}
	bool numlock() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMLOCK];
	}
	bool multiply() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_MULTIPLY];
	}
	bool add() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_ADD];
	}
	bool subtract() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_SUBTRACT];
	}
	bool decimal() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_DECIMAL];
	}
	bool divide() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_DIVIDE];
	}
	bool numpadenter() const noexcept {
		return 0 != this->key_handler_cbuf[KEY_INPUT_NUMPADENTER];
	}
	static constexpr size_t keybufsize = 256;
private:
	bool fllush_stream() {
		char buf[2][keybufsize] = {};
		for (size_t i = 0; i < this->key_handler_cbuf.size(); ++i) buf[0][i] = 0 != this->key_handler_cbuf[i];
		char* first_p;
		char* last_p;
		size_t i;
		for (first_p = buf[0], last_p = buf[1]; 0 == DxLib::GetHitKeyStateAll(last_p); std::swap(first_p, last_p)) {
			for (i = 0; i < keybufsize && !first_p[i] && !last_p[i]; ++i);
			if (i == keybufsize) return true;
		}
		return false;
	}
	std::array<int, keybufsize> key_handler_cbuf;
	std::array<std::vector<std::function<void()>>, keybufsize> registered_functions;
};
inline bool operator!=(const key_handler_c& l, size_t r) {
	return 0 == l[r];
}

inline bool operator!=(size_t l, const key_handler_c& r) {
	return r != l;
}
inline bool operator==(const key_handler_c& l, size_t r) {
	return !(l != r);
}
inline bool operator==(size_t l, const key_handler_c& r) {
	return !(l != r);
}
#endif //UNO_INC_KEYHANDLER_HPP_
