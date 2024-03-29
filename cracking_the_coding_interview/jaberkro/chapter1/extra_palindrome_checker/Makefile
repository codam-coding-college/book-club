CXXFLAGS = -Wall -Wextra -Werror

SRC = palindrome.cpp
OBJ = $(SRC:.cpp=.o)
NAME = palindromeChecker

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
