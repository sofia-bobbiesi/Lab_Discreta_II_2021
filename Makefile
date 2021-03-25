CFLAGS = -Wall -Wextra -O3 -std=c99 -I -fsanitize=address,undefined 
CC = gcc
TARGET = discreta_2
OBJS = $(SRCS:.c=.o)
SRCS = parte_1.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)

valgrind:
	valgrind --leak-check=full ./$(TARGET)


