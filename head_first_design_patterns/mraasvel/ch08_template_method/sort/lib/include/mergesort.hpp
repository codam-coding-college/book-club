#pragma once

#include "sfinae.hpp"
#include <vector>

namespace sorting {

	namespace _detail_ {

	template <typename RandomAccessIt, typename Compare, typename Container>
	void merge(RandomAccessIt first, RandomAccessIt midpoint,
				RandomAccessIt last, Compare comp,
				Container& out) {
		std::copy(first, last, out.begin());
		auto left = out.begin();
		auto right = out.begin() + std::distance(first, midpoint);
		auto left_end = right;
		auto right_end = right + std::distance(midpoint, last);
		while (first != last) {
			if (right == right_end || (left != left_end && comp(*left, *right))) {
				*first++ = *left++;
			} else {
				*first++ = *right++;
			}
		}
	}

	/*
	Out is a container that has at least enough space for [first, last) */
	template <typename RandomAccessIt, typename Compare, typename Container>
	void merge_sort(RandomAccessIt first, RandomAccessIt last, Compare comp, Container& out) {
		if (std::distance(first, last) <= 1) {
			return;
		}
		RandomAccessIt midpoint = first + (last - first) / 2;
		merge_sort(first, midpoint, comp, out);
		merge_sort(midpoint, last, comp, out);
		merge(first, midpoint, last, comp, out);
	}

	}


/*
Log(n) calls, where n is distance(first, last)
Merge = O(n) where n is distance(first, last)
1 * n + 2 * n/2 + 4 * n/4 + ... + n * 1 = n * numcalls = n * log(n)
Runtime: O(n log n) */

template <typename RandomAccessIt, typename Compare,
	RequireRandomAccessIterator<RandomAccessIt> = true>
void merge_sort(RandomAccessIt first, RandomAccessIt last, Compare comp) {
	using TempContainerType = std::vector<typename std::remove_reference<decltype(*first)>::type>;
	TempContainerType out (std::distance(first, last));
	_detail_::merge_sort(first, last, comp, out);
}

template <typename RandomAccessIt>
void merge_sort(RandomAccessIt first, RandomAccessIt last) {
	merge_sort(first, last, std::less<decltype(*first)>());
}

}
