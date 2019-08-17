#include <MemoryMap.h>

MemoryMap::MemoryMap(const std::shared_ptr<Cartridge> cartridge) 
    : m_memory(0xFFFF) 
    , m_cartridge(cartridge) {

    auto cartridgeRom = m_cartridge->GetMemory();
    
    std::copy(cartridgeRom.begin(), cartridgeRom.begin() + 0x7FFF, m_memory.begin());

}

void MemoryMap::Write(const uint16_t address, const uint8_t value)
    {if (address <= 0x1FFF) {
            
            switch(value) {
                case 0x00:
                    m_externalRam = ExternalRam::Disabled;
                    break;
                case 0x0A:
                    m_externalRam = ExternalRam::Enabled;
                    break;
                default:
                    m_externalRam = ExternalRam::Disabled;
            }

        } else if (address >= 0x2000 && address <= 0x3FFF) {
            //Select lower 5 bit of rom bank number
            LoadRomBank(value);
        } else if (address >= 0x4000 && address <= 0x5FFF) {
            //Select either ram bank 0x00-0x03
            //Or specify upper two bits (5 - 6) of ROM Bank number
            //Dependent upon ROM/RAM mode
        } else {
            m_memory[address] = value;
        }
    }

uint8_t MemoryMap::Read(const uint16_t address) const {
    return m_memory[address];
}

void MemoryMap::LoadRomBank(int nr) {
    
    auto cartridgeRom = m_cartridge->GetMemory();

    std::copy(cartridgeRom.begin() + nr * (0x7FFF - 0x4000), cartridgeRom.begin() + (nr + 1) * (0x7FFF - 0x4000), m_memory.begin() + 0x4000);
}