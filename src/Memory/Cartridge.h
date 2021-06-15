#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum Bank_Type {
    Bank_Rom_Only,
    Bank_MBC_1,
    Bank_MBC_2,
    Bank_MBC_3,
    Bank_MBC_5,
    Bank_MBC_6,
    Bank_MBC_7,
    Bank_Uknown,
} Bank_Type;

Bank_Type get_bank_type(uint8_t type_number);
bool has_ram(uint8_t type_number);