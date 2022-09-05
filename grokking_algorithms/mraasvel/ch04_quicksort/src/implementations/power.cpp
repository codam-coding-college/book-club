#include <cinttypes>
#include <vector>
#include <functional>
#include <cassert>

// https://www.techiedelight.com/power-function-implementation-recursive-iterative/

namespace grokking {

// x^y

uint64_t pow_it(uint64_t x, uint64_t y) {
	uint64_t a = 1;
	while (y-- > 0) {
		a *= x;
	}
	return a;
}

uint64_t pow_rec(uint64_t x, uint64_t y) {
	if (y == 0) {
		return 1;
	}
	return x * pow_rec(x, y - 1);
}

// x^y = x^(y / 2) * x^(y / 2)
// still O(n) because of many branches
uint64_t pow_rec2(uint64_t x, uint64_t y) {
	if (y == 0) {
		return 1;
	}

	uint64_t result = pow_rec2(x, y / 2) * pow_rec2(x, y / 2);
	if (y % 2 == 1) {
		return result * x;
	} else {
		return result;
	}
}

// O(log n) because we can cache the result
uint64_t pow_rec_opt(uint64_t x, uint64_t y) {
	if (y == 0) {
		return 1;
	}
	uint64_t result = pow_rec_opt(x, y / 2);
	if (y % 2 == 1) {
		return result * result * x;
	} else {
		return result * result;
	}
}

	namespace _detail_ {

	void do_test_powers(std::function<uint64_t(uint64_t, uint64_t)> power) {
		assert(power(2, 0) == 1);
		assert(power(2, 1) == 2);
		assert(power(2, 2) == 4);
		assert(power(2, 3) == 8);
		assert(power(2, 4) == 16);
		assert(power(25, 2) == 625);
	}

	}

void test_powers() {
	_detail_::do_test_powers(pow_it);
	_detail_::do_test_powers(pow_rec);
	_detail_::do_test_powers(pow_rec2);
	_detail_::do_test_powers(pow_rec_opt);
}

}
