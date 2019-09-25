#pragma once

#include <bitset>
#include <vector>
#include <memory>

#include <Cartridge.h>
#include <Cpu.h>
#include <MemoryMap.h>

class GameBoy {
public:

    using Byte = uint8_t;


    GameBoy() = default;

    void InsertCartridge(std::shared_ptr<Cartridge>);
    void RemoveCartridge();

    void PowerOn();

    void PowerOff();

private:

    std::shared_ptr<Cartridge> m_cartridge;

    std::shared_ptr<MemoryMap> m_mainMemory;

    std::unique_ptr<Cpu> m_cpu;
};



