#pragma once

#include "memory_controllers/MemoryBankController.h"
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

    void set_horizontal_blank();
    void set_vertical_blank();
    void set_searching_sprites();
    void set_data_transfer();

private:

    LCD_Modes get_mode() {
        const auto status = m_memory_controller->read(status_address);
        switch (status) {
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

    void set_mode(const LCD_Modes& mode) {

        auto status = m_memory_controller->read(status_address);

        switch(mode) {
            case LCD_Modes::H_Blank:
                clear_bit(status, 0);
                clear_bit(status, 1);
            break;

            case LCD_Modes::V_Blank:
                set_bit(status, 0);
                clear_bit(status, 1);
            break;

            case LCD_Modes::Searching_Sprite_Attributes:
                clear_bit(status, 0);
                set_bit(status, 1);
            break;

            case LCD_Modes::Transferring_Data:
                set_bit(status, 0);
                set_bit(status, 1);
            break;
        }

        m_memory_controller->write(status_address, status);
    }

    bool should_set_coincidence_flag();
    void set_coincidence_flag();
    void clear_coincidence_flag();

    const uint16_t status_address = 0xFF41;
    static const int coincidence_bit = 2;

    MemoryBankController* m_memory_controller;
    Interrupt_Handler m_interrupt_handler;
    LCD_Control m_lcd_control;
};