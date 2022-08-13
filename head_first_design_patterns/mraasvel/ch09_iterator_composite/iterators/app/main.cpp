#include "take.hpp"
#include "filter.hpp"
#include "map.hpp"
#include "range_iterator.hpp"
#include "consumers.hpp"
#include <iostream>

using Maarten::Take;
using Maarten::Filter;
using Maarten::Map;
using Maarten::RangeIterator;

using RangeType = RangeIterator<int>;
using FilterType = Filter<RangeType>;
using MapType = Map<FilterType, int>;
using TakeType = Take<MapType>;

int main() {
	TakeType take { // yields [4, 8, 12, 16, 20]
		5,
		MapType { // yields [ 4, 8, 12, 16, ... ]
			FilterType { // yields [2, 4, 6, 8, 10, ...]
				RangeType { 1 }, // yields [1, 2, 3, 4, ...]
				[] (const int& x) {
					return x % 2 == 0;
				}
			},
			[] (int n) {
				return n * 2;
			}
		}
	};

	int result = sum(take);
	int expected = 4 + 8 + 12 + 16 + 20;
	std::cout << "Result: " << result << std::endl;
	std::cout << "Expected: " << expected << std::endl;
	return 0;
}
