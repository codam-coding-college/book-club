#include "variant.hpp"
#include <cassert>

namespace variant {

Json::JsonData::JsonData(int n): n(n) {}
Json::JsonData::JsonData(bool b): b(b) {}
Json::JsonData::JsonData(const std::string& str): str(str) {}
Json::JsonData::JsonData(std::vector<Json*>&& array): array(std::move(array)) {}
Json::JsonData::JsonData(std::unordered_map<std::string, Json*>&& object): object(std::move(object)) {}
Json::JsonData::~JsonData() {
	std::cout << "Json Data destructor " << this << std::endl;
}

Json::Json(): type(Null) {}
Json::Json(int n): data(n), type(Number) {}
Json::Json(bool b): data(b), type(Boolean) {}
Json::Json(const std::string& s): data(s), type(String) {}
Json::Json(ArrayType&& array): data(std::move(array)), type(Array) {}
Json::Json(ObjectType&& object): data(std::move(object)), type(Object) {}

Json::~Json() {
	std::cout << "Json destructor: " << this << std::endl;
	switch (type) {
		case Number:
			break;
		case Boolean:
			break;
		case String:
			destroy_string();
			break;
		case Array:
			destroy_array();
			break;
		case Object:
			destroy_object();
			break;
		case Null:
			break;
	}
}

void Json::destroy_int() {}
void Json::destroy_bool() {}
void Json::destroy_string() {}

void Json::destroy_array() {
	std::cout << "destroy array " << this << std::endl;
	auto array = get_array();
	for (Json* x : array) {
		std::cout << "delete array element " << x << std::endl;
		delete x;
	}
}

void Json::destroy_object() {
	std::cout << "destroy object " << this << std::endl;
	auto object = get_object();
	for (auto x: object) {
		std::cout << "delete map entry " << x.first << " -> " << x.second << std::endl;
		delete x.second;
	}
}

Json::JsonType Json::get_type() const {
	return type;
}

int Json::get_num() const {
	assert(type == Number);
	return data.value().n;
}

bool Json::get_bool() const {
	assert(type == Boolean);
	return data.value().b;
}

const std::string& Json::get_string() const {
	assert(type == String);
	return data.value().str;
}

const Json::ArrayType& Json::get_array() const {
	assert(type == Array);
	return data.value().array;
}

const Json::ObjectType& Json::get_object() const {
	assert(type == Object);
	return data.value().object;
}

}
