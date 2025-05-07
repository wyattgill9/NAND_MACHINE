#include <stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include <sys/types.h>
#include "gates.h"

uint8_t setBit(uint8_t byte, int pos) {
    return byte | (1 << pos);
}

uint8_t clearBit(u_int8_t byte, int pos) {
    return byte & ~(1 << pos);
}

uint8_t toggleBit(uint8_t byte, int pos) {
    return byte ^ (1 << pos);
} 

bool getBit(uint8_t byte, int pos) {
    return (byte >> pos) & 1;
}

uint8_t writeBit(uint8_t byte, int pos, bool value) {
    return value ? setBit(byte, pos) : clearBit(byte, pos);
}

uint8_t NAND(uint8_t a, uint8_t b) {
    return ~(a & b);
}

uint8_t NOT(uint8_t a) {
    return NAND(a, a);
}

uint8_t AND(uint8_t a, uint8_t b) {
    return NOT(NAND(a, b)); 
}

uint8_t OR(uint8_t a, uint8_t b) {
    return NAND(NOT(a), NOT(b)); 
}

uint8_t NOR(uint8_t a, uint8_t b) {
    return NOT(OR(a, b));
}

uint8_t XOR(uint8_t a, uint8_t b) {
    return NAND(NAND(a, NAND(a, b)), NAND(b, NAND(a, b)));
}

uint8_t XNOR(uint8_t a, uint8_t b) {
    return NOT(XOR(a, b)); 
}

// void run_tests() {
//     uint8_t test_values[][2] = {
//         {0x00, 0x00}, {0xFF, 0xFF}, {0x55, 0xAA},
//         {0xAA, 0x55}, {0x0F, 0xF0}, {0xF0, 0x0F},
//         {0x01, 0x80}, {0x33, 0xCC}, {0x12, 0x34}
//     };
//
//     for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
//         uint8_t a = test_values[i][0];
//         uint8_t b = test_values[i][1];
//
//         // assert(NOT(a) == ~a);
//         // assert(AND(a, b) == (a & b));
//         // assert(OR(a, b) == (a | b));
//         // assert(NAND(a, b) == ~(a & b));
//         // assert(NOR(a, b) == ~(a | b));
//         // assert(XOR(a, b) == (a ^ b));
//         // assert(XNOR(a, b) == ~(a ^ b));
//
//         assert(NOT(NOT(a)) == a);
//         assert(OR(a, a) == a);
//         assert(AND(a, a) == a);
//         assert(XOR(a, a) == 0);
//         assert(XNOR(a, a) == 0xFF);
//
//         assert(AND(a, 0) == 0);
//         assert(AND(a, 0xFF) == a);
//         assert(OR(a, 0) == a);
//         assert(OR(a, 0xFF) == 0xFF);
//         assert(XOR(a, 0) == a);
//     }
//
//     uint8_t byte = 0x00;
//     for (int pos = 0; pos < 8; pos++) {
//         uint8_t expected = 1 << pos;
//         assert(setBit(byte, pos) == expected);
//         assert(getBit(expected, pos) == 1);
//
//         for (int other_pos = 0; other_pos < 8; other_pos++) {
//             if (other_pos != pos) {
//                 assert(getBit(expected, other_pos) == 0);
//             }
//         }
//     }
//
//     byte = 0xFF;
//     for (int pos = 0; pos < 8; pos++) {
//         uint8_t expected = byte & ~(1 << pos);
//         assert(clearBit(byte, pos) == expected);
//         assert(getBit(expected, pos) == 0);
//
//         for (int other_pos = 0; other_pos < 8; other_pos++) {
//             if (other_pos != pos) {
//                 assert(getBit(expected, other_pos) == 1);
//             }
//         }
//     }
//
//     byte = 0xAA;  // 10101010
//     for (int pos = 0; pos < 8; pos++) {
//         uint8_t expected = byte ^ (1 << pos);
//         assert(toggleBit(byte, pos) == expected);
//         assert(getBit(expected, pos) != getBit(byte, pos));
//     }
//
//     byte = 0x00;
//     uint8_t pattern = 0xA5;  // 10100101
//     for (int pos = 0; pos < 8; pos++) {
//         bool bit_value = (pattern >> pos) & 1;
//         byte = writeBit(byte, pos, bit_value);
//         assert(getBit(byte, pos) == bit_value);
//     }
//     assert(byte == pattern);
//
//     printf("Tests passed\n");
// }
