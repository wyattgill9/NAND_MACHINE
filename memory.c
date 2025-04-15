#include "memory.h"
#include <assert.h>

void init_memory(Memory* mem) {
    clear_memory(mem);
}

void read_word(Memory* mem, int address, bool word[WORD_SIZE]) {
    assert(address >= 0 && address < MEMORY_SIZE);
    
    for (int i = 0; i < WORD_SIZE; i++) {
        word[i] = mem->data[address][i];
    }
}

void write_word(Memory* mem, int address, bool word[WORD_SIZE]) {
    assert(address >= 0 && address < MEMORY_SIZE);
    
    for (int i = 0; i < WORD_SIZE; i++) {
        mem->data[address][i] = word[i];
    }
}

void clear_memory(Memory* mem) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            mem->data[i][j] = false;
        }
    }
}
