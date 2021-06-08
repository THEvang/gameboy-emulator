#include "Memory/Memory_Controller.hpp"

#include "Utilities/BitOperations.hpp"

#include "Input/Joypad_Controller.hpp"

MemoryBankController::MemoryBankController(Memory& cartridge_memory) 
    : m_cartridge_memory(cartridge_memory) 
{
    m_bank_type = get_bank_type(m_cartridge_memory.read(0x0147));
}

uint8_t MemoryBankController::read(uint16_t address) const {

    if(address <= 0x7FFF) {
        return read_from_rom_bank(address);
    }
    
    if (address >= 0xA000 && address <= 0xBFFF) {
        return read_from_ram(address);
    } 

    if(address == 0xFF00) {
        return read_joypad_input();        
    }

    return m_internal_memory[address];
}

void MemoryBankController::write(uint16_t address, uint8_t data) {

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
            m_internal_memory[address] = data;
        }
    } else if (address >= 0xE000 && address < 0xFE00) {
        m_internal_memory[address] = data;
        write(static_cast<uint16_t>(address - 0x2000), data);
    } else if (address >= 0xFEA0 && address < 0xFEFF) {

    } else if(address == 0xFF04) {
        m_internal_memory[0xFF04] = 0;
    } else if (address == 0xFF44) {
        m_internal_memory[0xFF44] = 0;
    } else if (address == 0xFF46) {
        dma_transfer(data);
    } else {
        m_internal_memory[address] = data;
    }
}

void MemoryBankController::dma_transfer(uint8_t data) {
    const auto address = static_cast<uint16_t>(data << 8u);
    for(int i = 0; i < 0xA0; i++) {
        const auto dma_data = read(static_cast<uint16_t>(address + i));
        write(static_cast<uint16_t>(0xFE00+i), dma_data);
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
    if(m_rom_bank == 0) {
        m_rom_bank++;
    }
}

void MemoryBankController::set_ram_bank_number(uint8_t data) {
    m_ram_bank = (data & 0x03u);
}

void MemoryBankController::set_banking_mode(uint8_t data) {
    if(data == 0) {
        m_banking_mode = BankingMode::ROM;
    } else if (data == 1) {
        m_banking_mode = BankingMode::RAM;
    }
}

uint8_t MemoryBankController::read_from_rom_bank(uint16_t address) const {

    
    if (address >= 0x4000 && address <= 0x7FFF) {
        const auto read_addr = static_cast<uint16_t>(address + (m_rom_bank - 1) * 0x4000);
        return m_cartridge_memory.read(read_addr);
    }
    
    return m_cartridge_memory.read(address);
}

uint8_t MemoryBankController::read_from_ram(uint16_t address) const {   
    return m_internal_memory[address];
}

uint8_t MemoryBankController::read_joypad_input() const {

    const auto data = m_internal_memory[0xFF00];

    if(!test_bit_8bit(data, 5)) {
        return Joypad_Controller::read_input_as_byte(Button_Types::Button_Key);
    }

    if(!test_bit_8bit(data, 4)) {
        return Joypad_Controller::read_input_as_byte(Button_Types::Direction_Key);
    }

    return data;
}