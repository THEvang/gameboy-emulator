#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gb_Rom {
    uint8_t* data;
    size_t size;
} gb_Rom;

void load_rom(gb_Rom* rom, const char* path);

#ifdef __cplusplus
}
#endif