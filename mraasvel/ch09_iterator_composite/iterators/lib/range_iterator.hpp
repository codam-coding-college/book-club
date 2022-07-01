#pragma once

#include <cassert>

namespace Maarten {

template <typename T>
class RangeIterator {
	public:
		using Item = T;
	
		RangeIterator(Item start, Item end)
		: start(start), end(end), unbounded(false) {
			assert(start <= end);
		}

		RangeIterator(Item start)
		: start(start), unbounded(true) {}

		Item next() {
			return start++;
		}

		bool has_next() const {
			return unbounded || start != end;
		}

	private:
		Item start;
		Item end;
		bool unbounded;
};

}
