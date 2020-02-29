#include <vector>
#include <memory>

#include <Cartridge.h>

class InternalMemory {
public:

    using word_type = uint8_t;
    using address_type = uint16_t;

    void Write(const address_type address, const word_type data) {
        m_memory[address] = data;
    }

    word_type Read(const address_type address) const {
        return m_memory[address];
    }

    auto begin() {
        return m_memory.begin();
    }

    auto end() {
        return m_memory.end();
    }


private:

    std::vector<uint8_t> m_memory;

};

enum class BankingMode {
    ROM,
    RAM
};

class MemoryController {
public:

    MemoryController(std::unique_ptr<Cartridge> cartridge);

    virtual void Write(uint16_t address, uint8_t data) = 0;
    virtual uint8_t Read(uint16_t address) = 0;
    virtual void SwitchRomBank(int bankNumber);
    virtual void SwitchRamBank(int bankNumber);

protected:

    BankingMode m_bankingMode;
    uint8_t m_rombankNumber;
    std::unique_ptr<InternalMemory> m_memory;
    std::unique_ptr<Cartridge> m_cartridge;
};


class MemoryBankController1 : public MemoryController {
public:
    MemoryBankController1(std::unique_ptr<Cartridge> cartridge);

    void Write(uint16_t address, uint8_t data) override {

        if(address <= 0x1FFF) {

            if ( (data & 0x00FF) == 0x0A) {
                
            } else {
                
            }


        } else if (address >= 0x2000 && address <=0x3FFF) {
            


        } else if (address >= 0x4000 && address <= 0x5FFF) {

            switch(m_bankingMode) {
                case BankingMode::RAM:
                    SwitchRamBank(data);
                break;
                case BankingMode::ROM:
                    m_rombankNumber &= (data << 5);
                    SwitchRomBank(m_rombankNumber);
                break;
                default:
                break;
            }

        } else if (address >= 0x6000 && address <= 0x7FFF) {

            if(data == 0) {
                m_bankingMode = BankingMode::ROM;
            } else if (data == 1) {
                m_bankingMode = BankingMode::RAM;
            }

        } else {
            m_memory->Write(address, data);
        }

    };



};

class MemoryBankController2 : public MemoryController {
public:

    MemoryBankController2(std::unique_ptr<Cartridge> cartridge);

    void Write(uint16_t address, uint8_t data) {
        
        if(address <= 0x1FFF) {

        } else if (address >= 0x2000 && address <= 0x3FFF) {

        } else {
            m_memory->Write(address, data);
        }
    }
};

class MemoryBankController3 : public MemoryController {
public:

    MemoryBankController3(std::unique_ptr<Cartridge> cartridge);

    void Write(uint16_t address, uint8_t data) {

        if(address <= 0x1FFF) {

        } else if (address >= 0x2000 && address <= 0x3FFF) {

        } else if (address >= 0x4000 && address <= 0x5FFF) {

        } else if (address >= 0x6000 && address <= 0x7FFF) {

        } else {
            m_memory->Write(address, data);
        }
    }

};


class MemoryBankController4 : public MemoryController {

    MemoryBankController4(std::unique_ptr<Cartridge> cartridge);

    void Write(uint16_t address, uint8_t data) {

        if(address <= 0x1FFF) {

        } else if (address >= 0x2000 && address <= 0x2FFF) {

        } else if (address >= 0x3000 && address <= 0x3FFF) {

        } else if (address >= 0x4000 && address <= 0x5FFF) {

        } else {

        }
    }
};