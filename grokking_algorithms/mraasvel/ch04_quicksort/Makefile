NAME := a.out
CC := g++
CXXFLAGS = -Wall -Wextra -Werror
CXXFLAGS += -Wno-unused-parameter -Wno-unused
IFLAGS = -I$(IDIR)
LFLAGS :=
DFLAGS := -g

BUILD_DIR = target
EXEC = $(BUILD_DIR)/$(NAME)
ODIR = $(BUILD_DIR)/obj
DDIR = $(BUILD_DIR)/dep
SDIR := src
IDIR := src

DEBUG_DIR := debug
DBG := lldb
ifdef DEBUG
CXXFLAGS += $(DFLAGS)
BUILD_DIR = $(DEBUG_DIR)
endif

SRC := $(shell find $(SDIR) -name "*.cpp")
OBJ := $(patsubst $(SDIR)/%.cpp,$(ODIR)/$(SUBDIR)%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.cpp,$(DDIR)/$(SUBDIR)%.d,$(SRC))

all: build

run: build
	$(EXEC)

debug:
	$(MAKE) build DEBUG=1
	$(DBG) $(DEBUG_DIR)/$(NAME)

build: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(IFLAGS)

$(DEP): $(DDIR)/%.d: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $< -MM -MF $@ -MT $(ODIR)/$*.o $(CXXFLAGS) $(IFLAGS)

clean:
	@$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: all run build debug re
-include $(DEP)
