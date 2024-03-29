#pragma once

#include "inversion_count_of_array.hpp"
#include "iterative_quicksort.hpp"
#include "introsort.hpp"
#include <vector>

namespace grokking {
int num_rotations(const std::vector<int>& v);
std::string lcp(const std::vector<std::string>& v);
int unbounded_binary_search(std::function<int(int)> f);
void test_powers();
void test_find_missing_term();
}
