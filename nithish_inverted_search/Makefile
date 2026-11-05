# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra

# Source Files
SRC = main.c common.c create.c dispaly.c search.c save.c update.c

# Object Files
OBJ = $(SRC:.c=.o)

# Executable
TARGET = a.out

# Build Target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile Source Files
%.o: %.c main.h
	$(CC) $(CFLAGS) -c $<

# Run Program
run: $(TARGET)
	./$(TARGET)

# Clean Files
clean:
	rm -f *.o $(TARGET)

# Rebuild Project
rebuild: clean $(TARGET)