#pragma once 

#include <memory>
#include <vector>

#include <Cartridge.h>

class MemoryMap {
public:

    MemoryMap(const std::shared_ptr<Cartridge> cartridge);

    void Write(const uint16_t address, const uint8_t value);

    uint8_t Read(const uint16_t address) const;

private:

    void LoadRomBank(int nr);

    std::vector<uint8_t> m_memory;
    std::shared_ptr<Cartridge> m_cartridge;
};