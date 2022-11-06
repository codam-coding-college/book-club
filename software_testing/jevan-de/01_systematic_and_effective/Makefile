PROG_NAME		= tester

CFLAGS			= -Wall -Werror -Wextra # -fsanitize=address
CXXFLAGS		= -std=c++11

MAIN_SOURCES	= estimates.c
TEST_SOURCES	= test_estimates.cpp main.cpp

MAIN_OBJECTS	= $(MAIN_SOURCES:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<; 

$(PROG_NAME): fclean $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(MAIN_OBJECTS) $(TEST_SOURCES) -o $@

clean:
	rm -f $(MAIN_OBJECTS) $(TEST_)

fclean: clean
	rm -f $(PROG_NAME)
