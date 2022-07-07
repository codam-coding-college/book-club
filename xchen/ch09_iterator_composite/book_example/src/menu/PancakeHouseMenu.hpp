#pragma once
#include <vector>
#include "MenuItem.hpp"
#include "../iterator/iterator.hpp"

class PancakeHouseMenu {
	public:
		PancakeHouseMenu();
		void addItem(std::string name, std::string description, bool vegetarian, double price);
		const std::vector<MenuItem> &getMenuItems() const;
		Iterator<MenuItem> *createIteratorPtr() const;
		// other methods

	private:
		std::vector<MenuItem> menuItems;
};
