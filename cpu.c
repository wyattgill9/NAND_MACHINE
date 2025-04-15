#include<stdbool.h>
#include "memory.h"
#include "gates.h"
#include <stdio.h>
#include "alu.h"

unsigned long long bool_to_ullong(bool word[64]) {
    unsigned long long result = 0;
    for (int i = 0; i < 64; i++) {
        if (AND(word[i], 1)) {
            unsigned long long mask = 1ULL << i;
            result = result + mask; 
        }
    }
    return result;
}

void ullong_to_bool(unsigned long long n, bool word[64]) {
    for (int i = 0; i < 64; i++) {
        unsigned long long mask = 1ULL << i;
        bool bit_set = AND((n & mask) != 0, 1);
        word[i] = bit_set;
    }
}

void fib() {
    Memory mem;
    init_memory(&mem);

    bool current[64] = {0};
    bool previous[64] = {0};
    bool next[64] = {0};
    bool counter[64] = {0};
    bool one[64] = {0};
    bool carry_out;
    
    ullong_to_bool(0, previous);
    ullong_to_bool(1, current);
    ullong_to_bool(1, one);
    
    write_word(&mem, 0, previous);
    write_word(&mem, 1, current);
    write_word(&mem, 2, one);
    
    for (int i = 1; i <= 20; i++) {
        read_word(&mem, 0, previous);
        read_word(&mem, 1, current);

        add64(previous, current, next, &carry_out);

        printf("F(%d) = %llu\n", i, bool_to_ullong(current));

        write_word(&mem, 0, current);
        write_word(&mem, 1, next);

        read_word(&mem, 2, counter);
        add64(counter, one, counter, &carry_out);
        write_word(&mem, 2, counter);
    }
}

int main() {
    fib();
    return 0;
}

