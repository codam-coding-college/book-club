#pragma once

namespace game {

struct SaveData {
	int uid;
};

// allows user to customize how save data is stored (DB, File, Cloud, ...)
class SaveStorage {
public:
	virtual int save(SaveData state) = 0;
	virtual SaveData load(int id) = 0;
	virtual void remove(int id) = 0;
	virtual ~SaveStorage() {}
};

}
