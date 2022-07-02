#include "printer.hpp"
#include "option.hpp"
#include <vector>
#include <iostream>

using variant::Option;
using util::Printer;

Option<Printer> f(int n) {
	if (n % 2 == 0) {
		return Option { Printer {} };
	}
	return Option<Printer> {};
}

int main() {
	std::cout << std::boolalpha;
	{
		auto option = f(5);
		std::cout << option.is_some() << std::endl;
	}
	{
		auto option = f(6);
		std::cout << option.is_some() << std::endl;
		option.value();
	}
	return 0;
}
