#include "BitOperations.h"

uint8_t rotate_left(uint8_t value, size_t n) {
    return (uint8_t) ((value << n) | (value >> (sizeof(uint8_t) * 8 - n)));
}

uint8_t rotate_right(uint8_t value, size_t n) {
    return (uint8_t) ((value >> n) | (value << (sizeof(uint8_t) * 8 - n)));
}

uint16_t combine_bytes(uint8_t upper, uint8_t lower) {
    return (uint16_t) ((upper << 8U) | lower);
}

void set_bit(uint8_t* b, int n) {
    *b |= (uint8_t) ((1U << n));
}

void clear_bit(uint8_t* b, int n) {
    *b &= (uint8_t) (~(1U << n));
}

bool test_bit_8bit(uint8_t b, int n) {
    return ((1U << n) & b) != 0;
}

bool test_bit_16bit(uint16_t b, int n) {
    return ((1U << n) & b) != 0;
}

bool half_carry_8bit(uint8_t a, uint8_t b) {
    return ((a & 0xFU) + (b & 0xFU)) > 0xFU;
}

bool half_carry_16bit(uint16_t a, uint16_t b) {
    return ((a & 0xFFFU) + (b & 0xFFFU)) > 0xFFFU;
}

bool half_borrow_8bit(uint8_t a, uint8_t b) {
   return (a & 0xFU) < (b & 0xFU);
}

bool half_borrow_16bit(uint16_t a, uint16_t b) {
   return (a & 0xFFFU) < (b & 0xFFFU);
}

bool overflows_8bit(uint8_t a, uint8_t b) {
    int sum = a + b;
    return sum > 0xFF;
}

bool overflows_16bit(uint16_t a, uint16_t b) {
    int sum = a + b;
    return sum > ((1 << 16) - 1);
}

bool underflows_8bit(uint8_t a, uint8_t b) {
    return b > a;
}