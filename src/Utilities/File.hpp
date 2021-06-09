#pragma once

#include <cstdint>

struct gb_Rom {
    uint8_t* data;
    size_t size;
};

void load_rom(gb_Rom* rom, const char* path);