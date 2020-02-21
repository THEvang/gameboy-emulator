#include <BitOperations.h>

uint16_t combine_bytes(uint8_t upper, uint8_t lower) {
    return (upper << 8) | lower;
}