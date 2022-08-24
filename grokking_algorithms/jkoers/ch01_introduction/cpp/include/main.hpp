#pragma once
#include <algorithm>
#include <cstddef>
#include <optional>
#include <vector>

template <typename T>
ssize_t bin_search_i(const std::vector<T>& v, const T& x) {
	ssize_t low = 0;
	ssize_t high = v.size() - 1;

	while (low <= high) {
		const ssize_t mid = (low + high) / 2;
		if (x == v[mid]) // TODO: allow for custom comparator
			return mid;
		else if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

// template <typename T>
// std::optional<const & T> bin_search(const std::vector<T>& v, const T& x) {
// 	const ssize_t idx = bin_search_i(x);
// 	return idx < 0 ? {} : std::make_optional(v[idx]);
// }
