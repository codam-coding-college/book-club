#pragma once

#include <functional>
#include <stack>

namespace grokking {

	namespace _detail_ {
		// make two subarrays, return the new pivot position
		template <typename RandomIter, typename Predicate>
		RandomIter partition(RandomIter start, RandomIter end, Predicate compare) {
			RandomIter pivot = std::prev(end);
			RandomIter pivot_position = start;
			while (start != pivot) {
				if (compare(*start, *pivot)) {
					std::swap(*start, *pivot_position);
					pivot_position++;
				}
				start++;
			}
			std::swap(*pivot, *pivot_position);
			return pivot_position;
		}
	}

template <typename RandomIter, typename Predicate>
void quicksort_iterative(RandomIter start, RandomIter end, Predicate compare) {

	using IterPair = std::pair<RandomIter, RandomIter>;
	using StackType = std::stack<IterPair>;

	StackType history;
	history.push(IterPair { start, end });
	while (!history.empty()) {
		IterPair top = history.top();
		history.pop();
		// make 2 subarrays, push to top of stack
		ptrdiff_t distance = std::distance(top.first, top.second);
		if (distance <= 1) {
			continue;
		}
		RandomIter pivot = _detail_::partition(top.first, top.second, compare);
		history.push(IterPair { top.first, pivot });
		history.push(IterPair { std::next(pivot), top.second });
	}
}

template <typename RandomIter>
void quicksort_iterative(RandomIter start, RandomIter end) {
	quicksort_iterative(start, end, std::less<decltype(*start)>());
}

}
