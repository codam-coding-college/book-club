#include <iostream>
#include "./utility/color.hpp"
#include "./waitress/Waitress.hpp"

int main() {
	PancakeHouseMenu pancakeHouseMenu;
	DinerMenu dinerMenu;
	Waitress waitress(pancakeHouseMenu, dinerMenu);

	waitress.printMenu();
}
