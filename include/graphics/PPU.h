#pragma once
#include "graphics/LCD_Status.h"
#include "cpu/Interrupt_Handler.h"
#include "memory_controllers/MBC1.h"
#include "graphics/Pixel.h"

class PPU {
public:
    PPU(MemoryBankController* memory_controller);

    void step(int cycles);

    auto screen() {
        return m_pixels;
    }

private:

    Color get_color(int color_id, uint16_t palette_address);

    void draw_scanline();
    void draw_background();
    void draw_sprites();

    const static auto scroll_y_address = 0xFF42; 
    const static auto scroll_x_address = 0xFF43;
    const static auto window_scroll_y_address = 0xFF4A;
    const static auto window_scroll_x_address = 0xFF4B;
    const static auto scanline_address = 0xFF44;

    const static auto pixels_in_tile = 8;
    const static auto vertical_tiles = 32;
    const static auto horizontal_tiles = 32;

    int tile_number(const Screen_Position& screen_position) const;

    uint16_t tile_data_address(int tile_identifier_address) const;

    MemoryBankController* m_memory_controller;

    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
    LCD_Status m_lcd_status;
    
    int m_scanline_counter = 0;

    Pixel_Array m_pixels;
};