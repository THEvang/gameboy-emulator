#include <MemoryMap.h>
#include <Logger.h>

MemoryMap::MemoryMap(std::shared_ptr<Cartridge> const & cartridge) 
    : m_memory(0xFFFF) 
    , m_cartridge(std::move(cartridge))
    , m_currentRomBank(0) 
    , m_currentRamBank(0)
{

    auto cartridgeRom = m_cartridge->GetMemory();
    
    std::copy(cartridgeRom.begin(), cartridgeRom.begin() + 0x7FFF, m_memory.begin());

}

void MemoryMap::Write(const uint16_t address, const uint8_t value)
    {
        if (address <= 0x1FFF) {
            switch(value) {
                case 0x0A:
                    Logger::Log(LogLevel::Debug, "Enabling External RAM");
                    m_externalRam = ExternalRam::Enabled;
                    break;
                default:
                    Logger::Log(LogLevel::Debug, "Disabling External RAM");
                    m_externalRam = ExternalRam::Disabled;
                    break;
            }

        } else if (address >= 0x2000 && address <= 0x3FFF) {
            Logger::Log(LogLevel::Debug, "Setting Lower 5 Bits of Rom Bank Number");
            //Select lower 5 bit of rom bank number
            LoadRomBank(value);
        } else if (address >= 0x4000 && address <= 0x5FFF) {
            switch(m_bankingMode) {
                case BankingMode::RomBanking:
                    Logger::Log(LogLevel::Debug, "Setting Bit 5 and 6 of the ROM Bank Number");

                    break;

                case BankingMode::RamBanking:
                    Logger::Log(LogLevel::Debug, "Setting RAM Bank Number");

                    break;
            }


        //Select either ram bank 0x00-0x03
        //Or specify upper two bits (5 - 6) of ROM Bank number
        //Dependent upon ROM/RAM mode

        } else if (address >= 0x6000 && address <= 0x7FFF) {
            switch(value) {
                case 0x00:
                    Logger::Log(LogLevel::Debug, "Setting Bankingmode to ROMBanking");
                    m_bankingMode = BankingMode::RomBanking;
                    break;
                case 0x01:
                    Logger::Log(LogLevel::Debug, "Setting Bankingmode to RAMBankin");
                    m_bankingMode = BankingMode::RamBanking;
                    break;
            }
        } 
        
        else {
            m_memory[address] = value;
        }
    }

uint8_t MemoryMap::Read(uint16_t const address) const {
    return m_memory[address];
}

void MemoryMap::LoadRomBank(int nr) {

    if (nr == 0) {
        nr++;
    }
    auto cartridgeRom = m_cartridge->GetMemory();

    std::copy(cartridgeRom.begin() + nr * (0x7FFF - 0x4000), cartridgeRom.begin() + (nr + 1) * (0x7FFF - 0x4000), m_memory.begin() + 0x4000);
}