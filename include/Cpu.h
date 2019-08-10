#pragma once

#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <bitset>

class MainMemory;

class Cpu {
public:

    using Byte = uint8_t;

    explicit Cpu(std::shared_ptr<std::vector<uint8_t>> MainMemory);

    void Execute();

private:

    void LoadRegister(Byte& to, const Byte& from);
    void Increment(Byte& reg);
    void Decrement(Byte& reg);

    uint16_t CombineRegisters(const Byte& high, const Byte& low) const;
    
    void AddRegisters(Byte& to, const Byte& from);
    void SubtractRegister(Byte& to, const Byte& from);
    void NoOperation();

    void AndWithA(const Byte& reg);
    void OrWithA(const Byte& reg);
    void XorWithA(const Byte& reg);


    void UnimplementedOperation(const std::string& message);

    Byte m_regA;
    Byte m_regB;
    Byte m_regC;
    Byte m_regD;
    Byte m_regE;
    std::bitset<8> m_regF;
    Byte m_regH;
    Byte m_regL;

    using StackPointer = uint16_t;
    using ProgramCounter = uint16_t;

    StackPointer m_stackPtr;
    ProgramCounter m_programCounter;

    std::shared_ptr<std::vector<uint8_t>> m_mainMemory;
};