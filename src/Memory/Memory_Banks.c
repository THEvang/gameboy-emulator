#include <stdint.h>
#include <assert.h>

#include "Memory_Controller.h"

#define ROM_BANK_SIZE 0x4000
#define RAM_BANK_SIZE 0x2000

#define DMA_ADDRESS 0xFF46
#define DIV_REGISTER_ADDRESS 0xFF04
#define LDC_Y_COORDINATE_ADDRESS 0xFF44
#define JOYPAD_INPUT_ADDRESS 0xFF00
#define INTERRUPT_FLAG_ADDRESS 0xFF0F

uint8_t gb_read_joypad_input(MemoryBankController* mc) {

    uint8_t data = mc->memory[JOYPAD_INPUT_ADDRESS];

    if ( !(data & Action_Button)) {
        return (mc->buttons >> 4) & 0x0F;
    }

    if ( !(data & Direction_Button)) {
        return mc->buttons & 0xFF;
    }

    return 0xFF;
}

void gb_dma_transfer(MemoryBankController* mc, uint8_t data) {
    
    uint16_t address = (uint16_t) (data << 8);
    assert(address <= 0xDFFF);

    for(int i = 0; i < 0xA0; i++) {
        assert( (address + i) <= 0xDFFF);
        mc->memory[0xFE00 + i] = mc->memory[address + i];
    }
}

void gb_common_writes(MemoryBankController* mc, uint16_t address, uint8_t data) {
    
    if(address <= 0x1FFF) {
        mc->ram_enabled = ((data & 0x0F) == 0x0A);
        return;
    }

    if (address >= 0xFEA0 && address < 0xFEFF) {
        return;
    }

    switch (address) {
    case DIV_REGISTER_ADDRESS:
        mc->memory[address] = 0;
        mc->div_register = 0;
        break;
    case DMA_ADDRESS:
        gb_dma_transfer(mc, data);
        break;
    case LDC_Y_COORDINATE_ADDRESS:
        mc->memory[address] = 0;
        break;
    default:
        mc->memory[address] = data;
        break;
    }
}

uint8_t gb_common_reads(MemoryBankController* mc, uint16_t address) {

    switch (address) {
    case JOYPAD_INPUT_ADDRESS:
        return gb_read_joypad_input(mc);
    case INTERRUPT_FLAG_ADDRESS:
        return mc->memory[address] | 0xE0;
    case 0xFF01: case 0xFF18: case 0xFF1B:
    case 0xFF1D: case 0xFF20:
        return 0xFF;
    default:
        return mc->memory[address];
    }
}

