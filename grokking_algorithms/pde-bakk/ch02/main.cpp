#include <iostream>
#include <vector>
#include <list>

template<typename T>
size_t find_pos_of_smallest(const std::vector<T>& arr, size_t startpos) {
	T	min_item = arr[startpos];
	size_t	min_item_idx = startpos;

	for (size_t i = startpos; i < arr.size(); i++) {
		T item = arr[i];
		if (item < min_item) {
			min_item = item;
			min_item_idx = i;
		}
	}
	return (min_item_idx);
}

template<typename T>
int	selection_sort_array(std::vector<T>& arr) {
	for (size_t sorted_len = 0; sorted_len < arr.size(); sorted_len++) {
		size_t min_idx = find_pos_of_smallest(arr, sorted_len);
		std::swap(arr[sorted_len], arr[min_idx]);
	}
	return (0);
}

int main() {
	std::vector<int>	arr = {8, 42, 10, 90, 67};
	selection_sort_array(arr);
	for (auto i : arr) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;
	return 0;
}
