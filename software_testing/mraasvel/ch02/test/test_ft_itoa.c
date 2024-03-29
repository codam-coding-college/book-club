#include <criterion/criterion.h>
#include "libft.h"
#include "limits.h"

/*
 * partitions
	- N == 0
	- N > 0
	- N < 0
 * ft_itoa: Boundary cases
 ON-POINT: 0
 OFF-POINT: 1, -1
 INT_MAX
 INT_MIN

 IN/OUT: 120, -120
*/

// Point of this macro is that it's a parameterized test while still showing the expansion of the variables
// due to the making being processed pre-compile time by the preprocessor.
// It also stringifies the input integer using `#`
#define ITOA_TEST(x) \
	do { \
		char* result = ft_itoa(x); \
		cr_assert(strcmp(result, #x) == 0); \
		free(result); \
	} while(0);

// What the macro expands to
Test(libft_itoa, oneExample) {
	char* result = ft_itoa(1);
	cr_assert(strcmp(result, "1") == 0);
	free(result);
}

Test(libft_itoa, one) {
	ITOA_TEST(1);
}

Test(libft_itoa, negative_one) {
	ITOA_TEST(-1);
}

Test(libft_itoa, zero) {
	ITOA_TEST(0);
}

Test(libft_itoa, int_max) {
	ITOA_TEST(2147483647);
}

Test(libft_itoa, int_min) {
	ITOA_TEST(-2147483648);
}

Test(libft_itoa, in_value) {
	ITOA_TEST(120);
}

Test(libft_itoa, out_value) {
	ITOA_TEST(-120);
}
