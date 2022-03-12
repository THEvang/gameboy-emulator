#pragma once

#include <stdint.h>

#include "Memory/Memory_Controller.h"

#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct PPU {
    uint32_t screen_buffer[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];
    uint32_t palette[4];
    int scanline_counter;
} PPU;

typedef enum Sprite_Attribute_Flags {
    BG_AND_WINDOW_OVER_OBJECT = 1 << 7,
    Y_FLIP = 1 << 6,
    X_FLIP = 1 << 5,
    PALETTE_NUMBER = 1 << 4
} Sprite_Attribute_Flags;

typedef struct Sprite_Attribute {
    uint8_t y_pos;
    uint8_t x_pos;
    uint8_t tile_location;
    uint8_t attributes;
    uint16_t oam_address;
} Sprite_Attribute;

void gb_ppu_step(PPU* ppu, MemoryBankController* mc, int cycles);
void gb_draw_scanline(PPU* ppu, MemoryBankController*);
void gb_draw_background(PPU* ppu, MemoryBankController*);
void gb_draw_sprites(PPU* ppu, MemoryBankController*);
uint32_t gb_get_color(uint8_t color_id, uint16_t palette_address, MemoryBankController* mc, PPU* ppu);
void gb_set_color(PPU* ppu, Point screen_coordinates, uint32_t color);