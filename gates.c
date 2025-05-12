#include<stdbool.h>
#include "gates.h"

bool NAND(bool a, bool b){
    // NAND is the fundamental gate, so we can't build it from other gates
    // Therefore we must use the built-in ! and && operators here
    return !(a && b);
}

bool NOT(bool a){
    return NAND(a, a);
}

bool AND(bool a, bool b){
    return NOT(NAND(a, b));
}

bool OR(bool a, bool b){
    return NAND(NOT(a), NOT(b));
}

bool NOR(bool a, bool b){
    return NOT(OR(a, b));
}

bool XOR(bool a, bool b) {
    bool t1 = AND(a, NOT(b));
    bool t2 = AND(NOT(a), b);
    return OR(t1, t2);
}

bool XNOR(bool a, bool b){
    return NOT(XOR(a, b));
}
