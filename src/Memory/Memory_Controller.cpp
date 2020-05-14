#include "Memory/Memory_Controller.h"

MemoryBankController::MemoryBankController(Memory& cartridge_memory) 
    :   m_internal_memory(0xFFFF), 
        m_cartridge_memory(cartridge_memory) 
{
    m_bank_type = get_bank_type(m_cartridge_memory.read(0x0147));
};

uint8_t MemoryBankController::read(const uint16_t address) const {


    if(address <= 0x7FFF) {
        return read_from_rom_bank(address);
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        return read_from_ram(address);
    } 

    if(address == 0xFF00) {
    }

    return m_internal_memory.read(address);
}

void MemoryBankController::write(const uint16_t address, uint8_t data) {

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
    } else if (address >= 0xE000 && address < 0xFE00) {
        m_internal_memory.write(address, data);
        write(address - 0x2000, data);
    } else if (address >= 0xFEA0 && address < 0xFEFF) {

    } else if(address == 0xFF04) {
        m_internal_memory.write(0xFF04, 0);
    } else if (address == 0xFF44) {
        m_internal_memory.write(0xFF44, 0);
    } else if (address == 0xFF46) {
        dma_transfer(data);
    } else {
        m_internal_memory.write(address, data);
    }
}

void MemoryBankController::dma_transfer(uint8_t data) {
    const uint16_t address = data << 8;
    for(int i = 0; i < 0xA0; i++) {
        const uint8_t dma_data = read(address + i);
        write(0xFE00+i, dma_data);
    }
}

void MemoryBankController::ram_switching(uint8_t data) {
    if(data == 0) {
        m_ram_enabled = false;
    } else if (data == 0xA0) {
        m_ram_enabled = true;
    }
}

void MemoryBankController::set_lower_rom_bank_number(uint8_t data) {

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

void MemoryBankController::set_upper_rom_bank_number(uint8_t data) {
    data &= 0b11100000;
    m_rom_bank &= 0b00011111;
    m_rom_bank |= data;
    if(m_rom_bank == 0) m_rom_bank++;
}

void MemoryBankController::set_ram_bank_number(uint8_t data) {
    m_ram_bank = (data & 0x03);
}

void MemoryBankController::set_banking_mode(uint8_t data) {
    if(data == 0) {
        m_banking_mode = BankingMode::ROM;
    } else if (data == 1) {
        m_banking_mode = BankingMode::RAM;
    }
}

uint8_t MemoryBankController::read_from_rom_bank(uint16_t address) const {

    if(m_bank_type == Bank_Type::Rom_Only) {
        return m_cartridge_memory.read(address);
    }

    if (address <= 0x3FFF) {
        return m_cartridge_memory.read(address);
    }  
    
    if (address >= 0x4000 && address <= 0x7FFF) {
        const uint16_t read_addr = address + (m_rom_bank - 1) * 0x4000;
        return m_cartridge_memory.read(read_addr);
    }
}

uint8_t MemoryBankController::read_from_ram(uint16_t address) const {   
    return m_internal_memory.read(address);
}