#include <cstdint>
#include <vector>

class Memory {
public:
    uint8_t read(const uint16_t address);
    void write(const uint16_t address, uint8_t value);

private:
    std::vector<uint8_t> m_memory;
};


class MemoryBankController {

    virtual uint8_t read(const uint16_t address) = 0;
    virtual void write(const uint16_t address, const uint8_t value) = 0;

protected:

    Memory m_memory;
};

 enum class BankingMode {
    ROM,
    RAM
};

class MBC1 : public MemoryBankController {
public:

    uint8_t read(const uint16_t address) override {
        if(address <= 0x3FFF) {
            return m_memory.read(address);
        } else if (address >= 0x4000 && address <= 0x7FFF) {
            m_memory.read(address + m_rom_bank_number * 16000);
        } else if (address >= 0xA000 && address <= 0xBFFF) {

        }
    }

    void write(const uint16_t address, const uint8_t value) override {

        if (value <= 0x1FFF) {
            m_enable_ram = (value == 0x0A);
        } else if ( value >= 0x2000 && value <= 0x3FFF) {
            if(value == 0x00) {
                m_rom_bank_number = 0x01;
            } else if (value == 0x20) {
                m_rom_bank_number = 0x21;
            } else if (value == 0x40) {
                m_rom_bank_number = 0x41;
            } else if (value == 0x60) {
                m_rom_bank_number = 0x61;
            } else {
                m_rom_bank_number &= value;
            }
        } else if (value >= 0x4000 && value <= 0x5FFF) {
            if(m_banking_mode == BankingMode::ROM)
            {
                m_rom_bank_number &= ~(3 << 5);
                m_rom_bank_number |= value << 5;
            } else {
                m_ram_bank_number = value;
            }

        } else if (value >= 0x6000 && value <= 0x7FFF) {
            if(value == 0x01) {
                m_banking_mode == BankingMode::RAM;
            } else {
                m_banking_mode == BankingMode::ROM;
            }
        }

    }

private:

    bool m_enable_ram;
    uint8_t m_rom_bank_number;
    uint8_t m_ram_bank_number;
    BankingMode m_banking_mode;

};

class MBC2 : MemoryBankController {

};




