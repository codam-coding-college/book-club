#include "../includes/binarySearch.hpp"

int BinarySearch::binary_search(std::vector<int> list, const int item) {
	_low = 0;
	_high = list.size();
	while (_low < _high) {
		_mid = ((_low + _high) / 2);
		_guest = list.at(_mid);
		if (_guest == item) {
			return _mid;
		} else if (_guest > item) {
			_high = _mid - 1;
		} else {
			_low = _mid + 1;
		}
	}
	return -1;
}

BinarySearch::BinarySearch() {

}

BinarySearch::~BinarySearch() {

}
