#include "printer.hpp"
#include "option.hpp"
#include "variant.hpp"
#include <vector>
#include <iostream>

using variant::Json;

int main() {
	Json::ArrayType array {};
	array.emplace_back(std::unique_ptr<Json>(new Json {false}));
	array.emplace_back(std::unique_ptr<Json>(new Json {42}));
	array.emplace_back(std::unique_ptr<Json>(new Json {std::string { "rookworst" }}));

	Json::ObjectType nested_object {};
	nested_object["nested"] = std::unique_ptr<Json>(new Json {} );
	nested_object["rookworst"] = std::unique_ptr<Json>(new Json {std::string { "wauw" }});

	Json::ObjectType object {};
	object["a"] = std::unique_ptr<Json>(new Json {std::move(array)});
	object["b"] = std::unique_ptr<Json>(new Json {std::move(nested_object)});
	Json json { std::move(object) };
	json.print();
	return 0;
}
