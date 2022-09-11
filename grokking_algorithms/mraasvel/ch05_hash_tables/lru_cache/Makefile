NAME := a.out
BUILD_DIR = .
BUILD_FLAGS := -std=c++17

run: build
	@$(BUILD_DIR)/$(NAME)

build:
	g++ main.cpp $(BUILD_FLAGS) -o $(NAME)
