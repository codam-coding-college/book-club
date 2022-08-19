//
// Created by Peer De bakker on 7/31/22.
//

#include <iostream>
#include "JsonParser.hpp"
#include <stdlib.h>

//int main(int argc, char **argv) {
//	int ret = EXIT_SUCCESS;
//	if (argc == 1) {
//		std::cerr << "Please enter a file to parse" << std::endl;
//		return (EXIT_FAILURE);
//	}
//
//	for (int i = 1; i < argc; i++) {
//		try {
//			JsonParser	parser(argv[i]);
//			auto node = parser.parse();
//			std::cerr << "\n\n" << *node << "\n";
//		} catch (std::exception& e) {
//			std::cerr << "exception: " << e.what() << "\n";
//			ret |= EXIT_FAILURE;
//		}
//	}
//	system("leaks json.out");
//	return (ret);
//}
int main() {
	try {
		JsonParser	parser("tests/jsons/object/simple.json");
		auto node = parser.parse();
		auto& obj = node->returnObject();
		fprintf(stderr, "obj has size %zu\n", obj.size());
		//		REQUIRE(obj.size() == 2);
		auto firstItem = obj.at("first");
		fprintf(stderr, "firstItem = %p\n", firstItem);
		std::cerr << "firstItem type = " << firstItem->getType() << "\n";

	} catch(std::exception& e) {
		// we shouldn't get here
		std::cerr << "exception: " << e.what() << "\n";
		return (1);
	}
	return (0);
}
