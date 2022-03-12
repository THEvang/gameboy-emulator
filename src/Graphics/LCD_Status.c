#include <stdbool.h>
#include <stdint.h>

#include "Graphics/LCD_Status.h"
#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Cpu/Interrupts.h"

static const int g_coincidence_bit = 2;

void gb_set_status(MemoryBankController* mc, int* scanline_counter) {
    
    mc->memory[LY] == mc->memory[LYC] ? 
        gb_set_coincidence_flag(mc) : 
        gb_clear_coincidence_flag(mc);

    const LCD_Modes current_mode = gb_get_mode(mc);
    const uint8_t scanline = mc->read(mc, LY);

    bool should_request_interrupt = false;
    
    uint8_t status = mc->memory[STAT];
    if(scanline >= 144) {
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
}

void gb_set_coincidence_flag(MemoryBankController* mc) {

    uint8_t status = mc->memory[STAT];
    set_bit(&status, g_coincidence_bit);
    mc->write(mc, STAT, status);
    if(test_bit_8bit(status, 6)) {
        gb_request_interrupt(mc, Interrupts_LCD_STAT);
    }
}

void gb_clear_coincidence_flag(MemoryBankController* mc) {
    
    uint8_t status = mc->memory[STAT];
    clear_bit(&status, g_coincidence_bit);
    mc->write(mc, STAT, status);
}

LCD_Modes gb_get_mode(MemoryBankController* mc) {
    return mc->memory[STAT] & 0x03;
}

void gb_set_mode(MemoryBankController* mc, LCD_Modes mode) {

    uint8_t status = mc->memory[STAT];
    status = (uint8_t) ( (uint8_t) (status  & ~0x03) | mode);
    mc->write(mc, STAT, status);
}
