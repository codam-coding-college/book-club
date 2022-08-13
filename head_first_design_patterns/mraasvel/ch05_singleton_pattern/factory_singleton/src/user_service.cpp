#include "user_service.hpp"

UserService::UserService(FactoryService& factory) {
	this->db = DatabaseService::build(factory);
}

UserService::~UserService() {}

CleverPointer<IService> UserService::clone(FactoryService& factory) {
	auto pointer = std::unique_ptr<IService>(new UserService { factory });
	return CleverPointer<IService> (std::move(pointer));
}

CleverPointer<UserService> UserService::build(FactoryService& factory) {
	return factory.build("user").convert<UserService>();
}

void UserService::add(FactoryService& factory) {
	factory.add_service("user", std::unique_ptr<UserService>(new UserService { factory }));
}

User UserService::find_user(int id) const {
	auto user = db->users.find(id);
	if (user == db->users.end()) {
		printf("didn't find user\n");
		throw 404;
	}
	return user->second;
}

void UserService::add_user(User user) {
	db->users.insert(std::make_pair(user.id, std::move(user)));
}

void UserService::remove_user(int id) {
	db->users.erase(id);
}

void UserService::print() const {
	for (auto& it : db->users) {
		printf("User {\n\tid: %d\n\tname: %s\n}\n", it.second.id, it.second.username.c_str());
	}
}
