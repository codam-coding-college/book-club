#include "eight_puzzle.hpp"
#include <iostream>

int main() {
	EP::EightPuzzle ep;
	auto result = ep.solve();
	std::cout << result << std::endl;
	return 0;
}
