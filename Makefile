CFLAGS = -Wall -Wextra -O3 -g -std=c99 -I -fsanitize=address,undefined 
CC = gcc
TARGET = discreta_2
OBJS = $(SRCS:.c=.o)
SRCS = parte_1.c avl-tree.c sorting.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)


