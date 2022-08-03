NAME = json
CXX = g++

SRC_DIR = src
OBJ_DIR = obj

SRC = 	element.cpp \
		parsed_json.cpp \
		parser.cpp \
		main.cpp

INCLUDE = -I ./src/include

OBJ := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
SRC = $(SRC:%.cpp=$(SRC_DIR)/%.cpp)

CFLAGS = -Wall -Werror -Wextra -std=c++17 -g #-g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) -c  $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
