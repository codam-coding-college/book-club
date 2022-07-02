#include "printer.hpp"
#include "option.hpp"
#include "variant.hpp"
#include <vector>
#include <iostream>

using variant::Option;
using variant::Json;
using util::Printer;

union UnionData {
	UnionData(int n): n(n) {}
	UnionData(Printer p): p(p) {}
	~UnionData() {
		p.~Printer();
	}
	Printer p;
	int n;
	std::string s;
};

Option<Printer> f(int n) {
	if (n % 2 == 0) {
		return Option<Printer> { Printer {} };
	}
	return Option<Printer> {};
}

int main() {
	std::string s { "String" };
	auto json = Json {
		Json::ObjectType {
			std::make_pair(std::string { "String" }, new Json { s }),
			std::make_pair(std::string { "Value" }, new Json { 42 }),
			std::make_pair(std::string { "Array" }, new Json { Json::ArrayType {
				new Json { 1 }, new Json { 2 },
			} }),
		},
	};
	auto object = json.get_object();
	auto num = object["Value"]->get_num();
	assert(num == 42);
	auto x = object["Array"]->get_array()[0]->get_num();
	assert(x == 1);
	return 0;
}
