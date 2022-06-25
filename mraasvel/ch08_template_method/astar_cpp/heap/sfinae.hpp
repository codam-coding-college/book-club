#pragma once

#include <iterator>
#include <type_traits>

namespace DSA {

	namespace Detail {

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

template <typename InputIterator>
using RequireInputIterator =
	Detail::RequireIterator<InputIterator, std::input_iterator_tag>;

template <typename BidirectionalIterator>
using RequireBidirectionalIterator =
	Detail::RequireIterator<BidirectionalIterator, std::bidirectional_iterator_tag>;

template <typename RandomAccessIterator>
using RequireRandomAccessIterator =
	Detail::RequireIterator<RandomAccessIterator, std::random_access_iterator_tag>;

template <typename Container, typename Allocator>
using RequireAllocator = 
	typename std::enable_if<
		std::uses_allocator<
			Container, Allocator
		>::value,
		bool
	>::type;

}
