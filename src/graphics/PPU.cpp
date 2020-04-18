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
        m_memory_controller->write(current_scanline, 0xFF44);

        m_scanline_counter = 456;

        if(current_scanline == 144) {
            m_interrupt_handler.request_v_blank_interrupt();
        } else if (current_scanline > 153) {
            current_scanline = 0;
            m_memory_controller->write(current_scanline, 0xFF44);
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

    constexpr auto memory_start = 0x8000;
    constexpr auto tile_size = 16;

    const auto scanline = m_memory_controller->read(current_scanline_address);
    const auto y_pos = scanline + m_memory_controller->read(scroll_y_address);
    
    const auto x_scroll = m_memory_controller->read(scroll_x_address);

    const auto tile_row = (y_pos / 8) * 32;

    const auto background_address = m_lcd_control.tile_map_start_address();
    const auto tile_data = m_lcd_control.tile_data_start_address();

    constexpr auto horizontal_pixels = 160;

    for(int pixel = 0; pixel < horizontal_pixels; pixel++) {

        const auto x_pos = x_scroll + pixel;

        const auto tile_column = x_pos / 8;
        const auto tile_address = background_address + tile_column + tile_row;
        const auto tile_number = m_lcd_control.tile_data_signed() ? static_cast<int8_t>(m_memory_controller->read(tile_address)) :
            m_memory_controller->read(tile_address);

        auto tile_location = tile_data;
        tile_location += m_lcd_control.tile_data_signed() ? ((tile_number + 128) * 16) : tile_number * 16; 

        const auto tile_line = (y_pos % 8) * 2;
        const auto data_1 = m_memory_controller->read(tile_location + tile_line);
        const auto data_2 = m_memory_controller->read(tile_location + tile_line + 1);

        auto color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        const auto color_1 = is_set(data_1, color_bit);
        const auto color_2 = is_set(data_2, color_bit);
        
        auto color = 0;
        color += color_1 ? 2 : 0;
        color += color_2 ? 1 : 0;

        m_screen[pixel][scanline] = color;
    }
}

void PPU::draw_sprites() {

}