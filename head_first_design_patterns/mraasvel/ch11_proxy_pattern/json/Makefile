ifdef RELEASE
	BUILD_DIR = target
	BUILD_TYPE = Release
else
	BUILD_DIR = debug
	BUILD_TYPE = Debug
endif

all: build

release:
	$(MAKE) build RELEASE=1

run: build
	$(BUILD_DIR)/app/a.out $(ARGS)

test: build
	$(BUILD_DIR)/test/test.out $(ARGS)

gdb: build
	gdb $(BUILD_DIR)/app/a.out $(ARGS)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: all release run test gdb build clean re
