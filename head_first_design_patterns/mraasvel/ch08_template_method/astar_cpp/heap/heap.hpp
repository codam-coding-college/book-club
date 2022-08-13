#ifndef HEAP_HPP
#define HEAP_HPP

#include "sfinae.hpp"
#include <vector>
#include <functional>
#include <algorithm>

namespace DSA {

	namespace HeapDetail {

	std::size_t parentIndex(std::size_t index);
	std::size_t leftChildIndex(std::size_t index);
	std::size_t rightChildIndex(std::size_t index);

	template <typename RandomIt, typename Compare>
	void heapifyDown(RandomIt first, RandomIt last, Compare comp, std::size_t index) {
		std::size_t size = std::distance(first, last) - 1;
		while (index < size) {
			std::size_t left = HeapDetail::leftChildIndex(index);
			std::size_t right = HeapDetail::rightChildIndex(index);
			// if index is a leaf or greater than all it's children
			if (left >= size ||
					(comp(first[left], first[index])
						&& (right >= size || comp(first[right], first[index])))) {
				break;
			}
			// if left is greater than right or only left exists, swap left
			if (right >= size || comp(first[right], first[left])) {
				std::swap(first[index], first[left]);
				index = left;
			} else if (right < size) {
				std::swap(first[index], first[right]);
				index = right;
			}
		}
	}

	}

template <class RandomIt, class Compare,
	RequireRandomAccessIterator<RandomIt> = true>
void make_heap(RandomIt first, RandomIt last, Compare comp) {
	if (first == last) {
		return;
	}
	std::size_t size = std::distance(first, last) - 1;
	std::size_t index = HeapDetail::parentIndex(size);
	while (index <= size) {
		HeapDetail::heapifyDown(first, last, comp, index);
		--index;
	}
}

template <class RandomIt>
void make_heap(RandomIt first, RandomIt last) {
	make_heap(first, last, std::less<decltype(*first)>());
}

template <class RandomIt, class Compare,
	RequireRandomAccessIterator<RandomIt> = true>
void push_heap(RandomIt first, RandomIt last, Compare comp) {
	std::size_t index = std::distance(first, last) - 1;
	std::size_t parent = HeapDetail::parentIndex(index);
	while (index != 0 && comp(first[parent], first[index])) {
		std::swap(first[index], first[parent]);
		index = parent;
		parent = HeapDetail::parentIndex(index);
	}
}

template <class RandomIt>
void push_heap(RandomIt first, RandomIt last) {
	push_heap(first, last, std::less<decltype(*first)>());
}

template <class RandomIt, class Compare,
	RequireRandomAccessIterator<RandomIt> = true>
void pop_heap(RandomIt first, RandomIt last, Compare comp) {
	std::swap(*first, *(last - 1));
	HeapDetail::heapifyDown(first, last, comp, 0);
}

template <class RandomIt>
void pop_heap(RandomIt first, RandomIt last) {
	pop_heap(first, last, std::less<decltype(*first)>());
}

template <
	typename T,
	typename Container = std::vector<T>,
	typename Compare = std::less<typename Container::value_type>
>
class Heap {
public:
	static_assert(std::is_same<T, typename Container::value_type>::value, "invalid container");
public:
	using container_type	= Container;
	using value_compare		= Compare;
	using value_type		= typename Container::value_type;
	using size_type			= typename Container::size_type;
	using reference			= typename Container::reference;
	using const_reference	= typename Container::const_reference;

	using iterator			= typename Container::iterator;
	using const_iterator	= typename Container::const_iterator;

public:
	Heap()
	: Heap(Compare(), Container()) {}
	explicit Heap(const Compare& compare)
	: Heap(compare, Container()) {}

	Heap(const Compare& compare, const Container& cont)
	: comp(compare), c(cont) {
		makeHeap();
	}

	Heap(const Compare& compare,Container&& cont)
	: comp(compare), c(std::move(cont)) {
		makeHeap();
	}

	Heap(const Heap& other) = default;
	Heap(Heap&& other) = default;

	template <class InputIt,
		RequireInputIterator<InputIt> = true>
	Heap(InputIt first, InputIt last,
			const Compare& compare = Compare())
	: comp(compare), c(first, last) {
		makeHeap();
	}

	template <class InputIt,
		RequireInputIterator<InputIt> = true>
	Heap(InputIt first, InputIt last,
		const Compare& compare, const Container& cont)
	: comp(compare), c(cont) {
		c.insert(c.end(), first, last);
		makeHeap();
	}

