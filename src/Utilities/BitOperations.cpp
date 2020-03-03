#include <BitOperations.h>
#include <limits>

auto combine_bytes(uint8_t upper, uint8_t lower) -> uint16_t {
    const uint16_t a = upper;
    const uint16_t b = lower;
    const uint16_t result = (a << 8) | b;
    return result;
}

auto half_carry_8bit(uint8_t a, uint8_t b) -> bool {

    return ((a & 0xF) + (b & 0xF)) > 0xF;
}

auto half_carry_16bit(uint16_t a, uint16_t b) -> bool {

    return ((a & 0xFFF) + (b & 0xFFF)) > 0xFFF;
}

auto half_borrow_8bit(uint8_t a, uint8_t b) -> bool {
   return (a & 0xF) < (b & 0xF);
}

auto half_borrow_16bit(uint16_t a, uint16_t b) -> bool {
   return (a & 0xFFF) < (b & 0xFFF);
}

void set_bit(uint8_t& b, int n) {
    b |= (1 << n);
}

void clear_bit(uint8_t& b, int n) {
    b &= ~(1 << n);
}

auto is_set(uint8_t b, int n) -> bool {
    return ((1 << n) & b) != 0;
}

auto overflows_8bit(uint8_t a, uint8_t b) -> bool {
    int sum = a + b;
    return sum > std::numeric_limits<uint8_t>::max();
};

auto overflows_16bit(uint16_t a, uint16_t b) -> bool {
    int sum = a + b;
    return sum > std::numeric_limits<uint16_t>::max();
};

auto underflows_8bit(uint8_t a, uint8_t b) -> bool {
    return b > a;
}

auto underflows_16bit(uint16_t a, uint16_t b) -> bool {
    return b > a;
}

void swap_nibbles(uint8_t& a) {
    a = ( (a & 0x0F) << 4 | (a & 0xF0) >> 4 );
}