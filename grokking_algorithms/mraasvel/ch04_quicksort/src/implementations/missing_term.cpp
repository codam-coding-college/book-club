#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

// https://www.techiedelight.com/find-missing-term-sequence-ologn-time/

namespace grokking {

int find_missing_term(const std::vector<int>& v) {
	if (v.size() < 2) {
		return -1;
	}
	int inc = (v[v.size() - 1] - v[0]) / v.size();
	int start = 0;
	int end = v.size();
	while (start <= end) {
		int midpoint = (start + end) / 2;
		if (midpoint + 1 < (int)v.size() && v[midpoint + 1] - v[midpoint] != inc) {
			return v[midpoint] + inc;
		} else if (midpoint > 0 && v[midpoint] - v[midpoint - 1] != inc) {
			return v[midpoint] - inc;
		}
		if (v[midpoint] - v[0] != midpoint * inc) {
			// left
			end = midpoint;
		} else {
			// right
			start = midpoint + 1;
		}
	}
	return -1;
}

void test_find_missing_term() {
	{
		std::vector<int> v { 5, 7, 9, 11, 15 };
		assert(find_missing_term(v) == 13);
	}
	{
		std::vector<int> v { 5, 9, 11, 13, 15 };
		assert(find_missing_term(v) == 7);
	}
	{
		std::vector<int> v { 5, 7, 9, 13, 15 };
		assert(find_missing_term(v) == 11);
	}
	{
		std::vector<int> v { 5, 7, 11, 13, 15 };
		assert(find_missing_term(v) == 9);
	}
	{
		std::vector<int> v { 5, 7, 11 };
		assert(find_missing_term(v) == 9);
	}
}

}
