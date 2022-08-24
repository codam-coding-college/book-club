#include "main.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_names(const std::string& filename, size_t max_names = ~0) {
	std::ifstream			 file(filename);
	std::vector<std::string> names;

	while (!file.eof() || !max_names--) {
		std::string line;
		getline(file, line);
		names.emplace_back(line);
	}
	std::sort(names.begin(), names.end());
	return (names);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <filename> <find>" << std::endl;
		return (EXIT_FAILURE);
	}
	const std::string			   filename = argv[1];
	const std::string			   find = argv[2];
	const std::vector<std::string> names = get_names(filename);

	std::cout << "Searching " << find << " in array of size " << names.size() << "..." << std::endl;

	const auto	  start = std::chrono::high_resolution_clock::now();
	const ssize_t i = bin_search_i(names, find);
	const auto	  end = std::chrono::high_resolution_clock::now();
	const auto	  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	if (i < 0)
		std::cout << "Not found" << std::endl;
	else
		std::cout << "Found at position " << i << " in " << duration.count() << " microseconds" << std::endl;

	return (EXIT_SUCCESS);
}
