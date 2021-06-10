#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Input/Joypad.hpp"

uint8_t read(MemoryBankController* mc, uint16_t address) {

    if(address <= 0x7FFF) {
        return read_from_rom_bank(mc, address);
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        //RAM
        return mc->memory[address];    
    } 

    if(address == 0xFF00) {
        return read_joypad_input(mc);        
    }

    return mc->memory[address];
}

void toggle_ram(MemoryBankController* mc, uint8_t data) {
    if(data == 0) {
        mc->ram_enabled = false;
    } else if (data == 0xA0) {
        mc->ram_enabled = true;
    }
}

void set_lower_rom_bank_number(MemoryBankController* mc, uint8_t data) {

    data &= 0b00011111;
    mc->rom_bank &= (0b11100000);
    mc->rom_bank |= data;
    
    if(mc->rom_bank == 0) {
        mc->rom_bank = 1;
    } else if (mc->rom_bank == 20) {
        mc->rom_bank = 21;
    } else if (mc->rom_bank == 40) {
        mc->rom_bank = 41;
    } else if (mc->rom_bank == 60) {
        mc->rom_bank = 61;   
    }
}

void set_upper_rom_bank_number(MemoryBankController* mc, uint8_t data) {
    data &= 0b11100000;
    mc->rom_bank &= 0b00011111;
    mc->rom_bank |= data;
    if(mc->rom_bank == 0) {
        mc->rom_bank++;
    }
}

void set_banking_mode(MemoryBankController* mc, uint8_t data) {
    if(data == 0) {
        mc->banking_mode = Banking_Mode_ROM;
    } else if (data == 1) {
        mc->banking_mode = Banking_Mode_RAM;
    }
}

void set_ram_bank_number(MemoryBankController* mc, uint8_t data) {
    mc->ram_bank = (data & 0x03u);
}

void write(MemoryBankController* mc, uint16_t address, uint8_t data) {

    if(address <= 0x1FFF) {
        toggle_ram(mc, data);
    } else if (address >= 0x2000 && address <= 0x3FFF) {
        set_lower_rom_bank_number(mc, data);
    } else if (address >= 0x4000 && address <= 0x5FFF) {

        switch (mc->banking_mode) {
            case Banking_Mode_RAM:
                set_ram_bank_number(mc, data);
                break;
            case Banking_Mode_ROM:
                set_upper_rom_bank_number(mc, data);
                break;
        }

    } else if (address >= 0x6000 && address <= 0x7FFF) {
        set_banking_mode(mc, data);
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(mc->ram_enabled) {
            mc->memory[address] = data;
        }
    } else if (address >= 0xE000 && address < 0xFE00) {
        mc->memory[address] = data;
        write(mc, (uint16_t) (address - 0x2000), data);
    } else if (address >= 0xFEA0 && address < 0xFEFF) {

    } else if(address == 0xFF04) {
        mc->memory[0xFF04] = 0;
    } else if (address == 0xFF44) {
        mc->memory[0xFF44] = 0;
    } else if (address == 0xFF46) {
        dma_transfer(mc, data);
    } else {
        mc->memory[address] = data;
    }
}

void dma_transfer(MemoryBankController* mc, uint8_t data) {
    
    uint16_t address = (uint16_t) (data << 8u);
    
    for(int i = 0; i < 0xA0; i++) {
        uint8_t dma_data = read(mc, (uint16_t) (address + i));
        write(mc, (uint16_t) (0xFE00+i), dma_data);
    }
}

uint8_t read_from_rom_bank(MemoryBankController* mc, uint16_t address) {

    if (address >= 0x4000 && address <= 0x7FFF) {
        uint16_t read_addr = (uint16_t) (address + (mc->rom_bank - 1) * 0x4000);
        return mc->rom[read_addr];
    }
    
    return mc->rom[address];
}

uint8_t read_joypad_input(MemoryBankController* mc) {

    uint8_t data = mc->memory[0xFF00];

    if(!test_bit_8bit(data, 5)) {
        return mc->joypad->button_keys;
    }

    if(!test_bit_8bit(data, 4)) {
        return mc->joypad->direction_keys;
    }

    return data;
}