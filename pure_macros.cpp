#include <bitset>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#define NAND(a, b) (!( (a) && (b) ))
#define NOT(a) (NAND(a, a))
#define AND(a, b) (NOT(NAND(a, b)))
#define OR(a, b) (NAND(NOT(a), NOT(b)))
#define NOR(a, b) (NOT(OR(a, b)))
#define XOR(a, b) (OR(AND((a), NOT(b)), AND(NOT(a), (b))))    
#define XNOR(a, b) (NOT(XOR(a, b)))        

#define FULL_ADDER(a, b, cin, sum_ptr, cout_ptr) \
    do { \
        bool _fa_ab_xor = XOR((a), (b)); \
        *(sum_ptr) = XOR(_fa_ab_xor, (cin)); \
        bool _fa_ab_and = AND((a), (b)); \
        bool _fa_cin_abxor_and = AND((cin), _fa_ab_xor); \
        *(cout_ptr) = OR(_fa_ab_and, _fa_cin_abxor_and); \
    } while (0)

#define REPEAT_64_TIMES(op, ...) \
    op(0, __VA_ARGS__) op(1, __VA_ARGS__) op(2, __VA_ARGS__) op(3, __VA_ARGS__) \
    op(4, __VA_ARGS__) op(5, __VA_ARGS__) op(6, __VA_ARGS__) op(7, __VA_ARGS__) \
    op(8, __VA_ARGS__) op(9, __VA_ARGS__) op(10, __VA_ARGS__) op(11, __VA_ARGS__) \
    op(12, __VA_ARGS__) op(13, __VA_ARGS__) op(14, __VA_ARGS__) op(15, __VA_ARGS__) \
    op(16, __VA_ARGS__) op(17, __VA_ARGS__) op(18, __VA_ARGS__) op(19, __VA_ARGS__) \
    op(20, __VA_ARGS__) op(21, __VA_ARGS__) op(22, __VA_ARGS__) op(23, __VA_ARGS__) \
    op(24, __VA_ARGS__) op(25, __VA_ARGS__) op(26, __VA_ARGS__) op(27, __VA_ARGS__) \
    op(28, __VA_ARGS__) op(29, __VA_ARGS__) op(30, __VA_ARGS__) op(31, __VA_ARGS__) \
    op(32, __VA_ARGS__) op(33, __VA_ARGS__) op(34, __VA_ARGS__) op(35, __VA_ARGS__) \
    op(36, __VA_ARGS__) op(37, __VA_ARGS__) op(38, __VA_ARGS__) op(39, __VA_ARGS__) \
    op(40, __VA_ARGS__) op(41, __VA_ARGS__) op(42, __VA_ARGS__) op(43, __VA_ARGS__) \
    op(44, __VA_ARGS__) op(45, __VA_ARGS__) op(46, __VA_ARGS__) op(47, __VA_ARGS__) \
    op(48, __VA_ARGS__) op(49, __VA_ARGS__) op(50, __VA_ARGS__) op(51, __VA_ARGS__) \
    op(52, __VA_ARGS__) op(53, __VA_ARGS__) op(54, __VA_ARGS__) op(55, __VA_ARGS__) \
    op(56, __VA_ARGS__) op(57, __VA_ARGS__) op(58, __VA_ARGS__) op(59, __VA_ARGS__) \
    op(60, __VA_ARGS__) op(61, __VA_ARGS__) op(62, __VA_ARGS__) op(63, __VA_ARGS__)

#define REPEAT_64_TIMES_REVERSE(op, ...) \
    op(63, __VA_ARGS__) op(62, __VA_ARGS__) op(61, __VA_ARGS__) op(60, __VA_ARGS__) \
    op(59, __VA_ARGS__) op(58, __VA_ARGS__) op(57, __VA_ARGS__) op(56, __VA_ARGS__) \
    op(55, __VA_ARGS__) op(54, __VA_ARGS__) op(53, __VA_ARGS__) op(52, __VA_ARGS__) \
    op(51, __VA_ARGS__) op(50, __VA_ARGS__) op(49, __VA_ARGS__) op(48, __VA_ARGS__) \
    op(47, __VA_ARGS__) op(46, __VA_ARGS__) op(45, __VA_ARGS__) op(44, __VA_ARGS__) \
    op(43, __VA_ARGS__) op(42, __VA_ARGS__) op(41, __VA_ARGS__) op(40, __VA_ARGS__) \
    op(39, __VA_ARGS__) op(38, __VA_ARGS__) op(37, __VA_ARGS__) op(36, __VA_ARGS__) \
    op(35, __VA_ARGS__) op(34, __VA_ARGS__) op(33, __VA_ARGS__) op(32, __VA_ARGS__) \
    op(31, __VA_ARGS__) op(30, __VA_ARGS__) op(29, __VA_ARGS__) op(28, __VA_ARGS__) \
    op(27, __VA_ARGS__) op(26, __VA_ARGS__) op(25, __VA_ARGS__) op(24, __VA_ARGS__) \
    op(23, __VA_ARGS__) op(22, __VA_ARGS__) op(21, __VA_ARGS__) op(20, __VA_ARGS__) \
    op(19, __VA_ARGS__) op(18, __VA_ARGS__) op(17, __VA_ARGS__) op(16, __VA_ARGS__) \
    op(15, __VA_ARGS__) op(14, __VA_ARGS__) op(13, __VA_ARGS__) op(12, __VA_ARGS__) \
    op(11, __VA_ARGS__) op(10, __VA_ARGS__) op(9, __VA_ARGS__) op(8, __VA_ARGS__) \
    op(7, __VA_ARGS__) op(6, __VA_ARGS__) op(5, __VA_ARGS__) op(4, __VA_ARGS__) \
    op(3, __VA_ARGS__) op(2, __VA_ARGS__) op(1, __VA_ARGS__) op(0, __VA_ARGS__)

