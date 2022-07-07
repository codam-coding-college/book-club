#include "PancakeHouseMenu.hpp"
#include "DinerMenu.hpp"
#include <iostream>
#include "../utility/color.hpp"

/* MenuItem */
std::string MenuItem::getName() const { return name; }
std::string MenuItem::getDescription() const { return description; }
bool MenuItem::isVegetarian() const { return vegetarian; }
double MenuItem::getPrice() const { return price; }
void MenuItem::print() const {
		std::cout 
		<< BLUE << name << RESET_COLOR
		<< " -- "
		<< YELLOW << "$" << price << RESET_COLOR
		<< " -- "
		<< description;
		if (vegetarian) {
			std::cout << GREEN << " [V]" << RESET_COLOR;
		}
		std::cout << std::endl;
};

/* PancakeHouseMenu */
PancakeHouseMenu::PancakeHouseMenu() {
	addItem("K&Bs Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
	addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
	addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
	addItem("Waffles”,", "“Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void PancakeHouseMenu::addItem(std::string name, std::string description, bool vegetarian, double price) {
	MenuItem item(name, description, vegetarian, price);
	menuItems.push_back(item);
}

const std::vector<MenuItem> &PancakeHouseMenu::getMenuItems() const { return menuItems; }

Iterator<MenuItem> *PancakeHouseMenu::createIteratorPtr() const { return new PancakeHouseMenuIterator<MenuItem>(menuItems); }

/* DinerMenu */
DinerMenu::DinerMenu() {
	menuItems = new MenuItem[MAX_ITEMS];
	addItem("Vegetarian BLT", "Bacon with lettuce & tomato on whole wheat", true, 2.99);
	addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
	addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
	addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
}

void DinerMenu::addItem(std::string name, std::string description, bool vegetarian, double price) {
	if (numberOfItems >= MAX_ITEMS) {
		std::cout << "Sorry, menu is full.\n";
	} else {
		MenuItem item(name, description, vegetarian, price);
		menuItems[numberOfItems] = item;
		numberOfItems++;
	}
}

MenuItem *DinerMenu::getMenuItems() const { return menuItems; }

Iterator<MenuItem> *DinerMenu::createIteratorPtr() const {return new DinerMenuIterator<MenuItem>(menuItems, MAX_ITEMS);}