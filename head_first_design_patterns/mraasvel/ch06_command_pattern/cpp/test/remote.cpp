#include "remote.hpp"
#include "command.hpp"
#include <catch2/catch.hpp>
#include <iostream>

struct Dummy {
	Dummy(): test(false) {}
	bool test;
};

class DummyOn: public ICommand {
public:
	DummyOn(Dummy& dummy): dummy(dummy) {}
	Dummy& dummy;
	void execute() {
		dummy.test = true;
	}
	void undo() {
		dummy.test = false;
	}
};

class DummyOff: public ICommand {
	public:
		DummyOff(Dummy& dummy): dummy(dummy) {}
		Dummy& dummy;
		void execute() {
			dummy.test = false;
		}
		void undo() {
			dummy.test = true;
		}
};

template <typename T, class... Args>
std::unique_ptr<ICommand> create(Args&&... args) {
	return std::unique_ptr<ICommand> { new T (args...) };
}

TEST_CASE("remote") {
	RemoteControl control;
	control.press_on(5);
	try {
		control.press_on(8);
		REQUIRE(false);
	} catch (std::exception& e) {}
}

TEST_CASE("off") {
	RemoteControl control;
	control.press_off(6);
	try {
		control.press_off(7);
		REQUIRE(false);
	} catch (std::exception& e) {}
}

TEST_CASE("dummy") {
	RemoteControl control;
	Dummy dummy;
	control.set_device(0, create<DummyOn>(dummy), create<DummyOff>(dummy));
	REQUIRE(dummy.test == false);
	control.press_on(0);
	REQUIRE(dummy.test == true);
	control.undo();
	REQUIRE(dummy.test == false);
	control.press_on(0);
	REQUIRE(dummy.test == true);
	control.press_off(0);
	REQUIRE(dummy.test == false);
	control.press_off(0);
	REQUIRE(dummy.test == false);
	// undo both press_off
	control.undo();
	REQUIRE(dummy.test == true);
	control.undo();
	REQUIRE(dummy.test == true);
	// undo first press_on
	control.undo();
	REQUIRE(dummy.test == false);
	// nothing left to undo
	control.undo();
	REQUIRE(dummy.test == false);
}
