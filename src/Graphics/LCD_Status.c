#include "Graphics/LCD_Status.h"

#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Cpu/Interrupts.h"
#include "Graphics/LCD_Control.h"

static const uint16_t g_status_address = 0xFF41;
static const int g_coincidence_bit = 2;

void set_status(MemoryBankController* mc, int* scanline_counter) {
    
    const uint16_t scanline_address = 0xFF44;
    if(!lcd_display_enabled(mc)) {
        *scanline_counter = 456;
        set_mode(mc, LCD_Mode_V_Blank);
        gb_write(mc, scanline_address, 0);
        return;   
    }

    const LCD_Modes current_mode = get_mode(mc);
    const uint8_t current_scanline = gb_read(mc, scanline_address);

    bool should_request_interrupt = false;
    
    uint8_t status = gb_read(mc, g_status_address);
    if(current_scanline >= 144) {
        set_mode(mc, LCD_Mode_V_Blank);
        should_request_interrupt = test_bit_8bit(status, 4);
    } else {
        
        if(*scanline_counter >= (456 - 80)) {
            set_mode(mc, LCD_Mode_Searching_Sprite_Attributes);
            should_request_interrupt = test_bit_8bit(status, 5);
        } else if(*scanline_counter >= (456 - 80 - 172)) {
            set_mode(mc, LCD_Mode_Transferring_Data);
        } else {
            set_mode(mc, LCD_Mode_H_Blank);
            should_request_interrupt = test_bit_8bit(status, 3);
        }
    }

    const LCD_Modes new_mode = get_mode(mc);

    if(should_request_interrupt && (current_mode != new_mode)) {
        request_interrupt(mc, Interrupts_LCD_STAT);
    }

    should_set_coincidence_flag(mc) ? set_coincidence_flag(mc) : clear_coincidence_flag(mc);
}

bool should_set_coincidence_flag(MemoryBankController* mc) {
    return gb_read(mc, 0xFF44) == gb_read(mc, 0xFF45);
}

void set_coincidence_flag(MemoryBankController* mc) {

    uint8_t status = gb_read(mc, g_status_address);
    set_bit(&status, g_coincidence_bit);
    gb_write(mc, g_status_address, status);
    if(test_bit_8bit(status, 6)) {
        request_interrupt(mc, Interrupts_LCD_STAT);
    }
}

void clear_coincidence_flag(MemoryBankController* mc) {
    
    uint8_t status = gb_read(mc, g_status_address);
    clear_bit(&status, g_coincidence_bit);
    gb_write(mc, g_status_address, status);
}

LCD_Modes get_mode(MemoryBankController* mc) {
        uint8_t status = gb_read(mc, g_status_address);
        status &= 0x03;
        switch (status) {
            case 0: 
                return LCD_Mode_H_Blank;
            case 1:
                return LCD_Mode_V_Blank;
            case 2:
                return LCD_Mode_Searching_Sprite_Attributes;
            case 3:
                return LCD_Mode_Transferring_Data;
            default:
                return LCD_Mode_H_Blank;
        }
}

void set_mode(MemoryBankController* mc, LCD_Modes mode) {

    uint8_t status = gb_read(mc, g_status_address);

    switch(mode) {
        case LCD_Mode_H_Blank:
            clear_bit(&status, 0);
            clear_bit(&status, 1);
        break;

        case LCD_Mode_V_Blank:
            set_bit(&status, 0);
            clear_bit(&status, 1);
        break;

        case LCD_Mode_Searching_Sprite_Attributes:
            clear_bit(&status, 0);
            set_bit(&status, 1);
        break;

        case LCD_Mode_Transferring_Data:
            set_bit(&status, 0);
            set_bit(&status, 1);
        break;
    }
    
    gb_write(mc, g_status_address, status);
}
