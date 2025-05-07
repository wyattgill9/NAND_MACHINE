CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = cpu.c gates.c memory.c alu.c util.c
OBJS = $(SRCS:.c=.o)
TARGET = cpu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
