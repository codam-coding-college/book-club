#include "user.hpp"

User::User(int id, const std::string& username)
: id(id), username(username) {}

User::User(int id, std::string&& username)
: id(id), username(username) {}
