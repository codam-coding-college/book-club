#ifndef BINARYSEARCH
#define BINARYSEARCH

#include <iostream>
#include <vector>

class BinarySearch {
private:
	int _low;
	int _high;
	int 	_guest;
	int	_mid;

public:
	int binary_search(std::vector<int> list, const int item);
	BinarySearch();
	~BinarySearch();
};

#endif