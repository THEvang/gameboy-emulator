#include "memory_controllers/MBC1.h"

MBC1::MBC1(Memory& internal_memory, Memory& rom_memory) 
    : MemoryBankController(internal_memory, rom_memory) 
{}

uint8_t MBC1::read(const uint16_t address) const {
    if (address <= 0x3FFF) {
        return m_rom_memory.read(address);
    }  
    
    if (address >= 0x4000 && address <= 0x7FFF) {
        const uint16_t read_addr = address + (m_rom_bank - 1) * 0x4000;
        return m_rom_memory.read(read_addr);
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        return m_internal_memory.read(address);
    } 

    return m_internal_memory.read(address);
}

void MBC1::write(const uint16_t address, uint8_t data) {

    if(address <= 0x1FFF) {
        ram_switching(data);
    } else if (address >= 0x2000 && address <= 0x3FFF) {
        set_lower_rom_bank_number(data);
    } else if (address >= 0x4000 && address <= 0x5FFF) {

        switch (m_banking_mode) {
            case BankingMode::RAM:
                set_ram_bank_number(data);
                break;
            case BankingMode::ROM:
                set_upper_rom_bank_number(data);
                break;
        }

    } else if (address >= 0x6000 && address <= 0x7FFF) {
        set_banking_mode(data);
    } else if (address >= 0xA000 && address <= 0xBFFF) {
        if(m_ram_enabled) {
            m_internal_memory.write(address, data);
        }
    } else if (address >= 0xE000 && address <= 0xFE00) {
        m_internal_memory.write(address, data);
        m_internal_memory.write(address - 0x2000, data);
    } else if (address >= 0xFEA0 && address <=0xFEFF) {

    } else if(address == 0xFF04) {
        m_internal_memory.write(0xFF04, 0);
    } else if (address == 0xFF44) {
        m_internal_memory.write(0xFF44, 0);
    } else if (address == dma_address) {
        dma_transfer(data);
    } else {
        m_internal_memory.write(address, data);
    }
}

void MBC1::dma_transfer(uint8_t data) {
    const auto address = data << 8;
    for(int i = 0; i < 0xA0; i++) {
            m_internal_memory.write(0xF300+i, m_internal_memory.read(address + i));
    }
}

void MBC1::ram_switching(uint8_t data) {
    if(data == 0) {
        m_ram_enabled = false;
    } else if (data == 0xA0) {
        m_ram_enabled = true;
    }
}

void MBC1::set_lower_rom_bank_number(uint8_t data) {

    data &= 0b00011111;
    m_rom_bank &= (0b11100000);
    m_rom_bank |= data;
    
    if(m_rom_bank == 0) {
        m_rom_bank = 1;
    } else if (m_rom_bank == 20) {
        m_rom_bank = 21;
    } else if (m_rom_bank == 40) {
        m_rom_bank = 41;
    } else if (m_rom_bank == 60) {
        m_ram_bank = 61;   
    }
}

void MBC1::set_upper_rom_bank_number(uint8_t data) {
    data &= 0b11100000;
    m_rom_bank &= 0b00011111;
    m_rom_bank |= data;
    if(m_rom_bank == 0) m_rom_bank++;
}

void MBC1::set_ram_bank_number(uint8_t data) {
    m_ram_bank = (data & 0x03);
}

void MBC1::set_banking_mode(uint8_t data) {
    if(data == 0) {
        m_banking_mode = BankingMode::ROM;
    } else if (data == 1) {
        m_banking_mode = BankingMode::RAM;
    }
}