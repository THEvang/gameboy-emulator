#pragma once

#include "Memory/Memory_Controller.h"
#include "cpu/Interrupt_Handler.h"
#include "graphics/LCD_Control.h"
#include "BitOperations.h"

enum class LCD_Modes {
    H_Blank,
    V_Blank,
    Searching_Sprite_Attributes,
    Transferring_Data
};

class LCD_Status {
public:
    LCD_Status(MemoryBankController* memory_controller, 
        const LCD_Control& lcd_control);

    void set_status(int& scanline_counter);

private:

    LCD_Modes get_mode() const;
    void set_mode(const LCD_Modes& mode);

    bool should_set_coincidence_flag() const;
    void set_coincidence_flag();
    void clear_coincidence_flag();

    const uint16_t status_address = 0xFF41;
    static const int coincidence_bit = 2;

    MemoryBankController* m_memory_controller;
    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
};