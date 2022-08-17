#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

template<class T>
int binary_search(std::vector<T> list, const T item) {
	size_t	low = 0;
	size_t	high = list.size();
	while (low < high) {
		size_t mid = ((low + high) / 2);
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
	if (argc != 3) {
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
	std::string find = argv[2];
	std::cout << "test " << binary_search(buffer, find) << std::endl;
}


//int main(void) {
//	std::vector<int> list;
//
//	for (size_t i = 0; i < 100; ++i) {
//		list.push_back((rand() % 200) + 1);
//	}
//	std::sort(list.begin(), list.end());
//	std::cout << "test " << binary_search(list, 10);
//}