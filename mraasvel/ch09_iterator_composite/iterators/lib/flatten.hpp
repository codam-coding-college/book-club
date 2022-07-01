#pragma once

#include <memory>

namespace Maarten {

/*
Takes an iterator over iterators.
Yields items yielded by the nested iterator.
*/
template <typename Iterator>
class Flatten {
	private:
		using NestedIterator = typename Iterator::Item;

	public:
		using Item = typename NestedIterator::Item;

		Flatten(Iterator it)
		: it(it), current(nullptr) {}

		Item next() {
			if (!current || !current->has_next()) {
				load_next_iterator();
			}
			Item next = current->next();
			return next;
		}

		bool has_next() {
			return it.has_next() || (current && current->has_next());
		}
	
	private:
		void load_next_iterator() {
			current = nullptr;
			if (!it.has_next()) {
				return;
			}
			current = std::unique_ptr<NestedIterator> { new NestedIterator { it.next() } };
		}

	private:
		Iterator it;
		std::unique_ptr<NestedIterator> current;
};

}
