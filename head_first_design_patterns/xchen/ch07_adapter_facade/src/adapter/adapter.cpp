#include "adapter.hpp"
#include <iostream>

void	English::hello() {
	std::cout << name << ": Hello!\n";
}

std::string	English::getName() const {
	return name;
}

void French::bonjour() {
	std::cout << name << ": Bonjour!\n";
}

std::string	French::getName() const {
	return name;
}

void	FrenchAdapter::hello() {
	french.bonjour();
}
