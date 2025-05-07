#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>

//64-bit words and 1024 words of memory -> 65 kb

#define MEMORY_SIZE 1024
#define WORD_SIZE 64

typedef struct {
    bool data[MEMORY_SIZE][WORD_SIZE];
} Memory;

void init_memory(Memory* mem);

void read_word(Memory* mem, int address, bool word[WORD_SIZE]);

void write_word(Memory* mem, int address, bool word[WORD_SIZE]);

void clear_memory(Memory* mem);

#endif
