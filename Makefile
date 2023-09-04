# Makefile

# Compiler
CC := g++
# Compiler flags
CFLAGS := -Wall -Wextra -std=c++11
# Output binary name
TARGET := main

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CC) $(CFLAGS) $< -o emulator

clean:
	rm -f $(TARGET)

.PHONY: all clean