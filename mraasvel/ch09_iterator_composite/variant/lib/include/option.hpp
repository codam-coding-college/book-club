#pragma once

#include <type_traits>
#include <iostream> // remove

namespace variant {

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

		Option(const T& value)
		: state(Some) {
			::new(&store) T { value };
		}

		Option(T&& value)
		: state(Some) {
			::new(&store) T { std::move(value) };
		}

		~Option() {
			if (is_some()) {
				std::cout << "destroying value" << std::endl;
				reinterpret_cast<T*>(&store)->~T();
			}
		}

		T& value() {
			return *reinterpret_cast<T*>(&store);
		}

		const T& value() const {
			return *reinterpret_cast<T*>(&store);
		}

		bool is_some() {
			return state == Some;
		}

		bool is_none() {
			return state == None;
		}

	private:
		Type state;
		std::aligned_storage<sizeof(T), alignof(T)> store;
};

}
