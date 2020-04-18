#pragma once

#include "memory_controllers/MemoryBankController.h"
#include "cpu/Interrupt_Handler.h"
#include "graphics/LCD_Control.h"

class LCD_Status {
public:
    LCD_Status(MemoryBankController* memory_controller, 
        LCD_Control lcd_control);

    void set_status(uint8_t& current_scanline, int& scanline_counter);

    void set_horizontal_blank();
    void set_vertical_blank();
    void set_searching_sprites();
    void set_data_transfer();

private:

    bool should_set_coincidence_flag();
    void set_coincidence_flag();
    void clear_coincidence_flag();

    const uint16_t status_address = 0xFF41;
    static const int coincidence_bit = 2;

    MemoryBankController* m_memory_controller;
    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
};