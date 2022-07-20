NAME := proxy.out

SRCS := src/main.cpp src/Subject.cpp src/Proxy.cpp src/Connection.cpp
HEADERS := include/Proxy.hpp include/Subject.hpp include/Connection.hpp
INCLUDES := -I "include/"

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
