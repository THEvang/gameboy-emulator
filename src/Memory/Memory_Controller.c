#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Input/Joypad.h"

#include <stdio.h>
#include <stdlib.h>

#define ROM_BANK_SIZE 0x4000
#define RAM_BANK_SIZE 0x2000

uint8_t gb_read(MemoryBankController* mc, uint16_t address) {

    if (address <= 0x3FFF) {
        return mc->rom[address];
    }

    if(address >= 0x4000 && address <= 0x7FFF) {
        int offset = address - ROM_BANK_SIZE;
        int effective_bank = gb_get_effective_rom_bank_number(mc);
        int read_addr = offset + effective_bank * ROM_BANK_SIZE;
        return mc->rom[read_addr];
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        if (mc->ram_enabled) {
            int offset = address - 0xA000;
            int ram_bank = gb_get_effective_ram_bank_number(mc);
            int read_addr = offset + ram_bank * RAM_BANK_SIZE;
            return mc->ram[read_addr];
        }
        return 0;
    }

    if(address == 0xFF00) {
        return gb_read_joypad_input(mc);        
    }

    if(address == 0xFF0F) {
        return mc->memory[address] | 0xE0;
    }

    return mc->memory[address];
}

void gb_set_rom_bank_number(MemoryBankController* mc, uint8_t data) {

    mc->rom_bank_number = (data & mc->rom_bank_mask);
    
    if(mc->rom_bank_number == 0) {
        (mc->rom_bank_number)++;
    }
}

void gb_set_banking_mode(MemoryBankController* mc, uint8_t data) {
    
    if (data == 1) {
        mc->banking_mode = Banking_Mode_RAM;
        return;
    }
    
    mc->banking_mode = Banking_Mode_ROM;
}

void gb_set_ram_bank_number(MemoryBankController* mc, uint8_t data) {
    mc->ram_bank_number = (data & mc->ram_bank_mask);
}

void gb_write(MemoryBankController* mc, uint16_t address, uint8_t data) {

    if(address <= 0x1FFF) {
        mc->ram_enabled = ((data & 0x0F) == 0x0A);
        return;
    }

    if (address >= 0x2000 && address <= 0x3FFF) {
        gb_set_rom_bank_number(mc, data);
        return;
    } 
    
    if (address >= 0x4000 && address <= 0x5FFF) {
        gb_set_ram_bank_number(mc, data);
        return;
    } 
    
    if (address >= 0x6000 && address <= 0x7FFF) {
        gb_set_banking_mode(mc, data);
        return;
    } 

    if (address >= 0xA000 && address <= 0xBFFF) {
        if(mc->ram_enabled) {
            int offset = address - 0xA000;
            int ram_bank = gb_get_effective_ram_bank_number(mc);
            int write_addr = offset + ram_bank * RAM_BANK_SIZE;
            mc->ram[write_addr] = data;
        }
        return;
    } 
    
    if (address >= 0xFEA0 && address < 0xFEFF) {
        return;
    } 
    
    if(address == 0xFF04) {
        mc->memory[address] = 0;
        return;
    }

    if (address == 0xFF44) {
        mc->memory[address] = 0;
        return;
    }
    
    if (address == 0xFF46) {
        gb_dma_transfer(mc, data);
        return;
    } 

    mc->memory[address] = data;
}

void gb_dma_transfer(MemoryBankController* mc, uint8_t data) {
    
    uint16_t address = (uint16_t) (data << 8);
    
    for(int i = 0; i < 0xA0; i++) {
        uint8_t dma_data = gb_read(mc, (uint16_t) (address + i));
        gb_write(mc, (uint16_t) (0xFE00 + i), dma_data);
    }
}

uint8_t gb_read_joypad_input(MemoryBankController* mc) {

    uint8_t data = mc->memory[0xFF00];

    if(!test_bit_8bit(data, 5)) {
        return mc->joypad->button_keys;
    }

    if(!test_bit_8bit(data, 4)) {
        return mc->joypad->direction_keys;
    }

    return data;
}

int gb_get_effective_rom_bank_number(MemoryBankController* mc) {
    return ((mc->ram_bank_number << 5) | (mc->rom_bank_number)) & mc->rom_bank_mask;
}

int gb_get_effective_ram_bank_number(MemoryBankController* mc) {
    return mc->banking_mode == Banking_Mode_ROM ? 0 : (mc->ram_bank_number & mc->ram_bank_mask);
}