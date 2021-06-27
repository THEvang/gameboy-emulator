#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct Joypad Joypad;

typedef enum Banking_Mode {
    Banking_Mode_ROM,
    Banking_Mode_RAM
} Banking_Mode;

typedef struct MemoryBankController {
    uint8_t memory[0xFFFF+1];
    uint8_t ram[(0x1FFF+1) * 4];
    uint8_t rom_bank_number;
    uint8_t rom_bank_mask;

    uint8_t ram_bank_mask;
    uint8_t ram_bank_number;

    uint8_t* rom;
    bool ram_enabled;
    Banking_Mode banking_mode;
    Joypad* joypad;
} MemoryBankController;

void gb_write(MemoryBankController* mc, uint16_t address, uint8_t data);
uint8_t gb_read(MemoryBankController* mc, uint16_t address);

void gb_dma_transfer(MemoryBankController* mc, uint8_t data);
uint8_t gb_read_joypad_input(MemoryBankController* mc);

int gb_get_effective_rom_bank_number(MemoryBankController* mc);
int gb_get_effective_ram_bank_number(MemoryBankController* mc);

void gb_set_rom_bank_number(MemoryBankController* mc, uint8_t data);
void gb_set_ram_bank_number(MemoryBankController* mc, uint8_t data);
void gb_set_banking_mode(MemoryBankController* mc, uint8_t data);