NAME		=	uri_parser

CC			= 	clang++

FLAGS		= 	-Wall -Wextra -Werror -std=c++11

SRC			= 	main.cpp uri_parser.cpp

OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# DIRECTORIES
OBJ_DIR		=	build

# COLORS
CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
YELLOW		=	\033[0;33m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Removed: $(OBJ_DIR) folder$(RESET)"

quietclean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all run debug clean fclean re compare