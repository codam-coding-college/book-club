#include "json.hpp"
#include <cassert>
#include <iostream>
#include <cstring>
#include <iomanip>

namespace json {

std::ostream& operator<<(std::ostream& out, const Type& rhs) {
	switch (rhs) {
		case Type::Number:
			out << "Number";
			break;
		case Type::Boolean:
			out << "Boolean";
			break;
		case Type::String:
			out << "String";
			break;
		case Type::Array:
			out << "Array";
			break;
		case Type::Object:
			out << "Object";
			break;
		case Type::Null:
			out << "Null";
			break;
	}
	return out;
}

Json::JsonData::JsonData(double d): d(d) {}
Json::JsonData::JsonData(bool b): b(b) {}
Json::JsonData::JsonData(const std::string& str): str(str) {}
Json::JsonData::JsonData(std::string&& str): str(std::move(str)) {}
Json::JsonData::JsonData(std::vector<std::unique_ptr<Json>>&& array)
: array(std::move(array)) {}
Json::JsonData::JsonData(std::unordered_map<std::string, std::unique_ptr<Json>>&& object)
: object(std::move(object)) {}
Json::JsonData::~JsonData() {}

// not even sure if this will work, but it is never called
// the only reason it exists is to be compatible with option move copy constructor
Json::JsonData& Json::JsonData::operator=(JsonData&& rhs) {
	std::memmove((void*)this, (void*)&rhs, sizeof(JsonData));
	return *this;
}

Json::Json(): type(Type::Null) {}
Json::Json(int n): data(static_cast<double>(n)), type(Type::Number) {}
Json::Json(double d): data(d), type(Type::Number) {}
Json::Json(bool b): data(b), type(Type::Boolean) {}
Json::Json(const std::string& s): data(s), type(Type::String) {}
Json::Json(std::string&& s): data(std::move(s)), type(Type::String) {}
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

Json::Json(Json&& rhs): type(rhs.type) {
	switch (type) {
		case Type::Number:
			data = std::move(rhs.get_num());
			break;
		case Type::Boolean:
			data = std::move(rhs.get_bool());
			break;
		case Type::String:
			data = std::move(rhs.data.value().str);
			break;
		case Type::Array:
			data = std::move(rhs.data.value().array);
			break;
		case Type::Object:
			data = std::move(rhs.data.value().object);
			break;
		case Type::Null:
			break;
	}
	rhs.type = Type::Null;
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

double Json::get_num() const {
	assert(type == Type::Number);
	return data.value().d;
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

void Json::print(std::ostream& out, bool readable) const {
	print_depth(out, 0, readable);
	if (readable) {
		out << std::endl;
	}
}

static void print_tabs(std::ostream& out, int depth) {
	if (depth == 0) {
		return;
	}
	out << std::setw(depth * 4) << ' ';
}

void Json::print_array(std::ostream& out, int depth, bool readable) const {
	const auto& array = get_array();
	if (array.empty()) {
		out << "[]";
		return;
	}
	out << "[";
	if (readable) {
		out << '\n';
	}
	for (int i = 0; i < (int)array.size(); i++) {
		if (readable) {
			print_tabs(out, depth + 1);
		}
		array[i]->print_depth(out, depth + 1, readable);
		if (i < (int)array.size() - 1) {
			out << ",";
			if (readable) {
				out << '\n';
			}
		}
	}
	if (readable) {
		out << '\n';
		print_tabs(out, depth);
	}
	out << "]";
}

void Json::print_object(std::ostream& out, int depth, bool readable) const {
	const auto& object = get_object();
	if (object.empty()) {
		out << "{}";
		return;
	}
	out << "{";
	if (readable) {
		out << '\n';
	}
	int i = 0;
	for (const auto& it: object) {
		if (readable) {
			print_tabs(out, depth + 1);
		}
		out << '"' << it.first << "\":";
		if (readable) {
			out << ' ';
		}
		it.second->print_depth(out, depth + 1, readable);
		if (i++ < (int)object.size() - 1) {
			out << ',';
			if (readable) {
				out << '\n';
			}
		}
	}
	if (readable) {
		out << '\n';
		print_tabs(out, depth);
	}
	out << '}';
}

static char get_escaped_char(char c) {
	switch (c) {
		case '"':
		case '\\':
		case '/':
			return c;
		case '\b':
			return 'b';
		case '\f':
			return 'f';
		case '\n':
			return 'n';
		case '\r':
			return 'r';
		case '\t':
			return 't';
	}
	return -1;
}

void Json::print_string(std::ostream& out) const {
	out << '"';
	const std::string& str = get_string();
	for (char c: str) {
		if (c == '"' || c == '\\' || c == '/' || !isprint(c)) {
			out << '\\';
			char ch = get_escaped_char(c);
			if (ch != -1) {
				out << ch;
			}
		} else {
			out << c;
		}
	}
	out << '"';
}

void Json::print_depth(std::ostream& out, int depth, bool readable) const {
	switch (get_type()) {
		case Type::Number:
			out << get_num();
			break;
		case Type::Boolean:
			out << std::boolalpha << get_bool();
			break;
		case Type::String:
			print_string(out);
			break;
		case Type::Array:
			print_array(out, depth, readable);
			break;
		case Type::Object:
			print_object(out, depth, readable);
			break;
		case Type::Null:
			out << "null";
			break;
	}
}

static bool equal_json_array(const Json::ArrayType& a, const Json::ArrayType& b) {
	if (a.size() != b.size()) {
		return false;
	}
	for (size_t i = 0; i < a.size(); i++) {
		if (*a[i] != *b[i]) {
			return false;
		}
	}
	return true;
}

static bool equal_json_object(const Json::ObjectType& a, const Json::ObjectType& b) {
	if (a.size() != b.size()) {
		return false;
	}
	for (const auto& pair: a) {
		auto it = b.find(pair.first);
		if (it == b.end()) {
			return false;
		}
		if (*pair.second != *it->second) {
			return false;
		}
	}
	return true;
}

bool operator==(const Json& a, const Json& b) {
	if (a.get_type() != b.get_type()) {
		return false;
	}
	switch (a.get_type()) {
		case Type::Number:
			return a.get_num() == b.get_num();
		case Type::Boolean:
			return a.get_bool() == b.get_bool();
		case Type::String:
			return a.get_string() == b.get_string();
		case Type::Array:
			return equal_json_array(a.get_array(), b.get_array());
		case Type::Object:
			return equal_json_object(a.get_object(), b.get_object());
		case Type::Null:
			return true;
	}
	return false;
}

bool operator!=(const Json& a, const Json& b) {
	return !(a == b);
}

}
