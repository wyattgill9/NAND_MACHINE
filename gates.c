#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

bool NAND(bool a, bool b){
    return !(a && b);
}

// nand only gates
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

bool XOR(bool a, bool b){
    bool t1 = NAND(a, b);
    bool t2 = NAND(a, t1);
    bool t3 = NAND(b, t1);
    return NAND(t2, t3);
}

bool XNOR(bool a, bool b){
    return NOT(XOR(a, b));
}

// int ANDN(int n, const int* inputs) {
//     int result = 1;
//     for (int i = 0; i < n; i++) {
//         result &= inputs[i];
//     }
//     return result;
// }
//
// int ORN(int n, const int* inputs) {
//     int result = 0;
//     for (int i = 0; i < n; i++) {
//         result |= inputs[i];
//     }
//     return result;
// }

void run_tests() {
    // NOT
    assert(NOT(true) == false);
    assert(NOT(false) == true);

    // AND
    assert(AND(false, false) == false);
    assert(AND(false, true) == false);
    assert(AND(true, false) == false);
    assert(AND(true, true) == true);

    // OR
    assert(OR(false, false) == false);
    assert(OR(false, true) == true);
    assert(OR(true, false) == true);
    assert(OR(true, true) == true);

    // NOR
    assert(NOR(false, false) == true);
    assert(NOR(false, true) == false);
    assert(NOR(true, false) == false);
    assert(NOR(true, true) == false);

    // XOR
    assert(XOR(false, false) == false);
    assert(XOR(false, true) == true);
    assert(XOR(true, false) == true);
    assert(XOR(true, true) == false);

    // XNOR
    assert(XNOR(false, false) == true);
    assert(XNOR(false, true) == false);
    assert(XNOR(true, false) == false);
    assert(XNOR(true, true) == true);

    printf("All tests passed!\n");
}

int main(){
    run_tests();
    return 0;
}
