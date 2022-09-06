#pragma once

#include <vector>
#include <ctgmath>

// https://www.techiedelight.com/introsort-algorithm/

namespace grokking {

	namespace _detail_ {

	static size_t heap_left_child(size_t parent) {
		return parent * 2 + 1;
	}

	static size_t heap_right_child(size_t parent) {
		return parent * 2 + 2;
	}

	// begin_index is the index of begin in the total array
	template <typename RandomIter>
	static void heapify_down(RandomIter begin, RandomIter end, size_t begin_index = 0) {
		size_t size = end - begin;
		size_t i = 0;
		while (i < size) {
			auto left_index = heap_left_child(i + begin_index);
			auto right_index = heap_right_child(i + begin_index);
			if (left_index >= size) {
				break;
			}
			// swap with maximum child element: we need to be careful to not go out of bounds
			size_t max_child_index;
			if (right_index < size && begin[right_index] > begin[left_index]) {
				max_child_index = right_index;
			} else {
				max_child_index = left_index;
			}
			if (begin[max_child_index] > begin[i]) {
				std::swap(begin[i], begin[max_child_index]);
				i = max_child_index;
			} else {
				break;
			}
		}

	}

	template <typename RandomIter>
	static void make_heap(RandomIter begin, RandomIter end) {
		auto distance = std::distance(begin, end);
		if (distance <= 1) {
			return;
		}
		RandomIter pos = begin + (end - begin) / 2;
		if (distance % 2 == 1) {
			pos += 1;
		}
		while (pos > begin) {
			pos--;
			heapify_down(pos, end, pos - begin);
		}
	}

	template <typename RandomIter>
	static RandomIter partition(RandomIter pivot, RandomIter end) {
		RandomIter pivot_position = pivot;
		for (auto it = std::next(pivot); it != end; it++) {
			if (*it < *pivot) {
				pivot_position++;
				std::swap(*it, *pivot_position);
			}
		}
		std::swap(*pivot, *pivot_position);
		return pivot_position;
	}

	}

template <typename RandomIter>
void heapsort(RandomIter begin, RandomIter end) {
	_detail_::make_heap(begin, end);
	end--;
	while (end != begin) {
		std::swap(*begin, *end--);
		_detail_::heapify_down(begin, end);
	}
}

template <typename RandomIter>
void insertionsort(RandomIter begin, RandomIter end) {
	// O(n^2)
	for (auto it = begin; it != end; it++) {
		auto inner = std::next(it);
		auto value = *inner;
		// move all larger elements one space forward
		while (inner > begin && value < *std::prev(inner)) {
			*inner = *std::prev(inner);
			inner--;
		}
		*inner = value;
	}
}

	namespace _detail_ {

	template <typename RandomIter>
	static void do_introsort(RandomIter begin, RandomIter end, int max_depth) {
		auto distance = std::distance(begin, end);
		if (distance <= 1) {
			return;
		} else if (distance <= 16) {
			// the constant factor of insertionsort is lower so it will be more efficient on smaller sizes
			return grokking::insertionsort(begin, end);
		} else if (max_depth == 0) {
			// the max depth will only be entered if the pivot choices were very inefficient
			// heapsort will guarantee a O(n log n) sort in this case
			return grokking::heapsort(begin, end);
		}
		// quicksort logic
		RandomIter pivot = partition(begin, end);
		do_introsort(begin, pivot, max_depth - 1);
		do_introsort(std::next(pivot), end, max_depth - 1);
	}

	}

template <typename RandomIter>
void introsort(RandomIter begin, RandomIter end) {
	int max_depth = std::log(std::distance(begin, end)) * 2;
	_detail_::do_introsort(begin, end, max_depth);
}

}
