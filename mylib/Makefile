# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g -fsanitize=address -Iinclude

# Source files in src/
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

# Default target: build tests
all: test_tensor

# Test target
test_tensor: tests/test_tensor.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Object file rule
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: test_tensor
	./test_tensor

# Clean
clean:
	rm -f src/*.o test_tensor
