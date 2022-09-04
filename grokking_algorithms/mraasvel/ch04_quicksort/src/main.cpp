#include <iostream>
#include "exercise.hpp"
#include "quicksort.hpp"
#include "implementations/amalgamated.hpp"
#include "math.hpp"
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

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

void test_quicksort_it() {
	std::vector<int> v { 5, 3, 1, 4, -5, 42 };
	grokking::quicksort_iterative(v.begin(), v.end());
	assert(std::is_sorted(v.begin(), v.end()));
}

void test_math() {
	assert(grokking::power(2, 4) == 16);
	assert(grokking::gcd(2 * 2 * 5 * 7 * 13, 2 * 5 * 13) == 2 * 5 * 13);
	assert(grokking::consecutive_powers_sum(2, 5) == 63);
	assert(grokking::consecutive_powers_sum(3, 3) == 40);
}

void test_inversion_count_array() {
	std::vector<int> v { 42, 5, 6, 56, 1 };
	int expected = 6;
	assert(grokking::inversion_count(v.begin(), v.end()) == expected);
}

void test_num_rotations() {
	{
		std::vector<int> v { 8, 9, 10, 2, 5, 6 };
		assert(grokking::num_rotations(v) == 3);
	}
	{
		std::vector<int> v { 2, 5, 6, 8, 9, 10 };
		assert(grokking::num_rotations(v) == 0);
	}
	{
		std::vector<int> v { 5, 6, 8, 9, 10, 2 };
		assert(grokking::num_rotations(v) == 1);
	}

}

int main() {
	test_sum();
	test_len();
	test_max();
	test_binary_search();
	test_quicksort();
	test_quicksort_it();
	test_inversion_count_array();
	test_num_rotations();
	test_math();
	return 0;
}
