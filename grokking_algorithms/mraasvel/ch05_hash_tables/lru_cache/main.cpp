#include <unordered_map>
#include <list>
#include <optional>

namespace LRU {

using std::unordered_map;
using std::list;
using std::optional;

template <typename K, typename V>
class Cache {
	public:
		using KeyType = K;
		using ValueType = V;

	private:
		using ListType = list<std::pair<KeyType, ValueType>>;
		using ListIterator = typename ListType::iterator;
		using MapType = unordered_map<KeyType, ListIterator>;

	public:
		bool contains_key(const KeyType& key) {
			return map.count(key) > 0;
		}

		const optional<ValueType> get(const KeyType& key) {
			auto it = map.find(key);
			if (it == map.end()) {
				return optional<ValueType> {};
			}
			// update LRU: move iterator to front of list
			cache.splice(cache.begin(), cache, it->second);
			return optional { cache.front().second };
		}

		void insert(const KeyType& key, const ValueType& value) {
			cache.emplace_front(std::make_pair(key, value));
			if (cache.size() > CACHE_SIZE) {
				map.erase(cache.back().first);
				cache.pop_back();
			}
			map.insert(std::make_pair(key, cache.begin()));
		}

	private:
		static constexpr size_t CACHE_SIZE = 100;
		MapType map;
		ListType cache;
};

}

class Service {
	public:
		using KeyType = std::string;
		using ValueType = std::string;

		std::string get(const std::string& key) {
			auto result = cache.get(key);
			if (result.has_value()) {
				return result.value();
			}
			auto value = std::string { "some string" };
			cache.insert(key, value);
			return value;
		}

	private:
		LRU::Cache<KeyType, ValueType> cache;
};


int main() {
	Service service;
	auto result = service.get("lmao");
	printf("%s\n", result.c_str());
	auto r2 = service.get("lmao");
	printf("%s\n", r2.c_str());
	auto r3 = service.get("2");
	printf("%s\n", r3.c_str());
	return 0;
}
