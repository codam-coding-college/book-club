#include "game_state.hpp"

namespace game {

GameState::GameState() {}

SaveData GameState::get_save_data() const {
	return SaveData { uid };
}

}
