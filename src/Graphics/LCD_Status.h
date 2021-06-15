#pragma once

#include <stdbool.h>
#include "Memory/Memory_Controller.h"

typedef enum LCD_Modes {
    LCD_Mode_H_Blank,
    LCD_Mode_V_Blank,
    LCD_Mode_Searching_Sprite_Attributes,
    LCD_Mode_Transferring_Data
} LCD_Modes;

void set_status(MemoryBankController* mc, int* scanline_counter);
LCD_Modes get_mode(MemoryBankController* mc);
void set_mode(MemoryBankController* mc, LCD_Modes mode);

bool should_set_coincidence_flag(MemoryBankController* mc);
void set_coincidence_flag(MemoryBankController* mc);
void clear_coincidence_flag(MemoryBankController* mc);