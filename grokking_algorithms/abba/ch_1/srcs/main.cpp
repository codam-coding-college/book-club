#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

template<class T>
int binary_search(const std::vector<T>& list, const T& item) {
	size_t	low = 0;
	size_t	high = list.size() - 1;
	while (low <= high) {
		int mid = ((low + high) / 2);
		T guest = list.at(mid);
		if (guest == item) {
			return mid;
		} else if (guest > item) {
				high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "usage: <program> <file> <value to check>\n";
		return 1;
	}
	std::vector<std::string> buffer;
	std::ifstream is(argv[1]);
	if (is.fail()) {
		std::cout << "invalid file\n";
		return 1;
	}
	std::string line;
	while (!is.fail())
	{
		getline(is, line);
		if (line.size() > 0) {
			buffer.push_back(line);
		}
	}
	std::sort(buffer.begin(), buffer.end());
	std::string find;
	while (1) {
		std::cout << "enter a name or type stop to end the program\n";
		std::cout << "command: ";
		std::cin >> find;
		if (find == "stop") {
			exit(0);
		}
		std::cout << "test " << binary_search(buffer, find) << std::endl;
	}
}
