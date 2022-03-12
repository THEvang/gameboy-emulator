#pragma once

#include <stdint.h>

#include "Memory/Memory_Controller.h"

#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

typedef struct Point {
    uint8_t x;
    uint8_t y;
} Point;

typedef struct Color {  
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha; 
} Color;

typedef struct PPU {
    int32_t screen_buffer[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];
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
Color gb_get_color(uint8_t color_id, uint16_t palette_address, MemoryBankController* mc);
void gb_draw_scanline(PPU* ppu, MemoryBankController*);
void gb_draw_background(PPU* ppu, MemoryBankController*);
void gb_draw_sprites(PPU* ppu, MemoryBankController*);
void gb_set_pixel(PPU* arr, Point screen_position, Color color);