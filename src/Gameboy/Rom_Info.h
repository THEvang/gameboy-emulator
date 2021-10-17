#pragma once

#include "Utilities/File.h"

typedef enum Memory_Bank_Type {
    MB_None,
    MB_MBC_1,
    MB_MBC_2,
    MB_MBC_3,
    MB_MBC_5,
    MB_MBC_6,
    MB_MBC_7,
    MB_MM01
} Memory_Bank_Type;

Memory_Bank_Type get_memory_bank_type(gb_Rom* rom);
void gb_print_rom_info(gb_Rom* rom);
