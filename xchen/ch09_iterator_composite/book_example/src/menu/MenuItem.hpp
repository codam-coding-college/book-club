#pragma once
#include <string>

class MenuItem {
	public:
		MenuItem(std::string name, std::string description, bool vegetarian, double price): name(name), description(description), vegetarian(vegetarian), price(price) {}
		MenuItem() {}
		std::string getName() const;
		std::string getDescription() const;
		bool isVegetarian() const;
		double getPrice() const;

		void print() const;

	private:
		std::string name;
		std::string description;
		bool vegetarian;
		double price;
};
