#pragma once

#include "Memory/Memory_Controller.h"

typedef enum LCD_Modes {
    LCD_Mode_H_Blank = 0,
    LCD_Mode_V_Blank = 1,
    LCD_Mode_Searching_Sprite_Attributes = 2,
    LCD_Mode_Transferring_Data = 3
} LCD_Modes;

void gb_set_status(MemoryBankController* mc, int* scanline_counter);
LCD_Modes gb_get_mode(MemoryBankController* mc);
void gb_set_mode(MemoryBankController* mc, LCD_Modes mode);

void gb_set_coincidence_flag(MemoryBankController* mc);
void gb_clear_coincidence_flag(MemoryBankController* mc);