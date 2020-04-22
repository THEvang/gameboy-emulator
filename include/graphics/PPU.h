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

    void draw_scanline();
    void draw_background();
    void draw_sprites();

    const static int pixels_in_tile = 8;
    const static int vertical_tiles = 32;
    const static int horizontal_tiles = 32;

    int background_tile_number(const Screen_Position& screen_position) const {
        
        const auto tile_row = (screen_position.y / pixels_in_tile) * horizontal_tiles;
        const auto tile_column = screen_position.x / pixels_in_tile;
        return tile_row + tile_column;
    }

    uint16_t background_tile_identifier_address(int tile_number) const {
        
        uint16_t tile_map_address = m_lcd_control.background_tile_map_select() ? 0x9C00 : 0x9800;
        return tile_map_address + tile_number;
    }

    uint16_t tile_data_address(int tile_identifier_address) const {
    
        const auto tile_identifier = m_lcd_control.tile_data_signed() ? static_cast<int8_t>(m_memory_controller->read(tile_identifier_address)) :
            m_memory_controller->read(tile_identifier_address);

        const auto tile_data_start_address = m_lcd_control.tile_data_signed() ? 0x8800 : 0x9C00;
        const auto tile_data_offset = m_lcd_control.tile_data_signed() ? ((tile_identifier + 128) * 16) : tile_identifier * 16; 

        return tile_data_start_address + tile_data_offset;
    }

    const static int scanline_address = 0xFF44;

    MemoryBankController* m_memory_controller;

    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
    LCD_Status m_lcd_status;
    
    int m_scanline_counter = 0;

    Pixel_Array m_pixels;
};