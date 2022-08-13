#pragma once

#include "command.hpp"
#include "devices/light.hpp"

class LightOn: public ICommand {
	public:
		LightOn(Light& light);
		void execute();
		void undo();
	private:
		Light& light;
};

class LightOff: public ICommand {
	public:
		LightOff(Light& light);
		void execute();
		void undo();
	private:
		Light& light;
};
