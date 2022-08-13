#pragma once

#include "save.hpp"

namespace game {

// concept: holds all data necessary to reconstruct a game state
class GameState {
public:
	GameState();

	SaveData get_save_data() const;

private:
	int uid;
};

}
