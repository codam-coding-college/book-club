//
// Created by Peer De bakker on 7/31/22.
//

#include <iostream>
#include "JsonParser.hpp"

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cerr << "Please enter a file to parse" << std::endl;
		return (EXIT_FAILURE);
	}
	for (int i = 1; i < argc; i++) {
		try {
			JsonParser	parser(argv[i]);
			auto node = parser.parse();
			std::cerr << *node << "\n";
		} catch (std::exception& e) {
			std::cerr << "exception: " << e.what() << "\n";
		}
	}
}
