#include "memory_storage.hpp"
#include <catch2/catch.hpp>

TEST_CASE("memory storage") {
	MemoryStorage<int> storage {};
	auto id = storage.store(42);
	REQUIRE(id == 1);
	auto entity = storage.find(id);
	auto entities = storage.find_all();
	REQUIRE(entity.id == id);
	REQUIRE(entity.data == 42);
	REQUIRE(entities.size() == 1);
	REQUIRE(entities[0].id == entity.id);
	storage.remove(id);
	REQUIRE(storage.find_all().size() == 0);
}
