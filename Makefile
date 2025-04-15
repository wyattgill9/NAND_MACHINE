CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = cpu.c alu.c gates.c memory.c
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