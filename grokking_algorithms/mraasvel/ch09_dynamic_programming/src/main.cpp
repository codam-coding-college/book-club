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

static BacktraceResult backtrack(const std::vector<std::string>& a, const std::vector<std::string>& b, const Matrix& lcs) {
	BacktraceResult result;
	int row = a.size() - 1;
	int col = b.size() - 1;
	while (row >= 0 && col >= 0) {
		int cur = lcs.get(row, col);
		if (cur == lcs.left(row, col, -1)) {
			col -= 1;
		} else if (cur == lcs.top(row, col, -1)) {
			row -= 1;
		} else {
			if (row == 0 && col == 0 && cur == 0) {
				break;
			}
			result.part_of_lcs_a.insert(row);
			result.part_of_lcs_b.insert(col);
			col -= 1;
			row -= 1;
		}
	}
	return result;
}

#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

static void print_no_change(const std::string& line) {
std::cout << "  " << line << '\n';
}
static void print_delete(const std::string& line) {
	std::cout << COLOR_RED << "- " << line << COLOR_RESET << '\n';
}
static void print_add(const std::string& line) {
	std::cout << COLOR_GREEN << "+ " << line << COLOR_RESET << '\n';
}

static void print_diff(const std::vector<std::string>& a, const std::vector<std::string>& b, const BacktraceResult& bt) {
	int i = 0;
	int j = 0;
	while (i < a.size() || j < b.size()) {
		if (i == a.size()) {
			print_add(b[j]);
			j++;
		} else if (j == b.size()) {
			print_delete(a[i]);
			i++;
		} else if (bt.part_of_lcs_a.count(i) == 0) {
			print_delete(a[i]);
			i++;
		} else if (bt.part_of_lcs_b.count(j) == 0) {
			print_add(b[j]);
			j++;
		} else {
			print_no_change(a[i]);
			i++;
			j++;
		}
	}
}

static void print_diff_backtrack(const std::vector<std::string>& a, const std::vector<std::string>& b, const Matrix& lcs, int i, int j) {
	int left = lcs.left(i, j, -1);
	int top = lcs.top(i, j, -1);
	if (i < 0 && j < 0) {
		return;
	} else if (i < 0) {
		print_diff_backtrack(a, b, lcs, i, j-1);
		print_add(b[j]);
	} else if (j < 0) {
		print_diff_backtrack(a, b, lcs, i-1, j);
		print_delete(a[i]);
	} else if (a[i] == b[j]) {
		print_diff_backtrack(a, b, lcs, i-1, j-1);
		print_no_change(a[i]);
	} else if (left >= top) {
		print_diff_backtrack(a, b, lcs, i, j-1);
		print_add(b[j]);
	} else {
		print_diff_backtrack(a, b, lcs, i-1, j);
		print_delete(a[i]);
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
	Matrix matrix = longest_common_subsequence(original, latest);
	print_diff_backtrack(original, latest, matrix, original.size() - 1, latest.size() - 1);
	return 0;
}
