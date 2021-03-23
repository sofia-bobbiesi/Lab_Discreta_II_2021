CFLAGS = -Wall -Wextra -O3 -std=c9 -fsanitize=address,undefine -I
CC = gcc
TARGET = discreta_ii
OBJS = $(SRCS:.c=.o)
SRCS = main.c

all: 	$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS)  -c $<  -o $@

.PHONY: clean

clean:
	$(RM) $(OBJS) *~ $(TARGET)
