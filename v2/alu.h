#ifndef ALU_H
#define ALU_H

#include <stdint.h>
// #include <stdbool.h>

void print_binary(uint8_t byte);
uint8_t invert8(uint8_t byte);

// uint8_t full_adder_direct(bool a, bool b, bool cin);
uint8_t add8(uint8_t a, uint8_t b);
uint8_t subtract8(uint8_t a, uint8_t b);
uint8_t right_shift(uint8_t byte, unsigned int pos);
uint8_t left_shift(uint8_t byte, unsigned int pos);


#endif
