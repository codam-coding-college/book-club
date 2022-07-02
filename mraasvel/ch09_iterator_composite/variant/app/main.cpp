#include "printer.hpp"
#include "option.hpp"
#include "variant.hpp"
#include <vector>
#include <iostream>

using variant::Json;

int main() {
	Json::ArrayType array {};
	array.emplace_back(std::make_unique<Json>(false));
	array.emplace_back(std::make_unique<Json>(42));
	array.emplace_back(std::make_unique<Json>(std::string { "rookworst" }));

	Json::ObjectType nested_object {};
	nested_object["nested"] = std::make_unique<Json>();
	nested_object["rookworst"] = std::make_unique<Json>( std::string { "wauw" });

	Json::ObjectType object {};
	object["a"] = std::make_unique<Json>(std::move(array));
	object["b"] = std::make_unique<Json>(std::move(nested_object));
	Json json { std::move(object) };
	json.print();
	return 0;
}
