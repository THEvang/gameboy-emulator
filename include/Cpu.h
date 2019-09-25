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

    void SetInitialState();

    void LoadFromImmediateByte(uint8_t& to);
    void LoadFromRegister(uint8_t& to, uint8_t from);
    void LoadFromAddress(Byte& to, uint16_t address);
    
    void LoadToRegister(Byte& to, const Byte& from);
    void LoadToAddress(uint16_t address, uint8_t value);
    void LoadImmediate16BitValue(uint8_t& high, uint8_t& low);
    void LoadImmediate16BitValue(uint16_t& to);

    void LoadStackPointerFromHL();
    
    void IncrementRegister(Byte& reg);

    void IncrementAtAddress(uint16_t address);

    void IncrementRegisterPair(uint8_t& high, uint8_t& low);
    void IncrementStackpointer();

    void DecrementRegisterPair(uint8_t& high, uint8_t& low);
    void DecrementStackPointer();

    void DecrementRegister(Byte& reg);
    void DecrementAtAddress(uint16_t address);

    uint16_t CombineRegisters(const Byte& high, const Byte& low) const;
    
    void AddRegisters(Byte& to, const Byte& from);
    void SubtractFromA(uint8_t value);
    void SubtractImmediateByte();
    void SubtractFromAddress(uint16_t address);

    void NoOperation();

    void AndWithA(const Byte& reg);
    void OrWithA(const Byte& reg);
    void XorWithA(const Byte& reg);

    void CompareWithA(const Byte& reg);

    void RLCA();

    void RR(uint8_t reg) {
        
        uint8_t msb = 0;
        if(m_regF.test(4)) {
            msb = 0b10000000;
        }

        if( (reg & 0b00000001) == 1) { 
            m_regF.set(4);
        } else {
            m_regF.reset(4);
        }

        reg = reg >> 1;

        reg |= msb;
        
        if (reg == 0) {
            m_regF.set(7);
        }

        m_regF.reset(6);
        m_regF.reset(5);

        m_programCounter++;
    }

    void RotateLeftThroughCarryFlag() {

        m_programCounter++;
    }

    void LDIA() {
        uint16_t address = CombineRegisters(m_regH, m_regL);

        m_regA = m_mainMemory->Read(address);

        address++;

        m_regH = (address >> 8);
        m_regL = address;

        m_programCounter++; 
        m_cycles += 8;
    }

    void LDIHL() {
        uint16_t address = CombineRegisters(m_regH, m_regL);
        m_mainMemory->Write(address, m_regA);

        address++;
        m_regH = (address >> 8);
        m_regL = address;

        m_programCounter++;
    }

    void SRA(uint8_t& reg) {

        if( (reg & 0x0001) == 1) {
            m_regF.set(4);
        } else {
            m_regF.reset(4);
        }

        reg = reg >> 1;

        if(reg == 0) {
            m_regF.set(7);
        }
        m_regF.reset(6);
        m_regF.reset(5);

        m_programCounter++;
    }

    void SRL(uint8_t& reg) {
        
        if ((reg & 0x0001) == 1) {
            m_regF.set(4);
        } else {
            m_regF.reset(4);
        }

        reg = reg >> 1;
        reg = reg & 0b01111111;

        if(reg == 0) {
            m_regF.set(7);
        }

        m_regF.reset(6);
        m_regF.reset(5);

        m_programCounter++;
    }

    void ComplementA();
    void ComplementCarryFlag();
    void SetCarryFlag();

    void LDHNA();
    void LDHAN();

    void Call();
    void Ret();
    void RetNZ();
    void RetZ();
    void RetNC();
    void RetC();

    void Jump();
    void JumpRelative();
    void JumpRelativeZ();
    void JumpRelativeNZ();
    void JumpRelativeNC();
    void JumpRelativeC();

    void Push(uint8_t high, uint8_t low);
    void Push(uint8_t high, std::bitset<8> low);
    void Pop(uint8_t& high, uint8_t& low);
    void Pop(uint8_t& high, std::bitset<8>& low)
    {
        uint8_t highByte = 0;
        uint8_t lowByte = 0;
        Pop(highByte, lowByte);

        high = highByte;
        low = std::bitset<8>(lowByte);
    }

    void Restart(uint8_t const address);

    void RRA();

    void DisableInterrupts();

    void UnimplementedOperation(std::string const & message) const;

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

    int m_cycles;
};