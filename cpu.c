#include<stdbool.h>
#include "memory.h"
#include "gates.h"
#include <stdio.h>
#include "alu.h"

void ullong_to_bool(unsigned long long n, bool word[64]);

unsigned long long bool_to_ullong(bool word[64]) {
    unsigned long long result = 0;
    for (int i = 0; i < 64; i++) {
        if (word[i]) {  
            unsigned long long mask = 1ULL << i;
            bool carry_out;
            bool result_bool[64];
            bool mask_bool[64];
            
            ullong_to_bool(result, result_bool);
            
            ullong_to_bool(mask, mask_bool);
            
            add64(result_bool, mask_bool, result_bool, &carry_out);
            
            result = 0;
            for (int j = 0; j < 64; j++) {
                if (word[j]) {
                    result |= (1ULL << j);
                }
            }
        }
    }
    return result;
}

void ullong_to_bool(unsigned long long n, bool word[64]) {
    for (int i = 0; i < 64; i++) {
        bool mask[64] = {0};
        mask[0] = true;
        
        bool temp[64];
        for (int j = 0; j < i; j++) {
            shift_left64(mask, temp);
            for (int k = 0; k < 64; k++) {
                mask[k] = temp[k];
            }
        }
        
        unsigned long long mask_val = 0;
        for (int j = 0; j < 64; j++) {
            if (mask[j]) {
                mask_val |= (1ULL << j);
            }
        }
        
        word[i] = AND((n & mask_val) != 0, true);
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
