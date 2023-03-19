# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Libraries
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Source files
SRCS = main.c game.c graphics.c audio.c utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = randomon

# Default build target
all: $(EXEC)

# Rule for building the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
