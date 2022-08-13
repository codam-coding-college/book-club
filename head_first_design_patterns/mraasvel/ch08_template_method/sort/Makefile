BUILD_DIR = target

all: run

run: build
	$(BUILD_DIR)/test/a.out

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR)

.PHONY: all run build init
