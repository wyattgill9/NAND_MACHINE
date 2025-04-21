#include "gates.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "alu.h"

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

void shift_left64(bool A[64], bool result[64]) {
    for (int i = 0; i < 63; ++i) {
        result[i] = A[i + 1];
    }
    result[63] = 0;
}

void shift_right64(bool A[64], bool result[64]) {
    for (int i = 1; i < 64; ++i) {
        result[i - 1] = A[i];
    }
    result[63] = 0;
}

void mult64(bool A[64], bool B[64], bool result[64], bool *carry_out) {
    bool temp_A[64];
    bool temp_result[64] = {0};

    *carry_out = 0;

    for (int i = 0; i < 64; ++i) {
        if (AND(B[i], 1)) {
            add64(temp_result, A, result, carry_out);
        }

        shift_left64(A, temp_A);
        for (int j = 0; j < 64; ++j) {
            A[j] = temp_A[j];
        }
    }
}

void div64(bool A[64], bool B[64], bool quotient[64], bool remainder[64], bool *error) {
    bool is_B_zero = true;
    for (int i = 0; i < 64; i++) {
        if (B[i]) {
            is_B_zero = false;
            break;
        }
    }
    
    if (is_B_zero) {
        *error = true;
        // Clear quotient and remainder
        for (int i = 0; i < 64; i++) {
            quotient[i] = false;
            remainder[i] = false;
        }
        return;
    }
    
    *error = false;
    
    for (int i = 0; i < 64; i++) {
        quotient[i] = false;
        remainder[i] = A[i];
    }
    
    for (int i = 63; i >= 0; i--) {
        bool temp_remainder[64];
        shift_left64(remainder, temp_remainder);
        for (int j = 0; j < 64; j++) {
            remainder[j] = temp_remainder[j];
        }
        
        bool temp[64];
        bool borrow;
        sub64(remainder, B, temp, &borrow);
        
        if (!borrow) {
            quotient[i] = true;
            
            for (int j = 0; j < 64; j++) {
                remainder[j] = temp[j];
            }
        }
    }
}

void mod64(bool A[64], bool B[64], bool result[64], bool *error) {

    bool quotient[64];
    
    div64(A, B, quotient, result, error);
    
} 
void mov64(bool src[64], bool dest[64]) {
    for (int i = 0; i < 64; i++) {
        dest[i] = src[i];
    }
}

void print_binary(bool arr[64]) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", arr[i]);
    }
}

void and64(bool A[64], bool B[64], bool result[64]) {
    for (int i = 0; i < 64; i++) {
        result[i] = AND(A[i], B[i]);
    }
}

void or64(bool A[64], bool B[64], bool result[64]) {
    for (int i = 0; i < 64; i++) {
        result[i] = OR(A[i], B[i]);
    }
}

void xor64(bool A[64], bool B[64], bool result[64]) {
    for (int i = 0; i < 64; i++) {
        result[i] = XOR(A[i], B[i]);
    }
}

void clear64(bool A[64]) {
    for (int i = 0; i < 64; i++) {
        A[i] = 0;
    }
}

bool equals64(bool A[64], bool B[64]) {
    for (int i = 0; i < 64; i++) {
        if (A[i] != B[i]) {
            return false;
        }
    }
    return true;
}

bool is_zero64(bool A[64]) {
    for (int i = 0; i < 64; i++) {
        if (A[i]) {
            return false;
        }
    }
    return true;
}
