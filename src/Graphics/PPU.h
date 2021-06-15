#pragma once

#include "Graphics/Pixel.h"
#include "Memory/Memory_Controller.h"

#ifdef __cplusplus
extern "C" {
#endif

static const uint16_t g_scanline_address = 0xFF44;
static const int g_pixels_in_tile = 8;
static const int g_vertical_tiles = 32;
static const int g_horizontal_tiles = 32;

typedef struct PPU {
    Pixel_Array screen;
    MemoryBankController* memory_controller;
    int scanline_counter;
} PPU;

void gb_ppu_step(PPU* ppu, int cycles);
Color gb_get_color(uint8_t color_id, uint16_t palette_address, MemoryBankController* mc);
void gb_draw_scanline(PPU* ppu, MemoryBankController*);
void gb_draw_background(PPU* ppu, MemoryBankController*);
void gb_draw_sprites(PPU* ppu, MemoryBankController*);

#ifdef __cplusplus
}
#endif