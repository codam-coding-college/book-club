#pragma once

#include <string>

struct User {
	User(int id = -1, const std::string& username = "default");
	// move constructor
	User(int id = -1, std::string&& username = "default");

	int id;
	std::string username;
};
