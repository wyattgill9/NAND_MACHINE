#ifndef GATES_H
#define GATES_H

#include<stdbool.h>

bool AND(bool a, bool b);
bool OR(bool a, bool b);
bool NOT(bool a);
bool XOR(bool a, bool b);
bool NAND(bool a, bool b);
bool NOR(bool a, bool b);
bool XNOR(bool a, bool b);

// int ANDN(int n, const int* inputs);
// int ORN(int n, const int* inputs);

#endif
