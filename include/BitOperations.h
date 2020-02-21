#pragma once

#include <cstdint>

template <typename T>
T rotate_left(T value, int n) {

    return (value << n) | (value >> (n - sizeof(T) * 8));
}

template <typename T>
T rotate_right(T value, int n) {

    return (value >> n) | (value << (n - sizeof(T) * 8));
}

uint16_t combine_bytes(uint8_t upper, uint8_t lower);