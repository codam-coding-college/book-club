#pragma once
#include "../iterator/iterator.hpp"
#include "../iterator/iterator.hpp"

class DinerMenu {
	public:
		DinerMenu();
		void addItem(std::string name, std::string description, bool vegetarian, double price);
		MenuItem *getMenuItems() const;
		Iterator<MenuItem> *createIteratorPtr() const; 
		// other methods

	private:
		static int const MAX_ITEMS = 6;
		int numberOfItems = 0;
		MenuItem* menuItems;
};
