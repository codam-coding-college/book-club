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
	{
		Json { Json::ObjectType {
			std::make_pair("key", new Json { Json::ArrayType { new Json { false } } }),
		} };
	}
	return 0;
}
