#include "game.hpp"
#include "memory_storage.hpp"

using game::SaveData;
using game::SaveStorage;

class MemoryStorageSave: public SaveStorage {
public:
	virtual int save(SaveData state) {
		return storage.store(state);
	};

	virtual SaveData load(int id) {
		return storage.find(id).data;
	};

	virtual void remove(int id) {
		storage.remove(id);
	};

private:
	MemoryStorage<SaveData> storage;
};

int main() {
	std::unique_ptr<SaveStorage> storage { new MemoryStorageSave };
	game::run(std::move(storage));
	return 0;
}
