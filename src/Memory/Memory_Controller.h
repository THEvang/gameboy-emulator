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

    uint16_t banking_register_1;
    uint8_t banking_register_2;

    //Use this to mask to the total number of banks
    int rom_bank_mask;
    int ram_bank_mask;
    
    uint16_t div_register;

    uint8_t* rom;
    bool ram_enabled;
    Banking_Mode banking_mode;

    uint8_t buttons;

    uint8_t (*read) (struct MemoryBankController*, uint16_t);
    void (*write) (struct MemoryBankController*, uint16_t, uint8_t);
} MemoryBankController;

void gb_memory_set_initial_state(MemoryBankController* mc, CartridgeHeader* header);