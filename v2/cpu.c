#include "alu.h"
#include "memory.h"
#include <stdio.h>

void test_add_sub() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            uint8_t a = i;
            uint8_t b = j;
            uint8_t sum = add8(a, b);
            uint8_t diff = subtract8(a, b);

            printf("a = %02d, b = %02d => a+b = %03d, a-b = %03d\n", a, b, sum, diff);
        }
    }
}

int main() {
    test_add_sub();
    return 0;
}
