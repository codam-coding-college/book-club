#pragma once

#include <functional>

namespace Maarten {

template <typename Iterator>
class Filter {
	public:
		using Item = typename Iterator::Item;
		using FunctionType = std::function<bool(const Item&)>;

		Filter(Iterator it, FunctionType filter)
		: it(it), filter(filter), finished(false) {
			load_next();
		}

		Item next() {
			Item next = item;
			load_next();
			return next;
		}

		bool has_next() {
			return !finished;
		}

	private:
		// the reason we preemptively load the next entry is because otherwise we won't know if we're finished
		// a way to avoid this would be to not have a `has_next()` function and simply return a Null type from `next()`
		// that would require changing the iterator structure
		void load_next() {
			while (it.has_next()) {
				Item x = it.next();
				if (filter(x)) {
					item = x;
					return;
				}
			}
			finished = true;
		}

	private:
		Iterator it;
		FunctionType filter;
		Item item; // problem: item might not have default constructor
		bool finished;
};

}
