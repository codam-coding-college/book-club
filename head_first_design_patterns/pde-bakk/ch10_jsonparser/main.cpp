//
// Created by Peer De bakker on 7/31/22.
//

#include <iostream>
#include "JsonParser.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
	int ret = EXIT_SUCCESS;
	if (argc == 1) {
		std::cerr << "Please enter a file to parse" << std::endl;
		return (EXIT_FAILURE);
	}

	for (int i = 1; i < argc; i++) {
		try {
			JsonParser	parser(argv[i]);
			auto node = parser.parseJSON();
			if (node != nullptr)
				std::cerr << *node << "\n";
		} catch (std::exception& e) {
			std::cerr << "exception: " << e.what() << "\n";
			ret |= EXIT_FAILURE;
		}
	}
	return (ret);
}
