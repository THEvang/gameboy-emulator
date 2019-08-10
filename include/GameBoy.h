#pragma once

#include <bitset>
#include <vector>
#include <memory>

#include <Cartridge.h>
#include <Cpu.h>

class GameBoy {
public:

    using Byte = uint8_t;


    GameBoy();

    void InsertCartridge(std::unique_ptr<Cartridge>);
    void RemoveCartridge();

    void PowerOn();

    void PowerOff();

private:

    std::unique_ptr<Cartridge> m_cartridge;

    std::shared_ptr<std::vector<Byte>> m_mainMemory;

    Cpu m_cpu;
};