#define ADD_STEP(i, lhs_bits, rhs_bits, result_bits, carry_array) \
    bool _sum_bit##i; \
    FULL_ADDER((lhs_bits)[i], (rhs_bits)[i], carry_array[i], &_sum_bit##i, &carry_array[i+1]); \
    (result_bits)[i] = _sum_bit##i;

#define SUB_STEP(i, lhs_bits, rhs_bits, result_bits, borrow_array) \
    bool _diff_bit##i; \
    bool _temp_not_rhs##i = NOT((rhs_bits)[i]); \
    FULL_ADDER((lhs_bits)[i], _temp_not_rhs##i, borrow_array[i], &_diff_bit##i, &borrow_array[i+1]); \
    (result_bits)[i] = _diff_bit##i;

#define ADD_BITS(lhs_bits, rhs_bits, result_bits) \
    do { \
        bool _carry[65] = {0}; \
        REPEAT_64_TIMES(ADD_STEP, lhs_bits, rhs_bits, result_bits, _carry) \
    } while (0)

#define SUB_BITS(lhs_bits, rhs_bits, result_bits) \
    do { \
        bool _borrow[65] = {1}; \
        REPEAT_64_TIMES(SUB_STEP, lhs_bits, rhs_bits, result_bits, _borrow) \
    } while (0)

#define BITWISE_OP(i, op_macro, lhs_bits, rhs_bits, result_bits) \
    (result_bits)[i] = op_macro((lhs_bits)[i], (rhs_bits)[i]);

#define UNARY_BITWISE_OP(i, op_macro, bits, result_bits) \
    (result_bits)[i] = op_macro((bits)[i]);

#define COMPARE_CHECK(i, lhs_bits, rhs_bits, found_diff, result) \
    if (!found_diff && (lhs_bits)[i] != (rhs_bits)[i]) { \
        found_diff = true; \
        result = (rhs_bits)[i] > (lhs_bits)[i]; \
    }

#define LEFT_SHIFT_SET_HIGH(i, bits, result_bits, n) \
    if (i >= n) (result_bits)[i] = (bits)[i - n];

#define LEFT_SHIFT_CLEAR_LOW(i, result_bits, n) \
    if (i < n) (result_bits)[i] = 0;

#define RIGHT_SHIFT_SET_LOW(i, bits, result_bits, n) \
    if (i < 64 - n) (result_bits)[i] = (bits)[i + n];

#define RIGHT_SHIFT_CLEAR_HIGH(i, result_bits, n) \
    if (i >= 64 - n) (result_bits)[i] = 0;

#define MULT_CONDITIONAL_ADD(i, result, lhs, rhs_bits, shift_temp) \
    if ((rhs_bits)[i]) { \
        shift_temp = lhs << i; \
        result = result + shift_temp; \
    }

#define DIV_SUBTRACT_IF_POSSIBLE(i, dividend, divisor, quotient, temp_sub) \
    temp_sub = dividend - (divisor << (63 - i)); \
    if (!(temp_sub > dividend)) { \
        dividend = temp_sub; \
        (quotient).bits[63 - i] = 1; \
    } else { \
        (quotient).bits[63 - i] = 0; \
    }

struct u64 {
    std::bitset<64> bits;    

    u64(uint64_t val = 0) : bits(val) {}
    
    u64& operator=(const u64& other) {
        bits = other.bits;
        return *this;
    }

    u64& operator+=(const u64& rhs) {
        *this = *this + rhs;
        return *this;
    }

    u64& operator-=(const u64& rhs) {
        *this = *this - rhs;
        return *this;
    }

    u64& operator*=(const u64& rhs) {
        *this = *this * rhs;
        return *this;
    }

    u64& operator/=(const u64& rhs) {
        *this = *this / rhs;
        return *this;
    }

    u64& operator%=(const u64& rhs) {
        *this = *this % rhs;
        return *this;
    }

    u64& operator&=(const u64& rhs) {
        *this = *this & rhs;
        return *this;
    }

    u64& operator|=(const u64& rhs) {
        *this = *this | rhs;
        return *this;
    }

    u64& operator^=(const u64& rhs) {
        *this = *this ^ rhs;
        return *this;
    }

    u64& operator<<=(int n) {
        *this = *this << n;
        return *this;
    }

    u64& operator>>=(int n) {
        *this = *this >> n;
        return *this;
    }

    u64& operator++() {
        *this += u64(1);
        return *this;
    }

    u64 operator++(int) {
        u64 temp = *this;
        ++(*this);
        return temp;
    }

    u64& operator--() {
        *this -= u64(1);
        return *this;
    }

    u64 operator--(int) {
        u64 temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const u64& lhs, const u64& rhs) {
        return lhs.bits == rhs.bits;
    }

    friend bool operator!=(const u64& lhs, const u64& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const u64& lhs, const u64& rhs) {
        bool found_diff = false;
        bool result = false;
        REPEAT_64_TIMES_REVERSE(COMPARE_CHECK, lhs.bits, rhs.bits, found_diff, result)
        return result;
    }

    friend bool operator>(const u64& lhs, const u64& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const u64& lhs, const u64& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>=(const u64& lhs, const u64& rhs) {
        return !(lhs < rhs);
    }

    u64 operator+() const {
        return *this;
    }

    u64 operator-() const {
        return (~(*this)) + u64(1);
    }

    u64 operator~() const {
        u64 result;
        REPEAT_64_TIMES(UNARY_BITWISE_OP, NOT, bits, result.bits)
        return result;
    }

    friend u64 operator+(const u64& lhs, const u64& rhs) {
        u64 result;
        ADD_BITS(lhs.bits, rhs.bits, result.bits);
        return result;
    }

    friend u64 operator-(const u64& lhs, const u64& rhs) {
        u64 result;
        SUB_BITS(lhs.bits, rhs.bits, result.bits);
        return result;
    }

    friend u64 operator*(const u64& lhs, const u64& rhs) {
        u64 result(0);
        u64 shift_temp;
        REPEAT_64_TIMES(MULT_CONDITIONAL_ADD, result, lhs, rhs.bits, shift_temp)
        return result;
    }

    friend u64 operator/(const u64& lhs, const u64& rhs) {
        if (rhs == u64(0)) return u64(0);
        if (lhs < rhs) return u64(0);
        if (lhs == rhs) return u64(1);
        
        u64 dividend = lhs;
        u64 quotient(0);
        u64 temp_sub;
        REPEAT_64_TIMES(DIV_SUBTRACT_IF_POSSIBLE, dividend, rhs, quotient, temp_sub)
        return quotient;
    }

    friend u64 operator%(const u64& lhs, const u64& rhs) {
        if (rhs == u64(0)) return u64(0);
        return lhs - (lhs / rhs) * rhs;
    }

    friend u64 operator&(const u64& lhs, const u64& rhs) {
        u64 result;
        REPEAT_64_TIMES(BITWISE_OP, AND, lhs.bits, rhs.bits, result.bits)
        return result;
    }

    friend u64 operator|(const u64& lhs, const u64& rhs) {
        u64 result;
        REPEAT_64_TIMES(BITWISE_OP, OR, lhs.bits, rhs.bits, result.bits)
        return result;
    }

    friend u64 operator^(const u64& lhs, const u64& rhs) {
        u64 result;
        REPEAT_64_TIMES(BITWISE_OP, XOR, lhs.bits, rhs.bits, result.bits)
        return result;
    }

    u64 operator<<(int n) const {
        u64 result;
        if (n >= 64) {
            result.bits.reset();
            return result;
        }
        REPEAT_64_TIMES(LEFT_SHIFT_SET_HIGH, bits, result.bits, n)
        REPEAT_64_TIMES(LEFT_SHIFT_CLEAR_LOW, result.bits, n)
        return result;
    }

    u64 operator>>(int n) const {
        u64 result;
        if (n >= 64) {
            result.bits.reset();
            return result;
        }
        REPEAT_64_TIMES(RIGHT_SHIFT_SET_LOW, bits, result.bits, n)
        REPEAT_64_TIMES(RIGHT_SHIFT_CLEAR_HIGH, result.bits, n)
        return result;
    }

    explicit operator bool() const {
        return bits.any();
    }

    explicit operator uint64_t() const {
        return bits.to_ullong();
    }

    friend std::ostream& operator<<(std::ostream& os, const u64& v) {
        return os << v.bits.to_ullong();
    }
};

// faster fib function
void fib_helper(u64 n, u64* fn, u64* fn1) {
    if (n == 0) {
        *fn = 0;
        *fn1 = 1;
        return;
    }

    u64 a, b;
    fib_helper(n >> 1, &a, &b);

    u64 c = a * (2 * b - a);
    u64 d = a * a + b * b;

    if ((n & 1) == 0) {
        *fn = c;
        *fn1 = d;
    } else {
        *fn = d;
        *fn1 = c + d;
    }
}

u64 fib(uint64_t n) {
    u64 fn, fn1;
    fib_helper(n, &fn, &fn1);
    return fn;
}

int main() {
    u64 a = 20;
    u64 b = 15;

    u64 c = a + b * ~a & (b << 2) | (a >> 1) ^ b;
    
    uint64_t _a = 20;
    uint64_t _b = 15;
    uint64_t _c = _a + _b * ~_a & (_b << 2) | (_a >> 1) ^ _b;

    assert(c == _c);

    std::cout << fib(93) << "\n";
    
    return 0;
}