	template <class InputIt,
		RequireInputIterator<InputIt> = true>
	Heap(InputIt first, InputIt last,
		const Compare& compare, Container&& cont)
	: comp(compare), c(std::move(cont)) {
		c.insert(c.end(), first, last);
		makeHeap();
	}

	template <class Alloc>
	explicit Heap(const Alloc& alloc)
	: Heap(Compare(), alloc) {}

	template <class Alloc,
		RequireAllocator<container_type, Alloc> = true>
	Heap(const Compare& compare, const Alloc& alloc)
	: comp(compare), c(alloc) {}

	template <class Alloc,
		RequireAllocator<container_type, Alloc> = true>
	Heap(const Compare& compare, const Container& cont,
		const Alloc& alloc)
	: comp(compare), c(cont, alloc) {
		makeHeap();
	}

	template <class Alloc,
		RequireAllocator<container_type, Alloc> = true>
	Heap(const Compare& compare, Container&& cont,
		const Alloc& alloc)
	: comp(compare), c(std::move(cont), alloc) {
		makeHeap();
	}

	template <class Alloc,
		RequireAllocator<container_type, Alloc> = true>
	Heap(const Heap& other, const Alloc& alloc)
	: comp(other.comp), c(other.c, alloc) {}

	template <class Alloc,
		RequireAllocator<container_type, Alloc> = true>
	Heap(Heap&& other, const Alloc& alloc)
	: comp(std::move(other.comp)), c(std::move(other.c), alloc) {}

	template <class InputIt, class Alloc,
		RequireInputIterator<InputIt> = true,
		RequireAllocator<container_type, Alloc> = true>
	Heap(InputIt first, InputIt last, const Compare& compare,
		const Alloc& alloc)
	: comp(compare), c(first, last, alloc) {
		makeHeap();
	}

	template <class InputIt, class Alloc,
		RequireInputIterator<InputIt> = true,
		RequireAllocator<container_type, Alloc> = true>
	Heap(InputIt first, InputIt last, const Compare& compare,
		const Container& cont, const Alloc& alloc)
	: comp(compare), c(cont, alloc) {
		c.insert(c.end(), first, last);
		makeHeap();
	}

	template <class InputIt, class Alloc,
		RequireInputIterator<InputIt> = true,
		RequireAllocator<container_type, Alloc> = true>
	Heap(InputIt first, InputIt last, const Compare& compare,
		Container&& cont, const Alloc& alloc)
	: comp(compare), c(std::move(cont), alloc) {
		c.insert(c.end(), first, last);
		makeHeap();
	}

	~Heap() {}

	Heap& operator=(const Heap& other) = default;
	Heap& operator=(Heap&& other) = default;

/*
Iterators */

	iterator begin() {
		return c.begin();
	}

	const_iterator begin() const {
		return c.cbegin();
	}

	iterator end() {
		return c.end();
	}

	const_iterator end() const {
		return c.cend();
	}

/*
Priority Queue functions */
	const_reference top() const {
		return c.front();
	}

	bool empty() const {
		return c.empty();
	}

	size_type size() const {
		return c.size();
	}

	void push(const value_type& v) {
		c.push_back(v);
		heapifyUp();
	}

	void push(value_type&& v) {
		c.push_back(std::move(v));
		heapifyUp();
	}

	template <typename... Args>
	void emplace(Args&&... args) {
		c.emplace_back(std::forward<Args>(args)...);
		heapifyUp();
	}

	void pop() {
		heapifyDown();
	}

	void swap(Heap& other) noexcept {
		std::swap(c, other.c);
		std::swap(comp, other.comp);
	}

	value_compare value_comp() const {
		return comp;
	}

private:
	void makeHeap() {
		DSA::make_heap(c.begin(), c.end(), comp);
	}
	void heapifyUp() {
		DSA::push_heap(c.begin(), c.end(), comp);
	}

	void heapifyDown() {
		DSA::pop_heap(c.begin(), c.end(), comp);
		c.pop_back();
	}

protected:
	value_compare comp;
	container_type c;
};

}

namespace std {

template <class T, class Container, class Compare>
void swap(  DSA::Heap<T, Container, Compare>& lhs,
			DSA::Heap<T, Container, Compare>& rhs) {
	lhs.swap(rhs);
}

}

#endif /* HEAP_HPP */
