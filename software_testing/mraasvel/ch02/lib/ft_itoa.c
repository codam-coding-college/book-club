#include <stdlib.h>

static int fill_chars(unsigned int n, int index, char* dest) {
	if (n >= 10) {
		index = fill_chars(n / 10, index, dest);
	}
	dest[index] = (n % 10) + '0';
	return index + 1;
}

char* ft_itoa(int n) {
	// INT is max 4 bytes, meaning the largest possible string is 11 chars
	char* result = malloc(12 * sizeof(char));
	if (!result) {
		return NULL;
	}
	int index = 0;
	unsigned int x = n;
	if (n < 0) {
		result[0] = '-';
		index = 1;
		x = -n;
	}
	index = fill_chars(x, index, result);
	result[index] = '\0';
	return result;
}
