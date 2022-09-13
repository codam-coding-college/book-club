CXX = g++

NAME := a.out
BUILD_DIR := build
SDIR := src
IDIR := include

EXEC := $(BUILD_DIR)/$(NAME)
SRC := $(shell find $(SDIR) -name *.cpp)

run: build
	$(EXEC)

build: $(EXEC)

$(EXEC): $(SRC)
	mkdir -p $(@D)
	$(CXX) $(SRC) -I$(IDIR) -o $@

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE)

.PHONY: build run clean
