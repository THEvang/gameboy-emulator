#include "graphics/LCD_Status.h"
#include "BitOperations.h"

LCD_Status::LCD_Status(MemoryBankController* memory_controller, const LCD_Control& lcd_control)
    : m_memory_controller(memory_controller)
    , m_interrupt_handler(m_memory_controller)
    , m_lcd_control(lcd_control)
{}

void LCD_Status::set_status(int& scanline_counter) {
    
    auto status = m_memory_controller->read(status_address);

    if(!m_lcd_control.lcd_display_enabled()) {
        scanline_counter = 456;
        status &= 252;
        set_bit(status, 0);
        m_memory_controller->write(status_address, status);
        m_memory_controller->raw()->write(0xFF44, 0);
        return;   
    }

    const auto current_mode = status & 0x3;
    const auto current_scanline = m_memory_controller->read(0xFF44);

    auto request_interrupt = false;
    if(current_scanline >= 144) {
        set_vertical_blank();
        request_interrupt = is_set(status, 4);
    } else {
        
        if(scanline_counter >= (456 - 80)) {
            set_searching_sprites();
            request_interrupt = is_set(status, 5);
        } else if(scanline_counter >= (456 - 80 - 172)) {
            set_data_transfer();
        } else {
            set_horizontal_blank();
            request_interrupt = is_set(status, 3);
        }
    }

    const auto new_mode = m_memory_controller->read(status_address) & 0x3;

    if(request_interrupt && (current_mode != new_mode)) {
        m_interrupt_handler.request_lcd_stat_interrupt();
    }

    should_set_coincidence_flag() ? set_coincidence_flag() :
        clear_coincidence_flag();
}

void LCD_Status::set_horizontal_blank() {
    
    auto status = m_memory_controller->read(status_address);
    clear_bit(status, 0);
    clear_bit(status, 1);
    m_memory_controller->write(status_address, status);
}

void LCD_Status::set_vertical_blank() {

    auto status = m_memory_controller->read(status_address);
    set_bit(status, 0);
    clear_bit(status, 1);
    m_memory_controller->write(status_address, status);
}

void LCD_Status::set_searching_sprites() {
    
    auto status = m_memory_controller->read(status_address);
    clear_bit(status, 0);
    set_bit(status, 1);
    m_memory_controller->write(status_address, status);
}

void LCD_Status::set_data_transfer() {
    
    auto status = m_memory_controller->read(status_address);
    set_bit(status, 0);
    set_bit(status, 1);
    m_memory_controller->write(status_address, status);
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