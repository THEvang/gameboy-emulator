#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct gb_Rom {
    uint8_t* data;
    size_t size;
} gb_Rom;

void load_rom(gb_Rom* rom, const char* path);