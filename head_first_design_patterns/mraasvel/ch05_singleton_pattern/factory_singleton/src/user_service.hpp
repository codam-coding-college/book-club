#pragma once

#include "iservice.hpp"
#include "database.hpp"
#include "user.hpp"
#include "factory_service.hpp"

class UserService: public IService {
public:
	UserService(FactoryService& factory);
	~UserService();

	CleverPointer<IService> clone(FactoryService& factory);

	static CleverPointer<UserService> build(FactoryService& factory);
	static void add(FactoryService& factory);

	User find_user(int id) const;
	void add_user(User user);
	void remove_user(int id);

	void print() const;

private:
	CleverPointer<DatabaseService> db;
};
