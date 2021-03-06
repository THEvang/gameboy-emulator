#pragma once

#include <array>

#include "Memory/Memory.hpp"
#include "Memory/Cartridge.hpp"

enum class BankingMode {
    ROM,
    RAM
};

class MemoryBankController {
public:

    MemoryBankController(Memory& cartridge_memory);

    [[nodiscard]] uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t data);

    //Gets raw memory for modules that must bypass usual memory control;
    constexpr auto& raw() noexcept {
        return m_internal_memory;
    };

private:

    Bank_Type m_bank_type = Bank_Type::Uknown;

    uint8_t m_ram_bank = 1;
    uint8_t m_rom_bank = 1;
    bool m_ram_enabled = false;
    BankingMode m_banking_mode = BankingMode::ROM;

    void special_writes(uint16_t address);
    void dma_transfer(uint8_t data);

    uint8_t read_from_rom_bank(uint16_t address) const;
    uint8_t read_from_ram(uint16_t address) const;
    uint8_t read_joypad_input() const;

    void switch_banking_mode(uint8_t data);

    void ram_switching(uint8_t data);
    void set_lower_rom_bank_number(uint8_t data);
    void set_upper_rom_bank_number(uint8_t data);
    void set_ram_bank_number(uint8_t data);
    void set_banking_mode(uint8_t data);

    std::array<uint8_t, 0xFFFF> m_internal_memory;
    Memory m_cartridge_memory;
};