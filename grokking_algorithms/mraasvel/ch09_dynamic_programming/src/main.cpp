#include "matrix.hpp"
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

/*
git diff
*/

// Use LCS to find out which lines changed
template <typename T>
static Matrix longest_common_subsequence(const std::vector<T>& a, const std::vector<T>& b) {
	Matrix matrix(a.size(), b.size());
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)b.size(); j++) {
			if (a[i] == b[j]) {
				int previous = matrix.topleft(i, j, 0);
				matrix.put(i, j, previous + 1);
			} else {
				int left = matrix.left(i, j, 0);
				int top = matrix.top(i, j, 0);
				int value = std::max(left, top);
				matrix.put(i, j, value);
			}
		}
	}
	return matrix;
}

static std::vector<std::string> read_lines(const std::string& filename) {
	std::ifstream ifs { filename };
	if (!ifs.is_open()) {
		std::stringstream ss;
		ss << "error: failed to open file: " << filename;
		throw std::runtime_error(ss.str());
	}
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(ifs, line)) {
		lines.push_back(std::move(line));
	}
	return lines;
}

template <typename T>
static void dbg(const std::string& prefix, const std::vector<T>& container) {
	std::cout << prefix << ": [ ";
	for (auto it = container.begin(); it != container.end(); it++) {
		if (it != container.begin()) {
			std::cout << ", ";
		}
		std::cout << *it;
	}
	std::cout << " ]\n";
}

struct BacktraceResult {
	std::unordered_set<int> part_of_lcs_a;
	std::unordered_set<int> part_of_lcs_b;
};

static BacktraceResult backtrace(const std::vector<std::string>& a, const std::vector<std::string>& b, const Matrix& lcs) {
	BacktraceResult result;
	int row = a.size() - 1;
	int col = b.size() - 1;
	while (row >= 0 && col >= 0) {
		int cur = lcs.get(row, col);
		if (cur == lcs.left(row, col, -1)) {
			std::cout << "LEFT\n";
			col -= 1;
		} else if (cur == lcs.top(row, col, -1)) {
			std::cout << "UP\n";
			row -= 1;
		} else {
			std::cout << "DIAG\n";
			result.part_of_lcs_a.insert(row);
			result.part_of_lcs_b.insert(col);
			col -= 1;
			row -= 1;
		}
	}
	return result;
}

static void print_diff(const std::vector<std::string>& a, const std::vector<std::string>& b, const BacktraceResult& bt) {
	int i = 0;
	int j = 0;
	while (i < a.size() || j < b.size()) {
		if (i == a.size()) {
			std::cout << "+ " << b[j] << '\n';
			j++;
		} else if (j == b.size()) {
			std::cout << "- " << a[i] << '\n';
			i++;
		} else {
			if (bt.part_of_lcs_a.count(i) == 0) {
				std::cout << "- " << a[i] << '\n';
				i++;
			} else if (bt.part_of_lcs_b.count(j) == 0) {
				std::cout << "+ " << b[j] << '\n';
				j++;
			} else {
				i++;
				j++;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " original latest\n";
		return 1;
	}
	argc--; argv++;
	auto original = read_lines(argv[0]);
	auto latest = read_lines(argv[1]);
	dbg("original", original);
	dbg("latest", latest);
	Matrix matrix = longest_common_subsequence(original, latest);
	matrix.debug(std::cout);
	auto bt = backtrace(original, latest, matrix);
	print_diff(original, latest, bt);
	return 0;
}
