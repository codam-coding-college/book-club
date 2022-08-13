#include "remote.hpp"
#include <cassert>
#include <sstream>

inline void RemoteControl::check_limit(size_t n, size_t limit) {
	if (n >= limit) {
		throw PressButtonException(n);
	}
}

RemoteControl::RemoteControl() {
	for (size_t i = 0; i < buttons.size(); i++) {
		buttons[i] = command_type { new NoCommand {} };
	}
}

void RemoteControl::press_on(size_t slot) {
	check_limit(slot, NUM_BUTTONS);
	press_button(slot);
}

void RemoteControl::press_off(size_t slot) {
	size_t n = NUM_BUTTONS + slot;
	check_limit(n, buttons.size());
	press_button(n);
}

void RemoteControl::press_button(size_t n) {
	buttons[n]->execute();
	history.push(n);
}

void RemoteControl::undo() {
	if (history.empty()) {
		return;
	}
	size_t n = history.top();
	history.pop();
	buttons[n]->undo();
}

void RemoteControl::set_device(size_t slot, command_type on, command_type off) {
	check_limit(slot, NUM_BUTTONS);
	buttons[slot] = std::move(on);
	buttons[NUM_BUTTONS + slot] = std::move(off);
}

/* Exception */

RemoteControl::PressButtonException::PressButtonException(size_t n) {
	std::stringstream ss;
	ss << "invalid button index: " << n;
	reason = ss.str();
}

const char* RemoteControl::PressButtonException::what() const noexcept {
	return reason.c_str();
}
