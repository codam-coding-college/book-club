#pragma once
#include "../menu/DinerMenu.hpp"
#include "../menu/PancakeHouseMenu.hpp"

class Waitress {
	public:
		Waitress(PancakeHouseMenu p, DinerMenu d): pancakeHouseMenu(p), dinerMenu(d) {}
		void printMenu(Iterator<MenuItem> *iterator) const;
		void printMenu() const;

	private:
		PancakeHouseMenu pancakeHouseMenu;
		DinerMenu dinerMenu;
};
