#pragma once

#include "save.hpp"
#include <memory>

namespace game {

int run(std::unique_ptr<SaveStorage> storage);

}
