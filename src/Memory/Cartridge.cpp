#include "Memory/Cartridge.hpp"

Bank_Type get_bank_type(uint8_t type_number) {
    switch(type_number) {
        case 0x00:
            return Bank_Type::Rom_Only;
        case 0x01:
        case 0x02:
        case 0x03:
            return Bank_Type::MBC_1;
        case 0x05:
        case 0x06:
            return Bank_Type::MBC_2;
        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            return Bank_Type::MBC_3;
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return Bank_Type::MBC_5;
        case 0x20:
            return Bank_Type::MBC_6;
        case 0x22:
            return Bank_Type::MBC_7;
        default:
            return Bank_Type::Uknown;
    }
}

bool has_ram(uint8_t type_number) {
    switch(type_number) {
        case 0x02:
        case 0x03:
        case 0x08:
        case 0x09:
        case 0x0C:
        case 0x0D:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x1A:
        case 0x1B:
        case 0x1D:
        case 0x1E:
        case 0x22:
        case 0xFF:
            return true;
        default:
            return false;
    }
}
