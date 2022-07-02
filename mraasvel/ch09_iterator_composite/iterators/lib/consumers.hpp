#pragma once

#include <vector>
#include <functional>

namespace Maarten {

using std::vector;

/*
Sum together all iterator values */
template <typename Iterator>
typename Iterator::Item sum(Iterator it) {
	typename Iterator::Item result {};
	while (it.has_next()) {
		result += it.next();
	}
	return result;
}

/*
Collect yielded iterator values into a vector */
template <typename Iterator>
vector<typename Iterator::Item> collect(Iterator it) {
	vector<typename Iterator::Item> result;
	while (it.has_next()) {
		result.emplace_back(it.next());
	}
	return result;
}

/*
Accumulate a value over iteration
Applies the function `f` to each item with the current accumulator
The return value of function `f` is the next value of the accumulator */
template <typename Accumulator, typename Iterator, typename Functor>
Accumulator fold(Accumulator init,
				Iterator it,
				Functor f) {
	while (it.has_next()) {
		init = f(init, it.next());
	}
	return init;
}

}
