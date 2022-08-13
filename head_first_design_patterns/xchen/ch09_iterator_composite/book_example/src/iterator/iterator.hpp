#pragma once
#include "../menu/MenuItem.hpp"

// interface
template<class T>
class Iterator {
	public:
		virtual bool hasNext() const = 0;
		virtual T next() = 0;
};

template<class T>
class DinerMenuIterator : public Iterator<T> {
	public:
		DinerMenuIterator(MenuItem *items, int size): items(items), size(size) {};
		bool hasNext() const {
			return !(position >= size || items[position].getName().empty());
		};
		T next() {
			T item = items[position];
			position++;
			return item;
		};
	private:
		T *items;
		int size;
		int position = 0;
};

template<class T>
class PancakeHouseMenuIterator : public Iterator<T> {
	public:
		PancakeHouseMenuIterator(std::vector<T> items): items(items) {};
		bool hasNext() const {
			return !((unsigned long)position >= items.size());
		};
		T next() {
			T item = items[position];
			position++;
			return item;
		};
	private:
		std::vector<T> items;
		int position = 0;
};
