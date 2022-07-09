#include "json.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>

using json_parse::Parser;

int main() {
	std::ifstream ifs { "./examples/example.json" };
	Parser file_parser { ifs };
	file_parser.parse();
	return 0;
}
