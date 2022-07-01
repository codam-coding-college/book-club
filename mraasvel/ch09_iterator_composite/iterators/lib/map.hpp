#pragma once

#include <functional>

namespace Maarten {

template <typename Iterator, typename Output>
class Map {
	private:
		using InputType = typename Iterator::Item;

	public:
		using Item = Output;
		using FunctionType = std::function<Item(InputType)>;

	public:
		Map(Iterator it, FunctionType f)
		: it(it), f(f) {}

		Item next() {
			return f(it.next());
		}

		bool has_next() {
			return it.has_next();
		}

	private:
		Iterator it;
		FunctionType f;
};

}
