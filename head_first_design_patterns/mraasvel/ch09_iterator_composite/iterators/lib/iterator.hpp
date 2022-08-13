#pragma once

/*
iterator specification:
I don't put it in an abstract class because I want to use templates instead of inheritance

type Item; // type of the value that the iterator yields
Item next(); // next function, contract: only call if `has_next()` returns TRUE
bool has_next(); // check function
*/

#include "range_iterator.hpp"

namespace Maarten {

// STL iterator wrapper for my own adapters
template <typename Iterator>
class Maarterator {
	public:
		using Item = typename Iterator::value_type;

		Maarterator(Iterator start, Iterator end)
		: range(start, end) {}

		Item next() {
			return *range.next();
		}

		bool has_next() {
			return range.has_next();
		}

	private:
		RangeIterator<Iterator> range;
};

}
