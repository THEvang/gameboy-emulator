#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Cartridge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Joypad Joypad;

typedef enum Banking_Mode {
    Banking_Mode_ROM,
    Banking_Mode_RAM
} Banking_Mode;

typedef struct MemoryBankController {
    uint8_t memory[0xFFFF];
    uint8_t* rom;
    bool ram_enabled;
    uint8_t rom_bank;
    Banking_Mode banking_mode;
    uint8_t ram_bank;
    Joypad* joypad;
} MemoryBankController;

void write(MemoryBankController* mc, uint16_t address, uint8_t data);
uint8_t read(MemoryBankController* mc, uint16_t address);

void dma_transfer(MemoryBankController* mc, uint8_t data);
uint8_t read_from_rom_bank(MemoryBankController* mc, uint16_t address);
uint8_t read_joypad_input(MemoryBankController* mc);

void toggle_ram(MemoryBankController* mc, uint8_t data);
void set_lower_rom_bank_number(MemoryBankController* mc, uint8_t data);
void set_upper_rom_bank_number(MemoryBankController* mc, uint8_t data);
void set_banking_mode(MemoryBankController* mc, uint8_t data);
void set_ram_bank_number(MemoryBankController* mc, uint8_t data);

#ifdef __cplusplus
}
#endif