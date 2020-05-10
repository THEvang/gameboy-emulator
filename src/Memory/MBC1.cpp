#include "memory_controllers/MBC1.h"

MBC1::MBC1(Memory& internal_memory, Memory& rom_memory) 
    : MemoryBankController(internal_memory, rom_memory) 
{}

uint8_t MBC1::read(const uint16_t address) const {
    if(address <= 0x3FFF) {
        return m_rom_memory.read(address);
    }  
    
    if (address >= 0x4000 && address <= 0x7FFF) {
        const auto read_addr = address + (m_rom_bank -1) * 0x4000;
        return m_rom_memory.read( read_addr);
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        return m_internal_memory.read(address);
    } 

    return m_internal_memory.read(address);
}

void MBC1::write(const uint16_t address, uint8_t value) {

    if(address <= 0x1FFF) {
        m_ram_enabled =  (value & 0x0F) == 0x0A; 
    } else if (address >= 0x2000 && address <= 0x3FFF) {

        value &= 0x1F;
        m_rom_bank &= (0b11100000);
        m_rom_bank |= value;
        
        if(m_rom_bank == 0) {
            m_rom_bank = 1;
        } else if (m_rom_bank == 20) {
            m_rom_bank = 21;
        } else if (m_rom_bank == 40) {
            m_rom_bank = 41;
        } else if (m_rom_bank == 60) {
            m_ram_bank = 61;   
        }

    } else if (address >= 0x4000 && address <= 0x5FFF) {

        switch (m_banking_mode) {
            case BankingMode::RAM:
                m_ram_bank = value;
                break;
            case BankingMode::ROM:
                m_rom_bank &= ~((0b00000011) << 5);
                m_rom_bank |= (value << 5);
                break;
        }

    } else if (address >= 0x6000 && address <= 0x7FFF) {
        if(value == 0) {
            m_banking_mode = BankingMode::ROM;
        } else if (value == 1) {
            m_banking_mode = BankingMode::RAM;
        }
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(m_ram_enabled) {
            m_internal_memory.write(address, value);
        }
    } else if (address >= 0XE00 && address <= 0XFE00) {
        m_internal_memory.write(address, value);
        m_internal_memory.write(address - 0x2000, value);
    }else if (address >= 0xFEA0 && address <=0xFEFF) {
    
    } else if(address == 0xFF04) {
        m_internal_memory.write(0xFF04, 0);
    } else if (address == 0xFF44) {
        m_internal_memory.write(0xFF44, 0);
    } else if (address == dma_address) {
        dma_transfer(value);
    } else {
        m_internal_memory.write(address, value);
    }
}

void MBC1::dma_transfer(uint8_t data) {
    const auto address = data << 8;
    for(int i = 0; i < 0xA0; i++) {
            m_internal_memory.write(0xF300+i, m_internal_memory.read(address + i));
    }
}