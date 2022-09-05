#pragma once

#include <vector>

// https://www.techiedelight.com/inversion-count-array/

namespace grokking {

	namespace _detail_ {
	
	template <typename RandomIter>
	int merge(RandomIter begin1, RandomIter end1, RandomIter begin2, RandomIter end2) {
		// can prevent using a temp vector by making an auxiliary instead
		using T = typename RandomIter::value_type;
		RandomIter destination = begin1;
		std::vector<T> temp;
		size_t size = std::distance(begin1, end2);
		temp.reserve(size);
		int count = 0;
		while (begin1 != end1 || begin2 != end2) {
			if (begin1 == end1) {
				temp.push_back(*begin2++);
			} else if (begin2 == end2) {
				temp.push_back(*begin1++);
			} else if (*begin1 > *begin2) {
				temp.push_back(*begin2++);
				count += std::distance(begin1, end1);
			} else {
				temp.push_back(*begin1++);
			}
		}
		std::copy(temp.begin(), temp.end(), destination);
		return count;
	}

	}



/*
Given an array, find the total number of inversions of it.
If (i < j) and (A[i] > A[j]), then pair (i, j) is called an inversion of an array A. We need to count all such pairs in the array.
*/
template <typename RandomIter>
int inversion_count(RandomIter begin, RandomIter end) {

	// Simple O(N^2) solution
	// int count = 0;
	// for (auto i = begin; i != end; i++) {
	// 	for (auto j = std::next(i); j != end; j++) {
	// 		if (*i > *j) {
	// 			count++;
	// 		}
	// 	}
	// }
	// return count;

	// O(N log N) solution
	// Essentially merge sort but we count the inversions while merging
	auto distance = std::distance(begin, end);
	if (distance <= 1) {
		return 0;
	}
	RandomIter midpoint = begin + distance / 2;
	int count = 0;
	count += inversion_count(begin, midpoint);
	count += inversion_count(midpoint, end);
	count += _detail_::merge(begin, midpoint, midpoint, end);
	return count;
}

}
