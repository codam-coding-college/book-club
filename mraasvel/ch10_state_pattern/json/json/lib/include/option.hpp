#pragma once

#include <type_traits>
#include <cassert>
#include <utility>

namespace json {

/*
Optional value
*/
template <typename T>
class Option {
	private:
		enum Type {
			Some,
			None
		};

	public:
		Option()
		: state(None) {}

		template <typename U = T>
		Option(const U& value)
		: state(Some) {
			::new(&store) T { value };
		}

		template <typename U = T>
		Option(U&& value)
		: state(Some) {
			::new(&store) T { std::move(value) };
		}

		template <typename U = T>
		Option(Option<U>&& other)
		: state(other.state) {
			if (other.is_some()) {
				other.state = None;
				::new(&store) T { std::move(*reinterpret_cast<U*>(&other.store)) };
			}
		}

		~Option() {
			if (is_some()) {
				reinterpret_cast<T*>(&store)->~T();
			}
		}

		template <typename U = T>
		Option& operator=(U&& rhs) {
			if (is_some()) {
				*reinterpret_cast<T*>(&store) = std::move(rhs);
			} else {
				::new(&store) T { std::move(rhs) };
			}
			return *this;
		}

		T& value() {
			assert(is_some());
			return *reinterpret_cast<T*>(&store);
		}

		const T& value() const {
			assert(is_some());
			return *reinterpret_cast<const T*>(&store);
		}

		bool is_some() const {
			return state == Some;
		}

		bool is_none() const {
			return state == None;
		}

	private:
		Type state;
		typename std::aligned_storage<sizeof(T), alignof(T)>::type store;
};

}
