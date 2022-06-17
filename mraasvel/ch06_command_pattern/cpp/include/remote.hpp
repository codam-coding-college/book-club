#pragma once

#include "command.hpp"
#include <exception>
#include <stack>
#include <memory>
#include <array>

/*
The RemoteControl is the `invoker` part of the command pattern
*/
class RemoteControl {
	private:
		static constexpr size_t NUM_BUTTONS = 7;
		using command_type = std::unique_ptr<ICommand>;
		using array_type = std::array<command_type, NUM_BUTTONS * 2>;

	public:
		RemoteControl();
		void press_on(size_t slot);
		void press_off(size_t slot);
		void undo();
		void set_device(size_t slot, command_type on, command_type off);

	private:
		static inline void check_limit(size_t n, size_t limit);
		void press_button(size_t n);
	
	public:
		class PressButtonException: public std::exception {
			public:
				PressButtonException(size_t n);
				std::string reason;
				virtual const char* what() const noexcept;
		};

	private:
		array_type buttons;
		std::stack<size_t> history; // history of button presses for undo
};
