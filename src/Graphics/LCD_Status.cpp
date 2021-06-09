#include "Graphics/LCD_Status.hpp"

#include "Memory/Memory_Controller.hpp"
#include "Utilities/BitOperations.hpp"

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
        request_interrupt = test_bit_8bit(status, 4);
    } else {
        
        if(scanline_counter >= (456 - 80)) {
            set_mode(LCD_Modes::Searching_Sprite_Attributes);
            request_interrupt = test_bit_8bit(status, 5);
        } else if(scanline_counter >= (456 - 80 - 172)) {
            set_mode(LCD_Modes::Transferring_Data);
        } else {
            set_mode(LCD_Modes::H_Blank);
            request_interrupt = test_bit_8bit(status, 3);
        }
    }

    const auto new_mode = get_mode();

    if(request_interrupt && (current_mode != new_mode)) {
        m_interrupt_handler.request(Interrupts::LCD_STAT);
    }

    should_set_coincidence_flag() ? set_coincidence_flag() :
        clear_coincidence_flag();
}

bool LCD_Status::should_set_coincidence_flag() const {
    return m_memory_controller->read(0xFF44) 
        == m_memory_controller->read(0xFF45);
}

void LCD_Status::set_coincidence_flag() {

    auto status = m_memory_controller->read(status_address);
    set_bit(&status, coincidence_bit);
    m_memory_controller->write(status_address, status);
    if(test_bit_8bit(status, 6)) {
        m_interrupt_handler.request(Interrupts::LCD_STAT);
    }
}

void LCD_Status::clear_coincidence_flag() {
    
    auto status = m_memory_controller->read(status_address);
    clear_bit(&status, coincidence_bit);
    m_memory_controller->write(status_address, status);
}


LCD_Modes LCD_Status::get_mode() const {
        auto status = m_memory_controller->read(status_address);
        status &= 0x03;
        switch (status ) {
            case 0: 
                return LCD_Modes::H_Blank;
            case 1:
                return LCD_Modes::V_Blank;
            case 2:
                return LCD_Modes::Searching_Sprite_Attributes;
            case 3:
                return LCD_Modes::Transferring_Data;
            default:
                return LCD_Modes::H_Blank;
        }
}

void LCD_Status::set_mode(const LCD_Modes& mode) {

    auto status = m_memory_controller->read(status_address);

    switch(mode) {
        case LCD_Modes::H_Blank:
            clear_bit(&status, 0);
            clear_bit(&status, 1);
        break;

        case LCD_Modes::V_Blank:
            set_bit(&status, 0);
            clear_bit(&status, 1);
        break;

        case LCD_Modes::Searching_Sprite_Attributes:
            clear_bit(&status, 0);
            set_bit(&status, 1);
        break;

        case LCD_Modes::Transferring_Data:
            set_bit(&status, 0);
            set_bit(&status, 1);
        break;
    }
    m_memory_controller->write(status_address, status);
}
