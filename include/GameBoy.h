#pragma once

#include <bitset>
#include <vector>

#include <Cartridge.h>

class GameBoy {
public:

    using Byte = uint8_t;


    GameBoy();

    void InsertCartridge(const Cartridge&);
    void RemoveCartridge();

    void PowerOn();

    void PowerOff();

private:
    
    void Emulate();

    using StackPointer = uint16_t;
    using ProgramCounter = uint16_t;

    Byte m_regA;
    Byte m_regB;
    Byte m_regC;
    Byte m_regD;
    Byte m_regE;
    std::bitset<8> m_regF;
    Byte m_regH;
    Byte m_regL; 

    StackPointer m_stackpointer;
    ProgramCounter m_programCounter;

    std::vector<Byte> m_mainMemory;
};



