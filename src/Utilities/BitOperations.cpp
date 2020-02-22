#include <BitOperations.h>

uint16_t combine_bytes(uint8_t upper, uint8_t lower) {
    return (upper << 8) | lower;
}

bool half_carry(uint8_t a, uint8_t b) {
    return (((a & 0xF) + (b & 0xF)) & 0x10) == 0x10;
}

void set_bit(uint8_t& b, int n) {
    b |= (1 << n);
}

void clear_bit(uint8_t& b, int n) {
    b &= ~(1 << n);
}

bool is_set(uint8_t b, int n) {
    return ((1 << n) & b) != 0;
}