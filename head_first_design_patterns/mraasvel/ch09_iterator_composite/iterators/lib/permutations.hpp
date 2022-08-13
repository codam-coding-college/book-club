#pragma once

#include <functional>
#include <vector>
#include <algorithm>

namespace Maarten {

template <typename T, typename Compare = std::less<T>>
class Permutations {
	public:
		using Item = std::vector<T>;

		Permutations(Item table)
		: table(table), finished(false) {}

		Item next() {
			Item copy { table };
			next_permutation();
			return copy;
		}

		bool has_next() {
			return !finished;
		}

	private:
		void next_permutation() {
			int pos = find_start();
			if (pos < 0) {
				finished = true;
				return;
			}
			// reset the permutation after the index
			// swap index with next highest value
			std::reverse(table.begin() + pos + 1, table.end());
			auto it = std::upper_bound(table.begin() + pos + 1, table.end(), table[pos]);
			std::iter_swap(table.begin() + pos, it);
		}

		// 0 1 3 2 -> return index of 1 because [3, 2] is already the last permutation
		// while table[i] >= table[i + 1]
		int find_start() {
			for (int i = table.size() - 2; i >= 0; i--) {
				if (Compare()(table[i], table[i + 1])) {
					return i;
				}
			}
			return -1;
		}

	private:
		Item table;
		bool finished;
};

}
