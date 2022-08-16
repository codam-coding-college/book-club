#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#pragma execution_character_set("utf-8")

template<typename T>
ssize_t	binarySearch(const std::vector<T>& arr, const T& x) {
	size_t	low = 0,
			high = arr.size() - 1;
	size_t	i = 0;

	while (low <= high) {
		i++;
		size_t mid = (low + high) / 2;
		if (x == arr[mid]) {
			return (static_cast<ssize_t>(mid));
		}
		else if (x < arr[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (-1);
}

std::vector<std::string>	get_names(const std::string& filename, size_t max_names = 0) {
	std::ifstream file(filename);
	std::vector<std::string>	names;
	size_t i = 0;

	while (!file.eof() || i < max_names) {
		std::string line;
		getline(file, line);
		names.emplace_back(line);
		++i;
	}
	std::sort(names.begin(), names.end());
	return (names);
}

int main(int argc, char **argv) {
	std::string	filename = argv[1];
	std::string find = "Nicholas";
	if (argc == 1) {
		std::cerr << "Please gib file\n";
		return (EXIT_FAILURE);
	}
	if (argv[2]) {
		find = argv[2];
	}
	auto names = get_names(filename);
	std::cout << "Let's attempt to find '" << find << "' in our array of size " << names.size() << ".\n";
	ssize_t find_idx = binarySearch<std::string>(names, find);
	if (find_idx == -1)
		std::cout << "We failed to find them" << "😔" << ".\n";
	else
		std::cout << "We found them at position " << find_idx << "! " "😊" << "\n";
	return (EXIT_SUCCESS);
}
