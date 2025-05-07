#ifndef ALU_H
#define ALU_H

#include<stdint.h>
#include<stdbool.h>

uint8_t setBit(uint8_t byte, int pos);
uint8_t NOT(uint8_t a);
uint8_t AND(uint8_t a, uint8_t b);
uint8_t OR(uint8_t a, uint8_t b);
uint8_t NOR(uint8_t a, uint8_t b);
uint8_t XOR(uint8_t a, uint8_t b);
uint8_t XNOR(uint8_t a, uint8_t b);

uint8_t setBit(uint8_t byte, int pos);
uint8_t clearBit(uint8_t byte, int pos);
uint8_t toggleBit(uint8_t byte, int pos);
bool getBit(uint8_t byte, int pos);
uint8_t writeBit(uint8_t byte, int pos, bool value);

#endif
