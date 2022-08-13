#pragma once

#include "user.hpp"
#include "iservice.hpp"
#include <unordered_map>

class FactoryService;

struct DatabaseService: public IService {
public:
	CleverPointer<IService> clone(FactoryService& factory);

	static void add(FactoryService& factory);
	static CleverPointer<DatabaseService> build(FactoryService& factory);

	std::unordered_map<int, User> users;
private:
};
