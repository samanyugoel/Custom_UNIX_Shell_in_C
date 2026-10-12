
CC = gcc
CFLAGS = -g -Wall -Wextra
TARGET = shell
SRC = main.c getword.c command.c cleanup.c pipe.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean: 
	rm -f $(TARGET)
