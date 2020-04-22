#pragma once

#include "memory_controllers/Memory.h"
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

    virtual ~MemoryBankController() = default;

    virtual uint8_t read(const uint16_t address) const = 0;
    virtual void write(const uint16_t address, uint8_t value) = 0;

    //Gets raw memory for modules that must bypass usual memory control;
    Memory* raw() {
        return &m_internal_memory;
    };

protected:

    uint8_t m_ram_bank = 1;
    uint8_t m_rom_bank = 1;
    bool m_ram_enabled = false;
    BankingMode m_banking_mode = BankingMode::ROM;

    Memory m_internal_memory;
    Memory m_rom_memory;
};