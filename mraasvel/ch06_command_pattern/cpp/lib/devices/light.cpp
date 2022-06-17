#include "devices/light.hpp"

Light::Light()
: is_on(false) {}

void Light::on() {
	is_on = true;
}

void Light::off() {
	is_on = false;
}
