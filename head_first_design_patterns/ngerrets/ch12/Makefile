# ------------------- EDIT THIS SECTION -------------------
TARGET ?= mvc

BIN_DIR ?= ./
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src ./include
INC_DIRS ?= ./include
CPPFLAGS ?= -Wall -Wextra -std=c++11
LDFLAGS ?=

# CXX := g++

# --------------------------- END -------------------------

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS += $(INC_FLAGS) -MMD -MP

# ifeq ($(OS),Windows_NT)
#  LDFLAGS += $(WINFLAGS)
# endif

.PHONY: all

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@echo "Linking..."
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Done!"

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling: " $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: fclean clean re
clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(BIN_DIR)/$(TARGET)

re: clean all

-include $(DEPS)

MKDIR_P ?= mkdir -p