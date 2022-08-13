#include "../includes/binarySearch.hpp"

int main(void) {
	std::vector<int> list;

	for (size_t i = 0; i < 100; ++i) {
		list.push_back((rand() % 200) + 1);
	}
	std::sort(list.begin(), list.end());
	BinarySearch search;
	std::cout << "test " << search.binary_search(list, 10);
}