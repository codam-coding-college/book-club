NAME := src/diff.out
BUILD_DIR := debug
TARGET := $(BUILD_DIR)/$(NAME)

run: build
	./$(TARGET)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR)
