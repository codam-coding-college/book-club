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

client: build
	$(BUILD_DIR)/examples/client/client.out $(ARGS)

server: build
	$(BUILD_DIR)/examples/server/server.out $(ARGS)

test: build
	$(BUILD_DIR)/test/test.out $(ARGS)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: all release client server test build clean re
