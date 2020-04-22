#include "graphics/PPU.h"
#include "BitOperations.h"

PPU::PPU(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
    , m_interrupt_handler(m_memory_controller)
    , m_lcd_control(m_memory_controller)
    , m_lcd_status(m_memory_controller, m_lcd_control)
{}

void PPU::step(int cycles) {

    auto current_scanline = m_memory_controller->read(0xFF44);
    m_lcd_status.set_status(current_scanline, m_scanline_counter);

    if(!m_lcd_control.lcd_display_enabled()) {
        return;
    }

    m_scanline_counter -= cycles;

    if(m_scanline_counter <= 0) {
        
        current_scanline++;
        m_memory_controller->raw()->write(0xFF44, current_scanline);

        m_scanline_counter = 456;

        if(current_scanline == 144) {
            m_interrupt_handler.request_v_blank_interrupt();
        } else if (current_scanline > 153) {
            current_scanline = 0;
            m_memory_controller->write(0xFF44, current_scanline);
        } else if (current_scanline < 144) {
            draw_scanline();
        }
    }
};

void PPU::draw_scanline() {

    if(m_lcd_control.background_display_enabled()) {
        draw_background();
    }

    if(m_lcd_control.sprite_display_eanbled()) {
        draw_sprites();
    }
}

void PPU::draw_background() {

    constexpr auto scroll_y_address = 0xFF42; 
    constexpr auto scroll_x_address = 0xFF43;
    constexpr auto window_scroll_y_address = 0xFF4A;
    constexpr auto window_scroll_x_address = 0xFF4B;
    constexpr auto current_scanline_address = 0xFF44;

    const auto scanline = m_memory_controller->read(current_scanline_address);
    const auto y_pos = scanline + m_memory_controller->read(scroll_y_address);
    
    const auto x_scroll = m_memory_controller->read(scroll_x_address);

    constexpr auto horizontal_pixels = 160;
    for(int pixel = 0; pixel < horizontal_pixels; pixel++) {

        const auto x_pos = x_scroll + pixel;

        const Screen_Position screen_coordinates {x_pos, y_pos};
        const auto bg_tile_number = background_tile_number(screen_coordinates);
        const auto bg_tile_identifier_address = background_tile_identifier_address(bg_tile_number);
        const auto bg_tile_data_address = tile_data_address(bg_tile_identifier_address);    
        
        const auto tile_line = (screen_coordinates.y % 8) * 2;
        const auto data_1 = m_memory_controller->read(bg_tile_data_address + tile_line);
        const auto data_2 = m_memory_controller->read(bg_tile_data_address + tile_line + 1);
        
        auto color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const auto color_1 = is_set(data_1, color_bit);
        const auto color_2 = is_set(data_2, color_bit);
        
        auto color = 0;
        color += color_1 ? 2 : 0;
        color += color_2 ? 1 : 0;
        
        Color pixel_color {0xA0, 0xA0, 0xA0, 0xAA};
        m_pixels.set_pixel({pixel, scanline}, pixel_color);
    }
}

void PPU::draw_sprites() {

}