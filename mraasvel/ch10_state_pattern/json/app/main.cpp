#include "json.hpp"
#include "json_parse.hpp"
#include <iostream>
#include <fstream>

int main() {
	std::ifstream ifs { "./examples/example.json" };
	auto json = json_parse::parse(ifs);
	return 0;
}
