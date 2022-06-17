BUILD_DIR := build
TARGET := a.out
TEST_TARGET := test.out
LIB_TARGET := design

all: run

run:
	$(MAKE) build BUILD_TARGET=$(TARGET)
	$(BUILD_DIR)/src/$(TARGET)

test:
	$(MAKE) build BUILD_TARGET=$(TEST_TARGET)
	$(BUILD_DIR)/test/$(TEST_TARGET)

lib:
	$(MAKE) build BUILD_TARGET=$(LIB_TARGET)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target $(BUILD_TARGET)

$(BUILD_DIR): setup

setup:
	cmake -B $(BUILD_DIR) -S .

.PHONY: all run test build setup lib
