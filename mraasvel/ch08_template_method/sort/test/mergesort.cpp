#include "mergesort.hpp"
#include <vector>
#include <ctime>
#include <random>
#include <catch2/catch.hpp>

using ContainerType = std::vector<int>;

static int randomIntRange(int min, int max) {
	static std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
	std::uniform_int_distribution<> die(min, max);
	return die(mersenne);
}

static ContainerType randomContainer(std::size_t n) {
	ContainerType x;
	x.reserve(n);
	while (n-- > 0) {
		x.push_back(randomIntRange(0, 10000));
	}
	return x;
}

TEST_CASE("Merge Sort" "[sort]") {
		static std::vector<ContainerType> testcases {
		{},
		{1},
		{2, 1},
		{1, 2, 3, 4},
		{4, 3, 2, 1},
		randomContainer(100),
		randomContainer(10000),
	};

	for (std::size_t i = 0; i < testcases.size(); ++i) {
		auto testcase = testcases[i];
		SECTION(std::to_string(i)) {
			auto copy {testcase};
			std::sort(copy.begin(), copy.end());
			sorting::merge_sort(testcase.begin(), testcase.end());
			REQUIRE(copy == testcase);
			REQUIRE(std::is_sorted(testcase.begin(), testcase.end()));
		}
	}
}
