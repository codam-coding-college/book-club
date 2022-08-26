NAME := a.out
CC := g++
CFLAGS := -Wall -Wextra -Werror
LFLAGS :=
DFLAGS := -g

BUILD_DIR = target
EXEC = $(BUILD_DIR)/$(NAME)
ODIR = $(BUILD_DIR)/obj
SDIR := src

DEBUG_DIR := debug
DBG := lldb
ifdef DEBUG
CFLAGS += $(DFLAGS)
BUILD_DIR = $(DEBUG_DIR)
endif

SRC := $(shell find $(SDIR) -name "*.cpp")
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/$(SUBDIR)%.o,$(SRC))

all: build

run: build
	$(EXEC)

debug:
	$(MAKE) build DEBUG=1
	$(DBG) $(DEBUG_DIR)/$(NAME)

build: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(@D)
	$(CC) -o $@ $< $(LFLAGS)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@$(RM) -r $(BUILD_DIR)

.PHONY: all run build debug
