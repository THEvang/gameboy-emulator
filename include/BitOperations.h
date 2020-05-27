#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

template <typename T>
constexpr T rotate_left(T value, std::size_t n) {

    static_assert(std::is_unsigned<T>(), "Bit rotation operands must be unsigned");

    return static_cast<T>((value << n) | (value >> (sizeof(T) * 8 - n)));
}

template <typename T>
constexpr T rotate_right(T value, std::size_t n) {

    static_assert(std::is_unsigned<T>(), "Bit rotation operands must be unsigned");

    return static_cast<T>((value >> n) | (value << (sizeof(T) * 8 - n)));
}

constexpr auto combine_bytes(uint8_t upper, uint8_t lower) -> uint16_t {
    return static_cast<uint16_t>((upper << 8U) | lower);
}

constexpr auto half_carry_8bit(uint8_t a, uint8_t b) -> bool {

    return ((a & 0xFU) + (b & 0xFU)) > 0xFU;
}

constexpr auto half_carry_16bit(uint16_t a, uint16_t b) -> bool {
    return ((a & 0xFFFU) + (b & 0xFFFU)) > 0xFFFU;
}

constexpr auto half_borrow_8bit(uint8_t a, uint8_t b) -> bool {
   return (a & 0xFU) < (b & 0xFU);
}

constexpr auto half_borrow_16bit(uint16_t a, uint16_t b) -> bool {
   return (a & 0xFFFU) < (b & 0xFFFU);
}

constexpr void set_bit(uint8_t& b, int n) {
    b |= static_cast<uint8_t>((1U << n));
}

constexpr void clear_bit(uint8_t& b, int n) {
    b &= static_cast<uint8_t>(~(1U << n));
}

constexpr auto is_set(uint8_t b, int n) -> bool {
    return ((1U << n) & b) != 0;
}

constexpr auto is_set(uint16_t b, int n) -> bool {
    return ((1U << n) & b) != 0;
}

constexpr auto overflows_8bit(uint8_t a, uint8_t b) -> bool {
    int sum = a + b;
    return sum > std::numeric_limits<uint8_t>::max();
}

constexpr auto overflows_16bit(uint16_t a, uint16_t b) -> bool {
    int sum = a + b;
    return sum > std::numeric_limits<uint16_t>::max();
}

constexpr auto underflows_8bit(uint8_t a, uint8_t b) -> bool {
    return b > a;
}

constexpr auto underflows_16bit(uint16_t a, uint16_t b) -> bool {
    return b > a;
}

constexpr void swap_nibbles(uint8_t& a) {
    a = static_cast<uint8_t>(( (a & 0x0FU) << 4U | (a & 0xF0U) >> 4U));
}