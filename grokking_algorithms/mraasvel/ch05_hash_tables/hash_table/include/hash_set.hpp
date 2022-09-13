#pragma once

#include <vector>
#include <list>
#include <iostream>

namespace grokking {

/**
 * @brief 
 * 
 * @tparam T 
 * @tparam Hash hasher object that overloads operator() as a hash function for type T: `size_t operator()(const T& key);`
 */
template <typename T, typename Hash>
class HashSet {
	public:
		using ValueType = T;
	
	private:
		struct HashNode {
			HashNode(const T& value, size_t hash_code)
			: value(value), hash_code(hash_code) {}
			T value;
			size_t hash_code;
		};

		using Bucket = std::list<HashNode>;
		using ArrayType = std::vector<Bucket>;

	public:
		HashSet(): _size(0) {
			buckets.resize(1);
		}

		// TODO: implement an iterator, return iterator
		bool find(const T& value) const {
			size_t hash_code = hasher(value);
			size_t index = hash_code % bucket_size();
			for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
				if (it->hash_code == hash_code && it->value == value) {
					return true;
				}
			}
			return false;
		}

		bool insert(const T& value) {
			resize_if_needed(1);
			size_t hash_code = hasher(value);
			if (do_insert(value, hash_code, buckets)) {
				_size++;
				return true;
			} else {
				return false;
			}
		}
	
		bool erase(const T& value) {
			size_t hash_code = hasher(value);
			size_t index = hash_code % bucket_size();
			for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
				if (it->hash_code == hash_code && it->value == value) {
					buckets[index].erase(it);
					return true;
				}
			}
			return false;
		}

		void print() const {
			int i = 0;
			std::cout << "Load factor: " << size() << " / " << bucket_size() << " = " << load_factor() << '\n';
			for (const auto& bucket: buckets) {
				std::cout << i++ << '\t';
				if (bucket.size() == 0) {
					std::cout << "---";
				} else {
					for (const auto& entry: bucket) {
						std::cout << entry.value << " -> ";
					}
					std::cout << "NULL";
				}
				std::cout << '\n';
			}
		}
	
	private:
		size_t bucket_size() const {
			return buckets.size();
		}

		float load_factor() const {
			return static_cast<float>(size()) / static_cast<float>(bucket_size());
		}

		size_t size() const {
			return _size;
		}

		void resize_if_needed(size_t n) {
			if (bucket_size() == 0) {
				buckets.resize(n * 2);
			} else if (load_factor() >= 0.7) {
				ArrayType next { bucket_size() * 2 };
				for (auto& bucket: buckets) {
					for (auto& entry: bucket) {
						do_insert(entry.value, entry.hash_code, next);
					}
				}
				buckets = next;
				print();
			}
		}

		bool do_insert(const T& value, size_t hash_code, ArrayType& buckets) {
			size_t index = hash_code % buckets.size();
			for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
				if (it->hash_code == hash_code && it->value == value) {
					return false;
				}
			}
			buckets[index].push_back(HashNode { value, hash_code });
			return true;
		}

	private:
		ArrayType buckets;
		Hash hasher;
		size_t _size;
};

}
