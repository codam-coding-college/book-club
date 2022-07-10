#include "json.hpp"
#include <cassert>
#include <iostream>

namespace json {

Json::JsonData::JsonData(int n): n(n) {}
Json::JsonData::JsonData(bool b): b(b) {}
Json::JsonData::JsonData(const std::string& str): str(str) {}
Json::JsonData::JsonData(std::vector<std::unique_ptr<Json>>&& array)
: array(std::move(array)) {}
Json::JsonData::JsonData(std::unordered_map<std::string, std::unique_ptr<Json>>&& object)
: object(std::move(object)) {}
Json::JsonData::~JsonData() {}

Json::Json(): type(Type::Null) {}
Json::Json(int n): data(n), type(Type::Number) {}
Json::Json(bool b): data(b), type(Type::Boolean) {}
Json::Json(const std::string& s): data(s), type(Type::String) {}
Json::Json(ArrayType&& array): data(std::move(array)), type(Type::Array) {}
Json::Json(ObjectType&& object): data(std::move(object)), type(Type::Object) {}

Json::~Json() {
	switch (type) {
		case Type::Number:
			break;
		case Type::Boolean:
			break;
		case Type::String:
			destroy_string();
			break;
		case Type::Array:
			destroy_array();
			break;
		case Type::Object:
			destroy_object();
			break;
		case Type::Null:
			break;
	}
}

void Json::destroy_int() {}
void Json::destroy_bool() {}
void Json::destroy_string() {
	get_string().~basic_string();
}

void Json::destroy_array() {
	JsonData& json = data.value();
	json.array.~vector();
}

void Json::destroy_object() {
	JsonData& json = data.value();
	json.object.~unordered_map();
}

json::Type Json::get_type() const {
	return type;
}

int Json::get_num() const {
	assert(type == Type::Number);
	return data.value().n;
}

bool Json::get_bool() const {
	assert(type == Type::Boolean);
	return data.value().b;
}

const std::string& Json::get_string() const {
	assert(type == Type::String);
	return data.value().str;
}

const Json::ArrayType& Json::get_array() const {
	assert(type == Type::Array);
	return data.value().array;
}

const Json::ObjectType& Json::get_object() const {
	assert(type == Type::Object);
	return data.value().object;
}

void Json::print() const {
	std::cout << "Json: ";
	print_depth(0);
	std::cout << std::endl;
}

static void print_tabs(int depth) {
	while (depth-- > 0) {
		std::cout << '\t';
	}
}

void Json::print_array(int depth) const {
	const auto& array = get_array();
	std::cout << "[ ";
	for (int i = 0; i < (int)array.size(); i++) {
		array[i]->print_depth(depth + 1);
		if (i < (int)array.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << " ]";
}

void Json::print_object(int depth) const {
	const auto& object = get_object();
	std::cout << '{';
	if (object.size() > 0) {
		std::cout << std::endl;
	}
	for (const auto& it: object) {
		print_tabs(depth + 1);
		std::cout << '"' << it.first << "\": ";
		it.second->print_depth(depth + 1);
		std::cout << std::endl;
	}
	if (object.size() > 0) {
		print_tabs(depth);
	}
	std::cout << '}' << std::endl;
}

void Json::print_depth(int depth) const {
	switch (get_type()) {
		case Type::Number:
			std::cout << get_num();
			break;
		case Type::Boolean:
			std::cout << std::boolalpha << get_bool();
			break;
		case Type::String:
			std::cout << '"' << get_string() << '"';
			break;
		case Type::Array:
			print_tabs(depth);
			print_array(depth);
			break;
		case Type::Object:
			print_tabs(depth);
			print_object(depth);
			break;
		case Type::Null:
			std::cout << "null";
			break;
	}
}

}
