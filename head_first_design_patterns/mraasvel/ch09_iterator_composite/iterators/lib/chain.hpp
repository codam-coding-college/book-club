#pragma once

namespace Maarten {

/*
chain values from 2 iterators together
first yields all values of it1, then of it2
*/
template <typename It1, typename It2>
class Chain {
	public:
		using Item = typename It1::Item;

		Chain(It1 it1, It2 it2)
		: it1(it1), it2(it2) {}

		Item next() {
			if (it1.has_next()) {
				return it1.next();
			} else {
				return it2.next();
			}
		}

		bool has_next() {
			return it1.has_next() || it2.has_next();
		}

	private:
		It1 it1;
		It2 it2;
};

}
