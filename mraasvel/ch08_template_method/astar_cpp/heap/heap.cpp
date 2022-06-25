#include "heap.hpp"

namespace DSA {
	namespace HeapDetail {

	std::size_t parentIndex(std::size_t index) {
		return (index - 1) / 2;
	}

	std::size_t leftChildIndex(std::size_t index) {
		return index * 2 + 1;
	}

	std::size_t rightChildIndex(std::size_t index) {
		return index * 2 + 2;
	}

	}
}
