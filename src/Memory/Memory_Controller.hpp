#pragma once

#include "Memory/Cartridge.hpp"

enum BankingMode {
    Banking_Mode_ROM,
    Banking_Mode_RAM
};

class MemoryBankController {
public:

    MemoryBankController(uint8_t* cartridge_memory);

    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t data);

    uint8_t memory[0xFFFF];
    uint8_t* rom;
    bool ram_enabled = false;

private:

    uint8_t m_ram_bank = 1;
    uint8_t m_rom_bank = 1;
    BankingMode m_banking_mode = Banking_Mode_ROM;

    void special_writes(uint16_t address);
    void dma_transfer(uint8_t data);

    uint8_t read_from_rom_bank(uint16_t address) const;
    uint8_t read_from_ram(uint16_t address) const;
    uint8_t read_joypad_input() const;

    void switch_banking_mode(uint8_t data);

    void set_lower_rom_bank_number(uint8_t data);
    void set_upper_rom_bank_number(uint8_t data);
    void set_ram_bank_number(uint8_t data);
    void set_banking_mode(uint8_t data);

};

void toggle_ram(MemoryBankController* mc, uint8_t data);