#include "exercise.hpp"
#include "quicksort.hpp"
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

int gcf(int x, int y) {
	if (y == 0) {
		return x;
	} else {
		return gcf(y, x % y);
	}
}

void test_sum() {
	std::array<int, 3> array { 2, 4, 6 };
	int sum = grokking::sum(array.begin(), array.end());
	assert(sum == 12);
}

void test_len() {
	auto v = { 1, 2, 3, 4 };
	assert(grokking::len(v.begin(), v.end()) == 4);
}

void test_max() {
	auto v = { 1, 2, 3, 4, -1, 42 };
	assert(grokking::max(v.begin(), v.end()) == 42);
}

void test_binary_search() {
	std::vector<int> v { 1, 2, 3, 4, 5 };
	auto find = grokking::binary_search(v.begin(), v.end(), 3);
	assert(*find == 3);
	auto fail = grokking::binary_search(v.begin(), v.end(), 42);
	assert(fail == v.end());
}

void test_quicksort() {
	std::vector<int> v { 5, 3, 1, 4, -5, 42 };
	grokking::quicksort(v.begin(), v.end());
	assert(std::is_sorted(v.begin(), v.end()));
}

int main() {
	test_sum();
	test_len();
	test_max();
	test_binary_search();
	test_quicksort();
	return 0;
}
