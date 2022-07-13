NAME := parser

SRCS := main.cpp ../json/JsonNode.cpp Parser.cpp ParserStates.cpp ParserUtils.cpp
HEADERS := ../json/JsonNode.h Parser.h
INCLUDES := -I "../json/"

CXXFLAGS := -Wall -Wextra -std=c++11

OBJS := $(SRCS:%=%.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(CXX) $(OBJS) -o $(NAME)

%.cpp.o: %.cpp
	@echo "Compiling: " $<
	@$(CXX)  $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: clean fclean re
clean:
	@rm -Rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
