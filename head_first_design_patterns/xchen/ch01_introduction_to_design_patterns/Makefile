NAME = a.out

OBJ_DIR := obj
DEP_DIR := dep
SRC_DIR := src

SRC := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEP := $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC))

CPP = clang++ -std=c++14
CFLAG = -Wall -Wextra -Werror -pedantic 

ifndef CHECK_NONUSE
	CFLAG += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function
endif


all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CFLAG) -o $@ $^

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CPP) -c -o $@ $< $(CFLAG)
	
$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $< -MM -MF $@ -MT $(OBJ_DIR)/$*.o $(CFLAG)

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
