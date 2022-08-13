#pragma once

#include "range_iterator.hpp"
#include <cstddef>

namespace Maarten {

/*
Simply returns false after returning n items
*/
template <typename Iterator>
class Take {
	public:
		using Item = typename Iterator::Item;

		Take(std::size_t n, Iterator it)
		: it(it), range(0, n) {}

		Item next() {
			range.next();
			return it.next();
		}

		bool has_next() {
			return range.has_next() && it.has_next();
		}

	private:
		Iterator it;
		RangeIterator<size_t> range;
};

}
