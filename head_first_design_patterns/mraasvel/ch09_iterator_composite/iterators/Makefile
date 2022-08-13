BUILD_DIR = target

all: run

run: build
	$(BUILD_DIR)/app/a.out

test: build
	$(BUILD_DIR)/test/test.out

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR)

.PHONY: all run test build
