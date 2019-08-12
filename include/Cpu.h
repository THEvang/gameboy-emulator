#pragma once

#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <bitset>

#include <MemoryMap.h>

class Cpu {
public:

    using Byte = uint8_t;

    explicit Cpu(std::shared_ptr<MemoryMap> mainMemory);

    void Execute();
    void ExecuteCB();

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

    void CompareWithA(const Byte& reg);

    void RotateRightThroughCarryFlag();
    void RotateLeftThroughCarryFlag();

    void ComplementA();
    void ComplementCarryFlag();
    void SetCarryFlag();

    void LDHNA();
    void LDHAN() {
        auto address = +0xFF00 + m_mainMemory->Read(m_programCounter + 1);

        m_regA = m_mainMemory->Read(address);

        m_programCounter++;
    };

    void Call();
    void Ret();

    void JumpRelativeNZ() {
        if (!m_regF.test(7)) {
            m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
        } else {
            m_programCounter += 2;
        }
    };

    void JumpRelativeNC() {
       if (!m_regF.test(4)) {
            m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
       } else {
           m_programCounter += 2;
       }
    }

    void JumpRelativeC() {
        if (m_regF.test(4)) {
            m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
       } else {
           m_programCounter += 2;
       }
    }

    void Pop(uint8_t& high, uint8_t& low) {
        high = m_mainMemory->Read(m_stackPtr + 1);
        low = m_mainMemory->Read(m_stackPtr);

        m_stackPtr += 2;
        m_programCounter++;
    };

    void Restart(uint8_t address) {
        m_mainMemory->Write(m_stackPtr, m_programCounter);
        m_stackPtr--;

        m_programCounter += 0x000 + address;
    };

    void RRA();

    void DisableInterrupts();


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

    std::shared_ptr<MemoryMap> m_mainMemory;
};