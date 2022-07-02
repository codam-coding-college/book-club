#include "printer.hpp"
#include "option.hpp"
#include "variant.hpp"
#include <vector>
#include <iostream>

using variant::Json;

int main() {
	{
		Json::ArrayType array {};
		array.emplace_back(std::make_unique<Json>(false));
		array.emplace_back(std::make_unique<Json>(42));
		array.emplace_back(std::make_unique<Json>(std::string { "rookworst" }));
		Json::ObjectType object {};
		object["a"] = std::make_unique<Json>(std::move(array));
		Json::ObjectType object2 {};
		object2["nested"] = std::make_unique<Json>();
		object2["rookworst"] = std::make_unique<Json>( std::string { "wauw" });
		object["b"] = std::make_unique<Json>(std::move(object2));
		Json json { std::move(object) };
		json.print();
	}
	return 0;
}