void gb_set_rom_bank_number(MemoryBankController* mc, uint8_t data, uint8_t bank_type_mask) {

    mc->banking_register_1 = (data & bank_type_mask) & mc->rom_bank_mask;
    
    if(mc->banking_register_1 == 0) {
        mc->banking_register_1++;
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
    mc->banking_register_2 = (data & 0x3);
}

void gb_write_none(MemoryBankController* mc, uint16_t address, uint8_t data) {

    //Writing to rom is not allowed
    if (address <= 0x7FFF) {
        return;
    } 

    gb_common_writes(mc, address, data);
}

uint8_t gb_read_none(MemoryBankController* mc, uint16_t address) {

    if(address <= 0x7FFF) {
        return mc->rom[address];
    }

    //No licensed games use rom+ram, so we just return 0xFF     
    if (address >= 0xA000 && address <= 0xBFFF) {
        return 0xFF;
    }

    return gb_common_reads(mc, address);
}

uint8_t gb_read_mbc_1(MemoryBankController* mc, uint16_t address) {

    if (address <= 0x3FFF) {
        int effective_bank = 0;
        if(mc->banking_mode == Banking_Mode_RAM) {
            effective_bank = (mc->banking_register_2 << 5);
        }

        return mc->rom[address + (effective_bank & mc->rom_bank_mask) * ROM_BANK_SIZE];
    }

    if(address >= 0x4000 && address <= 0x7FFF) {
        int offset = address - ROM_BANK_SIZE;
        int effective_bank = ((mc->banking_register_2 << 5) | (mc->banking_register_1));
        int read_addr = offset + (effective_bank & mc->rom_bank_mask) * ROM_BANK_SIZE;
        return mc->rom[read_addr];
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        if (mc->ram_enabled) {
            int offset = address - 0xA000;
            int ram_bank = mc->banking_mode == Banking_Mode_ROM ? 0 : (mc->banking_register_2);
            int read_addr = offset + (ram_bank & mc->ram_bank_mask) * RAM_BANK_SIZE;
            return mc->ram[read_addr];
        }
        return 0xFF;
    }

    return gb_common_reads(mc, address);
}

void gb_write_mbc_1(MemoryBankController* mc, uint16_t address, uint8_t data) {

    if (address >= 0x2000 && address <= 0x3FFF) {
        gb_set_rom_bank_number(mc, data, 0x1F);
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
            int ram_bank = mc->banking_mode == Banking_Mode_ROM ? 0 : (mc->banking_register_2);
            int write_addr = offset + (ram_bank & mc->ram_bank_mask) * RAM_BANK_SIZE;
            mc->ram[write_addr] = data;
        }
        return;
    }
    
    if (address >= 0xE000 && address < 0xFE00) {
        mc->memory[address] = data;
        mc->write(mc, (uint16_t) (address - 0x2000), data);
        return;
    }

    gb_common_writes(mc, address, data);
}

    mc->memory[address] = data;
}
        return;
    }

    if (address == 0xFF44) {
        mc->memory[address] = 0;
        return;
    }
    
    if (address == DMA_ADDRESS) {
        gb_dma_transfer(mc, data);
        return;
    } 

    mc->memory[address] = data;
}

// uint8_t gb_read_mbc_3(MemoryBankController* mc, uint16_t address);
// void gb_write_mbc_3(MemoryBankController* mc, uint16_t address, uint8_t data);

uint8_t gb_read_mbc_5(MemoryBankController* mc, uint16_t address) {

    //Always contains the first 16kbs of rom for MBC 5
    if (address <= 0x3FFF) {
        return mc->rom[address];
    }

    //Can contain banks up to 0x1FF, including bank 0
    if(address >= 0x4000 && address <= 0x7FFF) {
        int offset = address - ROM_BANK_SIZE;
        int read_addr = offset + (mc->banking_register_1 & mc->rom_bank_mask) * ROM_BANK_SIZE;
        return mc->rom[read_addr];
    }
    
    //Same as for MBC1, but can contain more ram
    if (address >= 0xA000 && address <= 0xBFFF) {
        if (mc->ram_enabled) {
            int offset = address - 0xA000;
            int ram_bank = mc->banking_register_2;
            int read_addr = offset + (ram_bank & mc->ram_bank_mask) * RAM_BANK_SIZE;
            return mc->ram[read_addr];
        }
        return 0xFF;
    }

    return gb_common_reads(mc, address);
}

void gb_write_mbc_5(MemoryBankController* mc, uint16_t address, uint8_t data) {

    //Set the 8 least significant bits of rom bank number
    if (address > 0x1FFF && address <= 0x2FFF) {
        mc->banking_register_1 = data;
        return;
    }

    //Sets the 9th bit of the rom bank number
    if (address <= 0x3FFF) {
        data &= 0x01;
        mc->banking_register_1 |= (uint16_t) (data << 8);
        return;
    }

    //Sets the ram bank number between 0x00 and 0x0F
    if (address <= 0x5FFF) {
        mc->banking_register_2 = data & 0x0F;
        return;
    }

    if (address >= 0xA000 && address <= 0xBFFF) {
        if(mc->ram_enabled) {
            int offset = address - 0xA000;
            int write_addr = offset + (mc->banking_register_2  & mc->ram_bank_mask) * RAM_BANK_SIZE;
            mc->ram[write_addr] = data;
        }
        return;
    }

    gb_common_writes(mc, address, data);
}