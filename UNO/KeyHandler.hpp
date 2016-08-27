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
	std::array<int, 256> key_handler_cbuf;
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
