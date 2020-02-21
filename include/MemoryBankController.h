#pragma once

#include <Memory.h>

enum class BankingMode {
    ROM,
    RAM
};

class MemoryBankController {
public:

    virtual uint8_t read(const uint16_t address) = 0;
    virtual void write(const uint16_t address, uint8_t value) = 0;

private:

    uint8_t m_ram_bank;
    uint8_t m_rom_banK;
    BankingMode m_banking_mode;
    Memory m_memory;
};