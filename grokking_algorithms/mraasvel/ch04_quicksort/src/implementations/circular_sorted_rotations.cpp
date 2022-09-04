#include <vector>
#include <algorithm>
#include <iostream>

// https://www.techiedelight.com/find-number-rotations-circularly-sorted-array/

namespace grokking {

	namespace _detail_ {
		// O(log n) answer -> binary search for min element
		int find_min_index(const std::vector<int>& v, int start, int end) {
			if (end - start <= 1) {
				return start;
			}
			int midpoint = (start + end) / 2;
			int index;
			if (v[end - 1] > v[midpoint]) {
				// go left
				index = find_min_index(v, start, midpoint);
			} else {
				// go right
				index = find_min_index(v, midpoint + 1, end);
			}
			if (v[index] < v[midpoint]) {
				return index;
			} else {
				return midpoint;
			}
		}
	}

// essentially a problem of finding the index of the minimum item
int num_rotations(const std::vector<int>& v) {
	// O(n) solution
	// auto position = std::min_element(v.begin(), v.end());
	// size_t answer = v.end() - position;

	// O(log n) solution
	size_t answer = v.size() - _detail_::find_min_index(v, 0, v.size());

	return answer == v.size() ? 0 : answer;
}

}
