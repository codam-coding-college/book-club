#include "commands/light_command.hpp"
#include "devices/light.hpp"

LightOn::LightOn(Light& light)
: light(light) {}

void LightOn::execute() {
	light.on();
}

void LightOn::undo() {
	light.off();
}

LightOff::LightOff(Light& light)
: light(light) {}

void LightOff::execute() {
	light.off();
}

void LightOff::undo() {
	light.on();
}
