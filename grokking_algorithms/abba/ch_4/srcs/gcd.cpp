#include <iostream>
#include <vector>

/*
 * If A = 0 then GCD(A,B)=B, since the GCD(0,B)=B, and we can stop.
 * If B = 0 then GCD(A,B)=A, since the GCD(A,0)=A, and we can stop.
 * Write A in quotient remainder form (A = B⋅Q + R)
 * Find GCD(B,R) using the Euclidean Algorithm since GCD(A,B) = GCD(B,R)
 */

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int lcm(int a, int b) {
	if (b == 0) {
		return a;
	}
	int value_gcd = gcd(a, b);
	return (a * b) / value_gcd;
}

//testing
#define assertm(exp, msg) assert(((void)msg, exp))

int main1(void) {
	std::cout << "---------testing gcd----------" << std::endl;
	int a = gcd(270, 192);
	assertm((a == 6), "expect expected");
	std::cout << "checkpoint #1\n";
	std::cout << a << std::endl;
	std::cout << "---------testing lcm----------" << std::endl;
	{
		int b = lcm(8, 10);
		assertm((b == 40), "expect expected");
		std::cout << "checkpoint #1\n";
		std::cout << b << std::endl;
	}
	{
		int b = lcm(8, 12);
		assertm((b == 24), "expect expected");
		std::cout << "checkpoint #1\n";
		std::cout << b << std::endl;
	}
	{
		int b = lcm(24, 36);
//		assertm((b == 24), "expect expected");
		std::cout << "checkpoint #1\n";
		std::cout << b << std::endl;
	}
	return 0;
}


int getTotalX(std::vector<int> a, std::vector<int> b) {
	int lcm_value = *a.begin();
	int gcd_value = *b.begin();
	for (auto x: a) {
		lcm_value = lcm(lcm_value, x);
	}
	for (auto x: b) {
		gcd_value = gcd(gcd_value, x);
	}
	int result = 0;
	while (1) {
		for (auto x: a) {
			if (gcd_value % x == 0 && x <= gcd_value) {
				result++;
			} else {
				return result;
			}
		}
		for (auto x: b) {
			if (gcd_value % x == 0 && x <= gcd_value) {
				result++;
			} else {
				return result;
			}
		}
		return result;
	}
	return {};
}

int main(void) {
	std::vector<int> a{2, 4};
	std::vector<int> b{16, 32, 96};
	std::cout << getTotalX(a, b);
	return 0;
}