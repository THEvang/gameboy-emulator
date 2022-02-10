#pragma once

#include "Gameboy/Cartridge.h"

#include <stdint.h>
#include <stdbool.h>

typedef enum Banking_Mode {
    Banking_Mode_ROM,
    Banking_Mode_RAM
} Banking_Mode;

typedef enum Button_Types {
    Direction_Button  = 1 << 4,
    Action_Button = 1 << 5
} Button_Type;

typedef struct MemoryBankController {
    uint8_t memory[0x10000];
    uint8_t ram[0x2000 * 16];

    uint16_t rom_bank_number;
    uint16_t rom_bank_mask;

    uint8_t ram_bank_mask;
    uint8_t ram_bank_number;
    uint16_t div_register;

    uint8_t* rom;
    bool ram_enabled;
    Banking_Mode banking_mode;

    uint8_t buttons;

    uint8_t (*read) (struct MemoryBankController*, uint16_t);
    void (*write) (struct MemoryBankController*, uint16_t, uint8_t);
} MemoryBankController;

void set_io(MemoryBankController* mc, Cartridge_Type mb_type);