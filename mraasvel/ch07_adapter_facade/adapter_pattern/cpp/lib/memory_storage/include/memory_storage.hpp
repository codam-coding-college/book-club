#pragma once

#include <string>
#include <unordered_map>
#include <exception>
#include <vector>

template <typename T>
class MemoryStorage {
public:
	struct Entity {
		Entity(int id, T data): id(id), data(data) {}
		int id;
		T data;
	};

public:
	int store(T data) {
		int id = ID++;
		storage[id] = std::move(data);
		return id;
	}

	std::vector<Entity> find_all() {
		std::vector<Entity> result;
		for (auto it : storage) {
			result.push_back(Entity { it.first, it.second });
		}
		return result;
	}

	Entity find(int id) {
		auto data = storage.find(id);
		if (data == storage.end()) {
			throw std::runtime_error("id not found exception");
		}
		return Entity { data->first, data->second };
	}

	void remove(int id) {
		storage.erase(id);
	}

private:
	static int ID;
	std::unordered_map<int, T> storage;
};

template <typename T>
int MemoryStorage<T>::ID = 1;
