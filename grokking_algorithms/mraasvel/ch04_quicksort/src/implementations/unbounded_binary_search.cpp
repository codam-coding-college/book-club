#include <functional>
#include <iostream>

namespace grokking {

	namespace _detail_ {

	int bounded_binary_search(int start, int end, std::function<int(int)> f) {
		std::cout << start << ", " << end << '\n';
		int lowest = end;
		while (start < end) {
			int midpoint = (start + end) / 2;
			if (f(midpoint) > 0) {
				lowest = midpoint;
				end = midpoint;
			} else {
				start = midpoint + 1;
			}
		}
		return end;
	}

	}

// precondition: f is monotonically increasing
// overflow not handled
// returns first x for which f(x) >= 0
int unbounded_binary_search(std::function<int(int)> f) {
	if (f(0) >= 0) {
		return 0;
	}
	// log(x) search for lowest power of 2 for which f(x) is positive
	// which will serve as our upper bound
	// this is apparently called an exponential search
	int x = 1;
	while (f(x) < 0) {
		x *= 2;
	}
	// previous power of 2 will serve as our lower bound
	int prev = x / 2;
	return _detail_::bounded_binary_search(prev, x, f);
}

}
