#pragma once

#include <Memory.h>
#include <memory>

enum class BankingMode {
    ROM,
    RAM
};

class MemoryBankController {
public:

    MemoryBankController(Memory& internal_memory, Memory& rom_memory) 
    : m_internal_memory(internal_memory) 
    , m_rom_memory(rom_memory) {
    };

    virtual uint8_t read(const uint16_t address) = 0;
    virtual void write(const uint16_t address, uint8_t value) = 0;

protected:

    uint8_t m_ram_bank;
    uint8_t m_rom_bank = 1;
    bool m_ram_enabled;
    BankingMode m_banking_mode;

    Memory m_internal_memory;
    Memory m_rom_memory;
};