#ifndef ALU_H
#define ALU_H

#include <stdbool.h>

void full_adder(bool a, bool b, bool cin, bool *sum, bool *cout);

void add64(bool A[64], bool B[64], bool sum[64], bool *carry_out);
void invert64(bool A[64], bool result[64]);
void add_one64(bool A[64], bool result[64], bool *carry_out);
void sub64(bool A[64], bool B[64], bool result[64], bool *carry_out);
void shift_left64(bool A[64], bool result[64]);
void shift_right64(bool A[64], bool result[64]);
void mult64(bool A[64], bool B[64], bool result[64], bool *carry_out);

void print_binary(bool arr[64]);

#endif
