#pragma once

#include "Graphics/Pixel.hpp"
#include "Memory/Memory_Controller.h"

class PPU {
public:
    PPU(MemoryBankController* memory_controller);

    void step(int cycles);

    Pixel_Array screen;

private:

    Color get_color(uint8_t color_id, uint16_t palette_address);

    void draw_scanline();
    void draw_background();
    void draw_sprites();

    const static uint16_t scroll_y_address = 0xFF42; 
    const static uint16_t scroll_x_address = 0xFF43;
    const static uint16_t window_scroll_y_address = 0xFF4A;
    const static uint16_t window_scroll_x_address = 0xFF4B;
    const static uint16_t scanline_address = 0xFF44;

    const static auto pixels_in_tile = 8;
    const static auto vertical_tiles = 32;
    const static auto horizontal_tiles = 32;

    MemoryBankController* m_memory_controller;
    
    int m_scanline_counter = 0;
};