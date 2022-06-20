#include "./adapter/adapter.hpp"
#include <iostream>
#include "./utility/color.hpp"

int main() {
	English david("david");
	French leo("leo");
	FrenchAdapter leo_adapter(leo);

	std::cout << MAGENTA_BOLD << ">> david.hello()\n " << RESET_COLOR;
	david.hello();
	std::cout << MAGENTA_BOLD << ">> leo.bonjour()\n " << RESET_COLOR;
	leo.bonjour();
	std::cout << MAGENTA_BOLD << ">> leo_adpater.hello()\n " << RESET_COLOR;
	leo_adapter.hello();
}
