#include <vector>
#include <string>

namespace grokking {

	namespace _detail_ {

	// O(m) where m is the length of the LCP of (x, y)
	std::string lcp_string(const std::string& x, const std::string y) {
		std::string prefix;
		for (int i = 0; i < (int)std::min(x.size(), y.size()); i++) {
			if (x[i] != y[i]) {
				break;
			}
			prefix.push_back(x[i]);
		}
		return prefix;
	}

	// divide and conquer
	// can be optimized for space complexity by returning indices
	std::string lcp(const std::vector<std::string>& v, int start, int end) {
		if (end - start == 0) {
			return "";
		} else if (end - start == 1) {
			return v[start];
		}
		int midpoint = (start + end) / 2;
		auto left = lcp(v, start, midpoint);
		auto right = lcp(v, midpoint, end);
		return lcp_string(left, right);
	}

	}

std::string lcp(const std::vector<std::string>& v) {

	/* O(n * m) where n is the number of strings and m is the length of LCP: */
	// if (v.size() == 0) {
	// 	return "";
	// }
	// std::string prefix;
	// for (int i = 0; i < (int)v[0].size(); i++) {
	// 	char ch = v[0][i];
	// 	for (int j = 0; j < (int)v.size(); j++) {
	// 		if (ch != v[j][i]) {
	// 			return prefix;
	// 		}
	// 	}
	// 	prefix.push_back(ch);
	// }
	// return prefix;

	auto prefix = _detail_::lcp(v, 0, v.size());
	return prefix;
}

}
