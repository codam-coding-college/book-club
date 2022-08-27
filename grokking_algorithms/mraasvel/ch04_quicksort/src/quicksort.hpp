#include <iterator>
#include <vector>

namespace grokking {

template <typename T>
struct less {
	using result_type = bool;

	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};

// in place swapping instead of making seperate arrays
template <typename RandomIter, typename Predicate>
RandomIter partition(RandomIter begin, RandomIter end, RandomIter pivot, Predicate comp) {
	std::swap(*begin, *pivot);
	pivot = begin;
	begin = std::next(begin);
	end = std::prev(end);
	while (begin != end) {
		if (comp(*begin, *pivot)) {
			begin++;
		} else {
			std::swap(*begin, *end);
			end--;
		}
	}
	RandomIter pivot_position;
	if (comp(*begin, *pivot)) {
		pivot_position = begin;
	} else {
		pivot_position = std::prev(begin);
	}
	std::swap(*pivot, *pivot_position);
	return begin;
}

template <typename RandomIter, typename Predicate>
void quicksort(RandomIter begin, RandomIter end, Predicate comp) {
	ptrdiff_t distance = std::distance(begin, end);
	if (distance <= 1) {
		return;
	}

	// take the midpoint as pivot
	RandomIter pivot = begin + (end - begin) / 2;
	pivot = partition(begin, end, pivot, comp);

	// if the array is partitioned perfectly (aka we have the perfect pivot)
	// then the depth will be Log2(n) and the work done on each level is approximately 2N
	// Making the algorithm O(n log n)
	quicksort(begin, pivot, comp);
	quicksort(std::next(pivot), end, comp);
}

template <typename RandomIter>
void quicksort(RandomIter begin, RandomIter end) {
	quicksort(begin, end, std::less<decltype(*begin)>());
}

}
