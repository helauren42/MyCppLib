SRCS = test.cpp

CFLAGS = -Wall -Werror -Wextra -Wno-unused

all: $(SRCS)
	c++ -g3 $(CFLAGS) $(SRCS)

run: all
	./test.sh

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test.sh
