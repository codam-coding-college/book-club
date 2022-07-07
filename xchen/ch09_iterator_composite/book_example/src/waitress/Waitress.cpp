#include "Waitress.hpp"
#include <iostream>
#include "../utility/color.hpp"

void Waitress::printMenu(Iterator<MenuItem>* iterator) const {
	while (iterator->hasNext()) {
		MenuItem item = iterator->next();
		item.print();
	}
}


void Waitress::printMenu() const {
	std::cout << MAGENTA_BOLD << "PancakeHouse Menu\n" << RESET_COLOR;
	Iterator<MenuItem> *iteratorPancakeHouse = pancakeHouseMenu.createIteratorPtr();
	printMenu(iteratorPancakeHouse);

	std::cout << MAGENTA_BOLD << "Diner Menu\n" << RESET_COLOR;
	Iterator<MenuItem> *iteratorDiner = dinerMenu.createIteratorPtr();
	printMenu(iteratorDiner);

}