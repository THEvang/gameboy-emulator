#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

template <typename T>
T rotate_left(T value, std::size_t n) {

    static_assert(std::is_unsigned<T>(), "Bit rotation operands must be unsigned");

    return static_cast<T>((value << n) | (value >> (sizeof(T) * 8 - n)));
}

template <typename T>
T rotate_right(T value, std::size_t n) {

    static_assert(std::is_unsigned<T>(), "Bit rotation operands must be unsigned");

    return static_cast<T>((value >> n) | (value << (sizeof(T) * 8 - n)));
}

void set_bit(uint8_t& b, int n);
void clear_bit(uint8_t& b, int n);

bool is_set(uint8_t b, int n);
bool is_set(uint16_t b, int n);

uint16_t combine_bytes(uint8_t upper, uint8_t lower);
bool half_carry_8bit(uint8_t a, uint8_t b);
bool half_carry_16bit(uint16_t a, uint16_t b);

bool half_borrow_8bit(uint8_t a, uint8_t b);
bool half_borrow_16bit(uint16_t a, uint16_t b);

bool overflows_8bit(uint8_t a, uint8_t b);
bool overflows_16bit(uint16_t a, uint16_t b);

bool underflows_8bit(uint8_t a, uint8_t b);
auto underflows_16bit(uint16_t a, uint16_t b) -> bool;

void swap_nibbles(uint8_t& a);