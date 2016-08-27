/*
Copyright © 2016 m0bec
Copyright © 2016 yumetodo
Copyright © 2016 kagucho_kamioda
Copyright © 2016 makuragi
Released under the MIT license
https://github.com/YukinobuKurata/YouTubeMagicBuyButton/blob/master/MIT-LICENSE.txt
*/
#ifndef UNO_INC_MOUSEEVENTHANDLER_HPP_
#define UNO_INC_MOUSEEVENTHANDLER_HPP_
#include <dxlibex/basic_types.hpp>
#include <DxLib.h>
#include <memory>
#include <vector>
#include <cstdint>
#include <functional>
#define UNO_RUNTIME_ERROR_THROW_WITH_MESSAGE( MESSAGE ) throw uno::runtime_error(__FILE__, __FUNCTION__, __LINE__, MESSAGE)
#define UNO_RUNTIME_ERROR_THROW_WITH_MESSAGE_IF( EXPR, MESSAGE ) if( EXPR ) throw uno::runtime_error(__FILE__, __FUNCTION__, __LINE__, #EXPR, MESSAGE)
#define UNO_MOUSE_INPUT_ERROR_THROW_WITH_MESSAGE( MESSAGE ) throw uno::mouse_input_error(__FILE__, __FUNCTION__, __LINE__, MESSAGE)
#define UNO_MOUSE_INPUT_ERROR_THROW_WITH_MESSAGE_IF( EXPR, MESSAGE ) if( EXPR ) throw uno::mouse_input_error(__FILE__, __FUNCTION__, __LINE__, #EXPR, MESSAGE)

namespace uno {
	namespace exception {
		class runtime_error : public std::runtime_error {
		protected:
			runtime_error(const char* except_name, const char* sorce_name, const char* func_name, std::uint64_t line, const char* expression, const std::string& msg)
				: std::runtime_error(
					std::string("exception : ") + except_name + '\n'
					+ "  in " + sorce_name + "\n"
					+ "  " + func_name + "() (line." + std::to_string(line) + ")\n"
					+ "  follow by below\n"
					+ "    " + expression
					+ ((msg.empty() || msg[0] == '\0') ? "\n" : "\n  MESSAGE : " + msg + "\n")
				)
			{}
			runtime_error(const char* except_name, const char* sorce_name, const char* func_name, std::uint64_t line, const std::string& msg)
				: std::runtime_error(
					std::string("exception : ") + except_name + '\n'
					+ " in " + sorce_name + "\n"
					+ "  " + func_name + "() (line." + std::to_string(line) + ")\n"
					+ ((msg.empty() || msg[0] == '\0') ? "\n" : " MESSAGE : " + msg + "\n")
				)
			{}
		public:
			runtime_error(const char* sorce_name, const char* func_name, std::uint64_t line, const char* expression, const std::string& msg)
				: runtime_error("runtime_error", sorce_name, func_name, line, expression, msg) {}
			runtime_error(const char* sorce_name, const char* func_name, std::uint64_t line, const std::string& msg)
				: runtime_error("runtime_error", sorce_name, func_name, line, msg) {}
		};

	}
	using exception::runtime_error;
	namespace exception {
		class mouse_input_error : public uno::exception::runtime_error {
		public:
			mouse_input_error(const char* sorce_name, const char* func_name, std::uint64_t line, const char* expression, const std::string& msg)
				: uno::exception::runtime_error("mouse_input_error", sorce_name, func_name, line, expression, msg) {}
			mouse_input_error(const char* sorce_name, const char* func_name, std::uint64_t line, const std::string& msg)
				: uno::exception::runtime_error("mouse_input_error", sorce_name, func_name, line, msg) {}
		};

	}
	using exception::mouse_input_error;
	enum class mouse_event : std::uint8_t {
		click,
		double_click,
		right_click,
		enter,
		leave,
		hover,
		hovering,
		drag,
		size
	};
	class mouse_event_handler_c {
	public:
		mouse_event_handler_c() = default;
		mouse_event_handler_c(const mouse_event_handler_c&) = delete;
		mouse_event_handler_c(mouse_event_handler_c&&) = delete;
		mouse_event_handler_c& operator=(const mouse_event_handler_c&) = delete;
		mouse_event_handler_c& operator=(mouse_event_handler_c&&) = delete;
		bool update() {
			const auto mouse_state = DxLib::GetMouseInput();
			const auto mouse_pos = this->GetMousePoint();
			//drag eventのためのマウス座標記録
			if (!mouse_state) {
				pos_record.clear();
			}
			else {
				pos_record.push_back(mouse_pos);
			}

		}
		template<typename Function>
		auto register_handler(uno::mouse_event e, std::shared_ptr<dxle::pointi> pos, Function&& f) -> decltype(f(), std::size_t{}) {
			auto& arr = mouse_event_handler_array[static_cast<std::underlying_type_t<uno::mouse_event>>(e)];
			arr.push_back(std::forward<Function>(f));
			return arr.size() - 1;
		}
		void remove_handler(uno::mouse_event e, std::size_t handler_number) {
			auto& arr = mouse_event_handler_array[static_cast<std::underlying_type_t<uno::mouse_event>>(e)];
			arr.erase(arr.begin() + handler_number);
		}
	private:
		dxle::pointi GetMousePoint(std::nothrow_t) {
			dxle::pointi re;
			if (!DxLib::GetMousePoint(&re.x, &re.y)) return{};
			return re;
		}
		dxle::pointi GetMousePoint() {
			dxle::pointi re;
			UNO_MOUSE_INPUT_ERROR_THROW_WITH_MESSAGE_IF(!DxLib::GetMousePoint(&re.x, &re.y), "");
			return re;
		}
		std::vector<dxle::pointi> pos_record;
		std::array<std::vector<std::function<void()>>, static_cast<std::underlying_type_t<uno::mouse_event>>(uno::mouse_event::size)> mouse_event_handler_array;
	};
}
#endif //UNO_INC_MOUSEEVENTHANDLER_HPP_
