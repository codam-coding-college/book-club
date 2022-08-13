#pragma once

#include <iterator>
#include <type_traits>

namespace sorting {

	namespace _detail_ {

	template <typename Iterator, typename Tag>
	using RequireIterator =
		typename std::enable_if<
			std::is_convertible<
				typename std::iterator_traits<Iterator>::iterator_category,
				Tag
			>::value,
			bool
		>::type;

	}

template <typename RandomAccessIterator>
using RequireRandomAccessIterator =
	_detail_::RequireIterator<RandomAccessIterator, std::random_access_iterator_tag>;

}
