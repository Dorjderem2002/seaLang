# The following line specifies the name of the executable that will be built.
TARGET = kimulator

# The following line specifies the source files that will be compiled.
SRCS = $(wildcard src/6502/*.cpp src/*.cpp )

# The following line specifies the compiler that will be used.
CC = g++

# The following line specifies the compiler flags that will be used.
CFLAGS = -Wall -std=c++17

# The following line specifies the linker flags that will be used.
LDFLAGS = -lsfml-graphics -lsfml-system -lsfml-window -I./include/ -L./lib/

# The following line specifies the dependencies of the executable.
DEPS = 

# The following line specifies the rule for building the executable.
$(TARGET): $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCS)

# The following line specifies the rule for cleaning up the build.
clean:
	rm -f $(TARGET)
