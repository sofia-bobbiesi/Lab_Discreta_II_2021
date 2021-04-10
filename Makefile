CFLAGS = -Wall -Wextra -O3 -g -std=c99 -I -fsanitize=address,undefined 
CC = gcc
TARGET = discreta_2
OBJS = $(SRCS:.c=.o)
SRCS = parte_1.c avl-tree.c main.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

callgrind:
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes ./$(TARGET)

massif:
	valgrind --tool=massif ./$(TARGET)
