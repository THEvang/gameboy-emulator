#include "graphics/LCD_Status.h"

LCD_Status::LCD_Status(MemoryBankController* memory_controller, const LCD_Control& lcd_control)
    : m_memory_controller(memory_controller)
    , m_interrupt_handler(m_memory_controller)
    , m_lcd_control(lcd_control)
{}

void LCD_Status::set_status(int& scanline_counter) {
    
    constexpr uint16_t scanline_address = 0xFF44;
    if(!m_lcd_control.lcd_display_enabled()) {
        scanline_counter = 456;
        set_mode(LCD_Modes::V_Blank);
        m_memory_controller->write(scanline_address, 0);
        return;   
    }

    const auto current_mode = get_mode();
    const auto current_scanline = m_memory_controller->read(scanline_address);

    auto request_interrupt = false;
    
    auto status = m_memory_controller->read(status_address);
    if(current_scanline >= 144) {
        set_mode(LCD_Modes::V_Blank);
        request_interrupt = is_set(status, 4);
    } else {
        
        if(scanline_counter >= (456 - 80)) {
            set_mode(LCD_Modes::Searching_Sprite_Attributes);
            request_interrupt = is_set(status, 5);
        } else if(scanline_counter >= (456 - 80 - 172)) {
            set_mode(LCD_Modes::Transferring_Data);
        } else {
            set_mode(LCD_Modes::H_Blank);
            request_interrupt = is_set(status, 3);
        }
    }

    const auto new_mode = get_mode();

    if(request_interrupt && (current_mode != new_mode)) {
        m_interrupt_handler.request_lcd_stat_interrupt();
    }

    should_set_coincidence_flag() ? set_coincidence_flag() :
        clear_coincidence_flag();
}

bool LCD_Status::should_set_coincidence_flag() {
    return m_memory_controller->read(0xFF44) 
        == m_memory_controller->read(0xFF45);
}

void LCD_Status::set_coincidence_flag() {

    auto status = m_memory_controller->read(status_address);
    set_bit(status, coincidence_bit);
    m_memory_controller->write(status_address, status);
    if(is_set(status, 6)) {
        m_interrupt_handler.request_lcd_stat_interrupt();
    }
}

void LCD_Status::clear_coincidence_flag() {
    
    auto status = m_memory_controller->read(status_address);
    clear_bit(status, coincidence_bit);
    m_memory_controller->write(status_address, status);
}