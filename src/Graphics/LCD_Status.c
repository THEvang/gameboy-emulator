#include "Graphics/LCD_Status.h"

#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Cpu/Interrupts.h"
#include "Graphics/LCD_Control.h"

static const uint16_t g_status_address = 0xFF41;
static const int g_coincidence_bit = 2;

void gb_set_status(MemoryBankController* mc, int* scanline_counter) {
    
    const uint16_t scanline_address = 0xFF44;
    if(!lcd_display_enabled(mc)) {
        *scanline_counter = 456;
        gb_set_mode(mc, LCD_Mode_V_Blank);
        gb_write(mc, scanline_address, 0);
        return;   
    }

    const LCD_Modes current_mode = gb_get_mode(mc);
    const uint8_t current_scanline = gb_read(mc, scanline_address);

    bool should_request_interrupt = false;
    
    uint8_t status = mc->memory[g_status_address];
    if(current_scanline >= 144) {
        gb_set_mode(mc, LCD_Mode_V_Blank);
        should_request_interrupt = test_bit_8bit(status, 4);
    } else {
        
        if(*scanline_counter >= (456 - 80)) {
            gb_set_mode(mc, LCD_Mode_Searching_Sprite_Attributes);
            should_request_interrupt = test_bit_8bit(status, 5);
        } else if(*scanline_counter >= (456 - 80 - 172)) {
            gb_set_mode(mc, LCD_Mode_Transferring_Data);
        } else {
            gb_set_mode(mc, LCD_Mode_H_Blank);
            should_request_interrupt = test_bit_8bit(status, 3);
        }
    }

    const LCD_Modes new_mode = gb_get_mode(mc);

    if(should_request_interrupt && (current_mode != new_mode)) {
        gb_request_interrupt(mc, Interrupts_LCD_STAT);
    }

    gb_should_set_coincidence_flag(mc) ? gb_set_coincidence_flag(mc) : gb_clear_coincidence_flag(mc);
}

bool gb_should_set_coincidence_flag(MemoryBankController* mc) {
    return mc->memory[0xFF44] == mc->memory[0xFF45];
}

void gb_set_coincidence_flag(MemoryBankController* mc) {

    uint8_t status = mc->memory[g_status_address];
    set_bit(&status, g_coincidence_bit);
    gb_write(mc, g_status_address, status);
    if(test_bit_8bit(status, 6)) {
        gb_request_interrupt(mc, Interrupts_LCD_STAT);
    }
}

void gb_clear_coincidence_flag(MemoryBankController* mc) {
    
    uint8_t status = mc->memory[g_status_address];
    clear_bit(&status, g_coincidence_bit);
    gb_write(mc, g_status_address, status);
}

LCD_Modes gb_get_mode(MemoryBankController* mc) {
    uint8_t status = mc->memory[g_status_address];
    return status & 0x03;
}

void gb_set_mode(MemoryBankController* mc, LCD_Modes mode) {

    uint8_t status = mc->memory[g_status_address];
    status = ((status  & ~0x03) | mode);
    gb_write(mc, g_status_address, status);
}
