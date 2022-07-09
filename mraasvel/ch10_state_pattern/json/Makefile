BUILD_DIR = debug
BUILD_TYPE = Debug

all: run

release:
	$(MAKE) run BUILD_DIR=target BUILD_TYPE=Release

run: build
	$(BUILD_DIR)/app/a.out

test: build
	$(BUILD_DIR)/test/test.out

gdb: build
	gdb $(BUILD_DIR)/app/a.out

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: all release run test gdb build clean re
