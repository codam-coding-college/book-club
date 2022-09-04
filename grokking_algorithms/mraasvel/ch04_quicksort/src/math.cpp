#include "math.hpp"

namespace grokking {

uint64_t power(uint64_t x, uint64_t y) {
	uint64_t k = 1;
	while (y-- > 0) {
		k *= x;
	}
	return k;
}

/**
 * @brief 
 * 
 * @param k base number
 * @param n exponent
 * @return uint64_t sum of powers k^0 + k^1 + ... + k^n
 */
uint64_t consecutive_powers_sum(uint64_t k, uint64_t n) {
	// S = k^0 + k^1 + ... + k^n
	// multiply both sides by k:
	// S * k = k^1 + k^2 + ... + k^(n+1)
	// add k^0 to both sides to get S on the right hand side
	// S * k + k^0 = (k^0 + k^1 + ... + k^n) + k^(n+1)
	// S * k + k^0 = S + k^(n+1)
	// Solve for S
	// S * (k - 1) + k^0 = k^(n+1)
	// S = ( k^(n+1) - k^0 ) / (k - 1)
	return (power(k, n + 1) - 1) / (k - 1);
}

/*
Base case:
	r = a % b;
	r == 0. making b the GCD of (a, b)
Recursive case:
	r = a % b;
	r > 0, making r some other smaller multiple of GCD(a, b)
	GCD(b, r) will be a simplified version of the problem using smaller numbers.
*/
uint32_t gcd(uint32_t a, uint32_t b) {
	if (b == 0) {
		return a;
	}
	uint32_t r = a % b;
	return gcd(b, r);
}

}
