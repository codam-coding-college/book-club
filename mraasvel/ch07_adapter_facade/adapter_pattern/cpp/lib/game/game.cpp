#include "game.hpp"
#include "game_state.hpp"

namespace game {

int run(std::unique_ptr<SaveStorage> storage) {
	GameState state;
	/*
	- play game, modify state
	- load save button
	- save button
	- delete save button
	*/
	storage->save(state.get_save_data());
	return 0;
}

}
