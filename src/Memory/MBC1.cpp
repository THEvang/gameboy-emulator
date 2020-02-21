#include "MBC1.h"

MBC1::MBC1(Memory& internal_memory, Memory& rom_memory) 
    : MemoryBankController(internal_memory, rom_memory) 
{
    
}

uint8_t MBC1::read(const uint16_t address) {
    if(address <= 0x3FFF) {
        return m_rom_memory.read(address);
    } else if (address >= 0x4000 || address <= 0x7FFF) {
        return m_rom_memory.read(address + m_rom_bank * 16000);
    } else {
        return m_internal_memory.read(address);
    }
};

void MBC1::write(const uint16_t address, uint8_t value) {

    if(address <= 0x1FFF) {
        m_ram_enabled = (value == 0) ? false : true; 
    } else if (address >= 0x2000 || address <= 0x3FFF) {

        if(value == 0) {
            m_rom_bank = 1;
        } else if (value == 20) {
            m_rom_bank = 21;
        } else if (value == 40) {
            m_rom_bank = 41;
        } else if (value == 60) {
            m_ram_bank = 61;   
        } else {            
            value &= (0b00011111);
            m_rom_bank &= (0b11100000);
            m_rom_bank |= value;
        }

    } else if (address >= 0x4000 || address <= 0x5FFF) {

        switch (m_banking_mode) {
            case BankingMode::RAM:
                m_rom_bank = value;
                break;
            case BankingMode::ROM:
                m_ram_bank &= ~((0b00000011) << 5);
                m_ram_bank |= (value << 5);
                break;
        }

    } else if (address >= 0x6000 || address <= 0x7FFF) {
        if(value == 0) {
            m_banking_mode = BankingMode::ROM;
        } else if (value == 1) {
            m_banking_mode = BankingMode::RAM;
        }
    } else {
        m_internal_memory.write(address, value);
    }
}