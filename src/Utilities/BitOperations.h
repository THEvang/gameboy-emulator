#pragma once

#include <stdint.h>
#include <stdbool.h>

uint8_t rotate_left(uint8_t value, size_t n);
uint8_t rotate_right(uint8_t value, size_t n);

uint16_t combine_bytes(uint8_t upper, uint8_t lower);

void set_bit(uint8_t* b, int n);
void clear_bit(uint8_t* b, int n);

bool test_bit_8bit(uint8_t b, int n);
bool test_bit_16bit(uint16_t b, int n);

bool half_carry_8bit(uint8_t a, uint8_t b);
bool half_carry_16bit(uint16_t a, uint16_t b);

bool half_borrow_8bit(uint8_t a, uint8_t b);
bool half_borrow_16bit(uint16_t a, uint16_t b);

bool overflows_8bit(uint8_t a, uint8_t b);
bool overflows_16bit(uint16_t a, uint16_t b);

bool underflows_8bit(uint8_t a, uint8_t b);
bool underflows_16bit(uint16_t a, uint16_t b);

void swap_nibbles(uint8_t* a);