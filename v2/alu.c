#include "gates.h"
#include "alu.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void print_binary(uint8_t byte) {
    printf("0b");
    for (int i = 7; i > 0; i--) {
        printf("%d", getBit(byte, i));
    }
}

uint8_t invert8(uint8_t byte) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        bool bit = !getBit(byte, i);
        result = writeBit(result, i, bit);
    }
    return result;
}

uint8_t full_adder_direct(bool a, bool b, bool cin) {
    
    bool sum = XOR(XOR(a, b), cin);

    bool carry = OR(AND(a, b), AND(cin, XOR(a, b)));

    return sum | (carry << 1);
}

uint8_t add8(uint8_t a, uint8_t b) {
    uint8_t sum = 0;
    bool carry = 0;

    for (int i = 0; i < 8; i++) {
        bool bitA = getBit(a, i);
        bool bitB = getBit(b, i);
        
        uint8_t result = full_adder_direct(bitA, bitB, carry);
        bool bitSum = getBit(result, 0);

        carry = getBit(result, 1);

        sum = writeBit(sum, i, bitSum);
    }
    return (uint8_t)sum | (carry ? 0x0100 : 0); 
}

uint8_t subtract8(uint8_t a, uint8_t b) {
    // a - b = a + (~b + 1)
    uint8_t neg_b = add8(invert8(b), 1);
    return add8(a, neg_b);
}

uint8_t right_shift(uint8_t byte, unsigned int pos) {
    pos &= 0x07;
    // while(pos >= 8) { pos = pos - 8; }    

    if(pos == 0) {
        return byte;
    }

    uint8_t result = 0;

    for(int i = 0; i < 8; i++) {
        int sourcePos = i + pos;

        if(sourcePos < 8) {
            bool bitValue = getBit(byte, sourcePos);
            result = writeBit(result, i, bitValue);
        }
    }
    return result;
}

uint8_t left_shift(uint8_t byte, unsigned int pos) {
    pos &= 0x07;

    if (pos == 0) {
        return byte;
    }

    uint8_t result = 0;

    for (int i = 7; i >= 0; i--) {
        int sourcePos = i - pos;

        if (sourcePos >= 0) {
            bool bitValue = getBit(byte, sourcePos);
            result = writeBit(result, i, bitValue);
        }
    }
    return result;
}
