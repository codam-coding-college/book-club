NAME = json_parser.a

INC_DIR = ./include
SRC_DIR = ./srcs
OBJ_DIR = ./obj
SRC_EXT = cpp
OBJ_EXT = o
INC_EXT = hpp
#SRCS = $(wildcard $(SRC_DIR)/*.c)
INCLUDE = -I $(INC_DIR) -I libft/include
SRCS = $(shell find $(SRC_DIR) -type f -name "*.$(SRC_EXT)")
HEADERS = $(shell find $(INC_DIR) -type f -name "*.$(INC_EXT)")
OBJECTSS = $(SRCS:.$(SRC_EXT)=.$(OBJ_EXT))
OBJS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJECTSS))

# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m

CFLAGS = -Wall -Werror -Wextra -std=c++17
ifdef DEBUG
 CFLAGS += -g3 -fsanitize=address
endif
SHELL := /bin/bash
export SHELL
export DEBUG
ifdef SPEED
 CFLAGS += -Ofast
endif

all: $(NAME)

$(NAME): $(LIBS) $(OBJS) $(HEADERS)
	ar -rc $(NAME) $(OBJS)
	@printf "$(PINK)Done building $(NAME) $(RESET)\n"

%.a: %
	$(MAKE) -C $< && cp $</$@ .

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p "$(@D)"
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	/bin/rm -f $(OBJS)
	@/bin/rm -f *.o *~ *.gch

fclean: clean
	/bin/rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug: DEBUG=1
debug:
	$(MAKE) fclean
	$(MAKE) all

test_ez: $(NAME)
	$(CXX) $(CFLAGS) $(INCLUDE) main.cpp $(NAME) -o json.out && ./json.out tests/basic_test.json

test: $(NAME)
	$(CXX) $(CFLAGS) $(INCLUDE) main.cpp $(NAME) -o json.out && ./json.out tests/ft_ssl_tests.json
