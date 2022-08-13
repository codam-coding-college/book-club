#include "factory_service.hpp"
#include "database.hpp"
#include "user_service.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

void init_factory() {
	FactoryService& factory = FactoryService::get();
	DatabaseService::add(factory);
	UserService::add(factory);
}

void user_stuff() {
	auto user_service = UserService::build(FactoryService::get());
	user_service->add_user(User {
		1, std::string { "nice" },
	});
	auto user = user_service->find_user(0);
	user_service->print();
}

int main() {
	init_factory();

	FactoryService& factory = FactoryService::get();
	std::cout << "building user service" << std::endl;
	auto user_service = UserService::build(factory);

	user_service->add_user(User {
		0, std::string { "Maarten" },
	});
	user_stuff();
	auto db = DatabaseService::build(factory);
	return 0;
}
