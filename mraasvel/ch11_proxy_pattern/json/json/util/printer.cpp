#include "printer.hpp"
#include <iostream>

namespace util {

Printer::Printer() {
	std::cout << "construct" << " " << this << std::endl;
}

Printer::Printer(const Printer&) {
	std::cout << "copy construct" << " " << this << std::endl;
}

Printer::Printer(Printer&&) {
	std::cout << "move construct" << " " << this << std::endl;
}

Printer& Printer::operator=(const Printer&) {
	std::cout << "assign" << " " << this << std::endl;
	return *this;
}

Printer& Printer::operator=(Printer&&) {
	std::cout << "move assign" << " " << this << std::endl;
	return *this;
}

Printer::~Printer() {
	std::cout << "destruct" << " " << this << std::endl;
}

}
