#pragma once

#include <iterator>
#include <limits>

namespace grokking {

template <typename Iter>
int sum(Iter begin, Iter end) {
	if (begin == end) {
		return 0;
	} else {
		return *begin + sum(std::next(begin), end);
	}
}

template <typename Iter>
int len(Iter begin, Iter end) {
	if (begin == end) {
		return 0;
	} else {
		return 1 + len(std::next(begin), end);
	}
}

template <typename Iter>
int max(Iter begin, Iter end) {
	if (begin == end) {
		return std::numeric_limits<int>::min();
	} else {
		int x = *begin;
		int y = max(std::next(begin), end);
		return std::max(x, y);
	}
}

// return iterator to target in range (begin, end]
// otherwise return end
template <typename RandomIter, typename T>
RandomIter binary_search(RandomIter begin, RandomIter end, const T& target) {
	if (begin == end) {
		return end;
	}
	RandomIter midpoint = begin + (end - begin) / 2;
	if (*midpoint < target) {
		RandomIter new_begin = midpoint + 1;
		return grokking::binary_search(new_begin, end, target);
	} else if (target < *midpoint) {
		RandomIter new_end = midpoint;
		return grokking::binary_search(begin, new_end, target);
	} else {
		return midpoint;
	}
}

}
