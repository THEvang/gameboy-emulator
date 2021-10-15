#pragma once

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
    uint8_t ram[0x2000 * 4];
    int n_rom_banks;
    uint8_t rom_bank_number;
    uint8_t rom_bank_mask;

    uint8_t ram_bank_mask;
    uint8_t ram_bank_number;
    uint16_t div_register;

    uint8_t* rom;
    bool ram_enabled;
    Banking_Mode banking_mode;

    uint8_t buttons;

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