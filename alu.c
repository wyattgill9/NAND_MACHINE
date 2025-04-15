#include "gates.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

void full_adder(bool a, bool b, bool cin, bool *sum, bool *cout) {
    bool ab_xor = XOR(a, b);
    *sum = XOR(ab_xor, cin);

    bool ab_and = AND(a, b);
    bool cin_abxor_and = AND(cin, ab_xor);
    *cout = OR(ab_and, cin_abxor_and);
}

void add64(bool A[64], bool B[64], bool sum[64], bool *carry_out) {
    bool c0 = 0;
    for (int i = 0; i < 64; ++i) {
        full_adder(A[i], B[i], c0, &sum[i], &c0);
    }
    *carry_out = c0;
}

void invert64(bool A[64], bool result[64]) {
    for (int i = 0; i < 64; ++i) {
        result[i] = NOT(A[i]);
    }
}

void add_one64(bool A[64], bool result[64], bool *carry_out) {
    bool one[64] = {0};
    one[0] = 1;
    add64(A, one, result, carry_out);
}

void sub64(bool A[64], bool B[64], bool result[64], bool *carry_out) {
    bool B_complement[64];
    bool B_plus_one[64];

    invert64(B, B_complement);
    
    add_one64(B_complement, B_plus_one, carry_out);
    
    add64(A, B_plus_one, result, carry_out);
}

void print_binary(bool arr[64]) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", arr[i]);
    }
}

int main() {
    bool A[64] = {
        1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1
    };
    bool B[64] = {
        0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0,
        1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1,
        0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0,
        1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1
    };

    bool result[64];
    bool carry_out;

    sub64(A, B, result, &carry_out);

    printf("A = ");
    print_binary(A);
    printf("\nB = ");
    print_binary(B);
    printf("\nResult (A - B) = ");
    print_binary(result);
    printf("\nCarry out = %d\n", carry_out);

    return 0;
}

