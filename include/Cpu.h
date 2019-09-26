#pragma once

#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <bitset>

#include <MemoryMap.h>
#include <FlagRegister.h>

class Cpu {
public:

    using Byte = uint8_t;

    explicit Cpu(std::shared_ptr<MemoryMap> mainMemory);

    void Execute();
    void ExecuteCB();

private:

    void SetInitialState();

    void Add(uint8_t const value);
    void Add(uint16_t const address);

    void Load(uint8_t & reg); //Load from immediate value
    void Load(uint8_t & reg, uint8_t value); //Load from register
    void Load(uint8_t & reg, uint16_t address); //Load from address
    void Load(uint16_t const address, uint8_t const value); //Load to address
    void Load(std::pair<uint8_t&, uint8_t> registerPair); //Load immediate 16 bits to register pair

    void Or(); //Or with immediate byte 
    void Or(uint8_t const value); //Or with value
    void Or(uint16_t const addres); //Or with value at address
    void SetOrFlags(uint8_t const result);

    void Xor(); //Xor with immediate byte
    void Xor(uint8_t const value); //Xor with value
    void Xor(uint16_t const address); //Xor with value at address

    void And();
    void And(uint8_t const value);
    void And(uint16_t const address);
    void SetAndFlags(uint8_t const result);

    void Increment(uint8_t & value);
    void Increment(uint8_t & high, uint8_t & low);
    void SetIncrementFlags();

    void Decrement(uint8_t & value);
    void Decrement(uint8_t const address);
    void SetDecrementFlags();

    
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


    void CompareWithA(const Byte& reg);

    void RLCA();

    void RR(uint8_t reg) {
        
        m_flags.resetSubtract();
        m_flags.resetHalfCarry();

        uint8_t msb = 0;
        if(m_flags.carryFlag() == FlagState::Set) {
            msb = 0b10000000;
        }

        if( (reg & 0b00000001) == 1) { 
            m_flags.setCarry();
        } else {
            m_flags.resetCarry();
        }

        reg = reg >> 1;

        reg |= msb;
        
        if (reg == 0) {
            m_flags.setZero();
        }


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

        m_flags.resetSubtract();
        m_flags.resetHalfCarry();

        if( (reg & 0x0001) == 1) {
            m_flags.setCarry();
        } else {
            m_flags.resetCarry();
        }

        reg = reg >> 1;

        if(reg == 0) {
            m_flags.setZero();
        }
        
        m_programCounter++;
    }

    void SRL(uint8_t& reg) {
        
        m_flags.resetSubtract();
        m_flags.resetHalfCarry();

        if ((reg & 0x0001) == 1) {
            m_flags.setCarry();
        } else {
            m_flags.resetCarry();
        }

        reg = reg >> 1;
        reg = reg & 0b01111111;

        if(reg == 0) {
            m_flags.setZero();
        }

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
    void Pop(uint8_t& high, uint8_t& low);

    void Restart(uint8_t const address);

    void RRA();

    void DisableInterrupts();

    void UnimplementedOperation(std::string const & message) const;

    Byte m_regA;
    Byte m_regB;
    Byte m_regC;
    Byte m_regD;
    Byte m_regE;
    Byte m_regH;
    Byte m_regL;

    FlagRegister m_flags;

    using StackPointer = uint16_t;
    using ProgramCounter = uint16_t;

    StackPointer m_stackPtr;
    ProgramCounter m_programCounter;

    std::shared_ptr<MemoryMap> m_mainMemory;

    int m_cycles;
};