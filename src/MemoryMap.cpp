#include <MemoryMap.h>

MemoryMap::MemoryMap(const std::shared_ptr<Cartridge> cartridge) 
    : m_memory(0xFFFF) 
    , m_cartridge(cartridge) {

    auto cartridgeRom = m_cartridge->GetMemory();
    
    std::copy(cartridgeRom.begin(), cartridgeRom.begin() + 0x7FFF, m_memory.begin());

}

void MemoryMap::Write(const uint16_t address, const uint8_t value)
    {
        if (address <= 0x7FFF) {
            LoadRomBank(value);
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