#pragma once

#include <cstdint>
#include <limits>

template <typename T>
T rotate_left(T value, int n) {

    return (value << n) | (value >> (n - sizeof(T) * 8));
}

template <typename T>
T rotate_right(T value, int n) {

    return (value >> n) | (value << (n - sizeof(T) * 8));
}

void set_bit(uint8_t& b, int n);
void clear_bit(uint8_t& b, int n);

bool is_set(uint8_t b, int n);

uint16_t combine_bytes(uint8_t upper, uint8_t lower);
bool half_carry_8bit(uint8_t a, uint8_t b);
bool half_carry_16bit(uint16_t a, uint16_t b);

bool half_borrow_8bit(uint8_t a, uint8_t b);
bool half_borrow_16bit(uint16_t a, uint16_t b);

bool overflows_8bit(uint8_t a, uint8_t b);
bool overflows_16bit(uint16_t a, uint16_t b);

bool underflows_8bit(uint8_t a, uint8_t b);