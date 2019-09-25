#include <Cpu.h>

#include <iostream>
#include <Logger.h>
#include <Opcodes.h>

Cpu::Cpu(std::shared_ptr<MemoryMap> mainMemory)
    : m_mainMemory(mainMemory) 
{
    SetInitialState();
}

void Cpu::SetInitialState() {

    m_programCounter = 0x0100;
    m_stackPtr = 0xFFFE;

    m_regA = 0x01;
    m_regF = std::bitset<8>(0xB0);
    m_regB = 0x00;
    m_regC = 0x13;
    m_regD = 0x00;
    m_regE = 0xD8;
    m_regH = 0x01;
    m_regL = 0x4D;

    m_mainMemory->Write(0xFF05, 0x00);
    m_mainMemory->Write(0xFF06, 0x00);
    m_mainMemory->Write(0xFF07, 0x00);

    m_mainMemory->Write(0xFF10, 0x80);
    m_mainMemory->Write(0xFF11, 0xBF);
    m_mainMemory->Write(0xFF12, 0xF3);

    m_mainMemory->Write(0xFF14, 0xBF);

    m_mainMemory->Write(0xFF16, 0x3F);
    m_mainMemory->Write(0xFF17, 0x00);
    
    m_mainMemory->Write(0xFF19, 0xBF);
    m_mainMemory->Write(0xFF1A, 0x7F);
    m_mainMemory->Write(0xFF1B, 0xFF);
    m_mainMemory->Write(0xFF1C, 0x9F);
    m_mainMemory->Write(0xFF1E, 0xBF);
    m_mainMemory->Write(0xFF20, 0xFF);
    m_mainMemory->Write(0xFF21, 0x00);
    m_mainMemory->Write(0xFF22, 0x00);

    m_mainMemory->Write(0xFF23, 0xBF);
    m_mainMemory->Write(0xFF24, 0x77);
    m_mainMemory->Write(0xFF25, 0xF3);
    m_mainMemory->Write(0xFF26, 0xF1);
    m_mainMemory->Write(0xFF40, 0x91);
    m_mainMemory->Write(0xFF42, 0x00);
    m_mainMemory->Write(0xFF43, 0x00);

    m_mainMemory->Write(0xFF45, 0x00);
    m_mainMemory->Write(0xFF47, 0xFC);
    m_mainMemory->Write(0xFF48, 0xFF);
    m_mainMemory->Write(0xFF49, 0xFF);
    m_mainMemory->Write(0xFF4A, 0x00);
    m_mainMemory->Write(0xFF4B, 0x00);
    m_mainMemory->Write(0xFFFF, 0x00);
}

void Cpu::Execute() {

    Byte opcode = m_mainMemory->Read(m_programCounter);

    Logger::Log(LogLevel::Debug, "Program counter: \t" + std::to_string(m_programCounter));
    Logger::Log(LogLevel::Debug, "Opcode: \t" + std::to_string(opcode));
    
    Logger::Log(LogLevel::Debug, "Register A: \t" + std::to_string(m_regA));
    Logger::Log(LogLevel::Debug, "Register B: \t" + std::to_string(m_regB));
    Logger::Log(LogLevel::Debug, "Register C: \t" + std::to_string(m_regC));
    Logger::Log(LogLevel::Debug, "Register D: \t" + std::to_string(m_regD));
    Logger::Log(LogLevel::Debug, "Register E: \t" + std::to_string(m_regE));
    Logger::Log(LogLevel::Debug, "Register H: \t" + std::to_string(m_regH));
    Logger::Log(LogLevel::Debug, "Register L: \t" + std::to_string(m_regL));

    Logger::Log(LogLevel::Debug, std::to_string(m_mainMemory->Read(0xFF01)));

    switch(static_cast<Opcode>(opcode)) {
        case Opcode::NOP:
            NoOperation();
            break;

        case Opcode::LD_BC_D16:
            LoadImmediate16BitValue(m_regB, m_regC);
            break;

        case Opcode::LD_ADDR_BC_A:
            LoadToAddress(CombineRegisters(m_regB, m_regC), m_regA);
            break;

        case Opcode::INC_BC:
            IncrementRegisterPair(m_regB, m_regC);
            break;
        
        case Opcode::INC_B:
            IncrementRegister(m_regB);
            break;
        
        case Opcode::DEC_B:
            DecrementRegister(m_regB);
            break;

        case Opcode::LD_B_D8:
            LoadFromImmediateByte(m_regB);
            break;
        
        case Opcode::RLCA:
            RLCA();
            break;

        case Opcode::LD_ADDR_A16_SP:
            UnimplementedOperation("LD (a16), SP");
            m_programCounter += 3;
            break;

        case Opcode::ADD_HL_BC:
            UnimplementedOperation("ADD HL, BC");
            m_programCounter++;
            break;

        case Opcode::LD_A_ADDR_BC:
            LoadFromAddress(m_regA, CombineRegisters(m_regB, m_regC));
            break;

        case Opcode::DEC_BC:
            DecrementRegisterPair(m_regB, m_regC);
            break;
        
        case Opcode::INC_C:
            IncrementRegister(m_regC);
            break;
        
        case Opcode::DEC_C:
            DecrementRegister(m_regC);
            break;
        
        case Opcode::LD_C_D8:
            LoadFromImmediateByte(m_regC);
            break;
        
        case Opcode::RRCA:
            UnimplementedOperation("RRCA");
            m_programCounter++;
            break;
        
        case Opcode::STOP:
            UnimplementedOperation("STOP");
            m_programCounter++;
            break;

        case Opcode::LD_DE_D16:
            LoadImmediate16BitValue(m_regD, m_regE);
            break;
        
        case Opcode::LD_ADDR_DE_A:
            LoadToAddress(CombineRegisters(m_regD, m_regE), m_regA);
            break;
        
        case Opcode::INC_DE:
            IncrementRegisterPair(m_regD, m_regE);
            break;
        
        case Opcode::INC_D:
            IncrementRegister(m_regD);
            break;
        
        case Opcode::DEC_D:
            DecrementRegister(m_regD);
            break;
        
        case Opcode::LD_D_D8:
            LoadFromImmediateByte(m_regD);
            break;
        
        case Opcode::RLA:
            UnimplementedOperation("RLA");
            m_programCounter++;
            break;

        case Opcode::JR_R8:
            JumpRelative();
            break;
        
        case Opcode::ADD_HL_DE:
            UnimplementedOperation("ADD, HL, DE");
            m_programCounter++;
            break;
        
        case Opcode::LD_A_ADDR_DE:
            LoadFromAddress(m_regA, CombineRegisters(m_regD, m_regE));
            break;
        
        case Opcode::DEC_DE:
            DecrementRegisterPair(m_regD, m_regE);
            break;
        
        case Opcode::INC_E:
            IncrementRegister(m_regE);
            break;

        case Opcode::DEC_E:
            DecrementRegister(m_regE);
            break;
        
        case Opcode::LD_E_D8:
            LoadFromImmediateByte(m_regE);
            break;
        
        case Opcode::RRA:
            RR(m_regA);
            break;

        case Opcode::JR_NZ_R8:
            JumpRelativeNZ();
            break;
        
        case Opcode::LD_HL_D16:
            LoadImmediate16BitValue(m_regH, m_regL);
            break;
        
        case Opcode::LD_ADDR_HLI_A:
            LDIHL();
            break;
        
        case Opcode::INC_HL:
            IncrementRegisterPair(m_regH, m_regL);
            break;

        case Opcode::INC_H:
            IncrementRegister(m_regH);
            break;
        
        case Opcode::DEC_H:
            DecrementRegister(m_regH);
            break;
        
        case Opcode::LD_H_D8:
            LoadFromImmediateByte(m_regH);
            break;
        
        case Opcode::DAA:
            UnimplementedOperation("DAA");
            m_programCounter++;
            break;
        
        case Opcode::JR_Z_R8:
            JumpRelativeZ();
            break;

        case Opcode::ADD_HL_HL:
            UnimplementedOperation("ADD HL, HL");
            m_programCounter++;
            break;
        
        case Opcode::LD_A_ADDR_HLI:
            LDIA();
            break;
        
        case Opcode::DEC_HL:
            DecrementRegisterPair(m_regH, m_regL);
            break;
        
        case Opcode::INC_L:
            IncrementRegister(m_regL);
            break;
        
        case Opcode::DEC_L:
            DecrementRegister(m_regL);
            break;
        
        case Opcode::LD_L_D8:
            LoadFromImmediateByte(m_regL);
            break;
        
        case Opcode::CPL:
            ComplementA();
            break;
        
        case Opcode::JR_NC_R8:
            JumpRelativeNC();
            break;
        
        case Opcode::LD_SP_D16:
            LoadImmediate16BitValue(m_stackPtr);
            break;
        
        case Opcode::LD_ADDR_HLD_A:
            UnimplementedOperation("LD (HL-), A");
            m_programCounter++;
            break;
        
        case Opcode::INC_SP:
            IncrementStackpointer();
            break;
        
        case Opcode::INC_ADDR_HL:
            IncrementAtAddress(CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::DEC_ADDR_HL:
            DecrementAtAddress(CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_ADDR_HL_D8:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
            }
        
        case Opcode::SCF:
            SetCarryFlag();
            break;
        
        case Opcode::JR_C_R8:
            JumpRelativeC();
            break;
        
        case Opcode::ADD_HL_SP:
            UnimplementedOperation("ADD HL, SP");
            break;
        
        case Opcode::LD_A_ADDR_HLD:
            UnimplementedOperation("LD A, (HL-)");
            break;
        
        case Opcode::DEC_SP:
            DecrementStackPointer();
            break;
        
        case Opcode::INC_A:
            IncrementRegister(m_regA);
            break;
        
        case Opcode::DEC_A:
            DecrementRegister(m_regA);
            break;
        
        case Opcode::LD_A_D8:
            LoadFromImmediateByte(m_regA);
            break;

        case Opcode::CCF:
            ComplementCarryFlag();
            break;
        
        case Opcode::LD_B_B:
            LoadFromRegister(m_regB, m_regB);
            break;
        
        case Opcode::LD_B_C:
            LoadFromRegister(m_regB, m_regC);
            break;
        
        case Opcode::LD_B_D:
            LoadFromRegister(m_regB, m_regD);
            break;
        
        case Opcode::LD_B_E:
            LoadFromRegister(m_regB, m_regE);
            break;
        
        case Opcode::LD_B_H:
            LoadFromRegister(m_regB, m_regH);
            break;
        
        case Opcode::LD_B_L:
            LoadFromRegister(m_regB, m_regL);
            break;
        
        case Opcode::LD_B_ADDR_HL:
            LoadFromAddress(m_regB, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_B_A:
            LoadFromRegister(m_regB, m_regA);
            break;
        
        case Opcode::LD_C_B:
            LoadFromRegister(m_regC, m_regB);
            break;
        
        case Opcode::LD_C_C:
            LoadFromRegister(m_regC, m_regC);
            break;
        
        case Opcode::LD_C_D:
            LoadFromRegister(m_regC, m_regD);
            break;
        
        case Opcode::LD_C_E:
            LoadFromRegister(m_regC, m_regE);
            break;
        
        case Opcode::LD_C_H:
            LoadFromRegister(m_regC, m_regH);
            break;
        
        case Opcode::LD_C_L:
            LoadFromRegister(m_regC, m_regL);
            break;
        
        case Opcode::LD_C_ADDR_HL:
            LoadFromAddress(m_regC, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_C_A:
            LoadFromRegister(m_regC, m_regA);
            break;

        case Opcode::LD_D_B:
            LoadFromRegister(m_regD, m_regB);
            break;

        case Opcode::LD_D_C:
            LoadFromRegister(m_regD, m_regC);
            break;

        case Opcode::LD_D_D:
            LoadFromRegister(m_regD, m_regD);
            break;

        case Opcode::LD_D_E:
            LoadFromRegister(m_regD, m_regE);
            break;

        case Opcode::LD_D_H:
            LoadFromRegister(m_regD, m_regH);
            break;

        case Opcode::LD_D_L:
            LoadFromRegister(m_regD, m_regL);
            break;

        case Opcode::LD_D_ADDR_HL:
            LoadFromAddress(m_regD, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_D_A:
            LoadFromRegister(m_regD, m_regA);
            break;

        case Opcode::LD_E_B:
            LoadFromAddress(m_regE, m_regB);
            break;

        case Opcode::LD_E_C:
            LoadFromRegister(m_regE, m_regC);
            break;

        case Opcode::LD_E_D:
            LoadFromRegister(m_regE, m_regD);
            break;

        case Opcode::LD_E_E:
            LoadFromRegister(m_regE, m_regE);
            break;

        case Opcode::LD_E_H:
            LoadFromRegister(m_regE, m_regH);
            break;

        case Opcode::LD_E_L:
            LoadFromRegister(m_regE, m_regL);
            break;

        case Opcode::LD_E_ADDR_HL:
            LoadFromAddress(m_regE, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_E_A:
            LoadFromRegister(m_regE, m_regA);
            break;

        case Opcode::LD_H_B:
            LoadFromRegister(m_regH, m_regB);
            break;

        case Opcode::LD_H_C:
            LoadFromRegister(m_regH, m_regC);
            break;

        case Opcode::LD_H_D:
            LoadFromRegister(m_regH, m_regD);
            break;

        case Opcode::LD_H_E:
            LoadFromRegister(m_regH, m_regE);
            break;

        case Opcode::LD_H_H:
            LoadFromRegister(m_regH, m_regH);
            break;

        case Opcode::LD_H_L:
            LoadFromRegister(m_regH, m_regL);
            break;

        case Opcode::LD_H_ADDR_HL:
            LoadFromAddress(m_regH, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_H_A:
            LoadFromRegister(m_regH, m_regA);
            break;

        case Opcode::LD_L_B: 
            LoadFromRegister(m_regL, m_regB);
            break;
        
        case Opcode::LD_L_C:
            LoadFromRegister(m_regL, m_regC);
            break;
        
        case Opcode::LD_L_D:
            LoadFromRegister(m_regL, m_regD);
            break;
        
        case Opcode::LD_L_E:
            LoadFromRegister(m_regL, m_regE);
            break;
        
        case Opcode::LD_L_H:
            LoadFromRegister(m_regL, m_regH);
            break;
        
        case Opcode::LD_L_L:
            LoadFromRegister(m_regL, m_regL);
            break;
        
        case Opcode::LD_L_ADDR_HL:
            LoadFromAddress(m_regL, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_L_A:
            LoadFromRegister(m_regL, m_regA);
            break;
        
        case Opcode::LD_ADDR_HL_B:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regB);
            break;

        case Opcode::LD_ADDR_HL_C:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regC);
            break;

        case Opcode::LD_ADDR_HL_D:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regD);
            break;
        
        case Opcode::LD_ADDR_HL_E:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regE); 
            break;
        
        case Opcode::LD_ADDR_HL_H:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regH);
            break;
        
        case Opcode::LD_ADDR_HL_L:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regL);
            break;
        
        case Opcode::HALT:
            UnimplementedOperation("HALT");
            m_programCounter++;
            break;
        
        case Opcode::LD_ADDR_HL_A:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regA);
            break;

        case Opcode::LD_A_B:
            LoadFromRegister(m_regA, m_regB);
            break;
        
        case Opcode::LD_A_C:
            LoadFromRegister(m_regA, m_regC);
            break;
        
        case Opcode::LD_A_D:
            LoadFromRegister(m_regA, m_regD);
            break;
        
        case Opcode::LD_A_E:
            LoadFromRegister(m_regA, m_regE);
            break;
        
        case Opcode::LD_A_H:
            LoadFromRegister(m_regA, m_regH);
            break;
        
        case Opcode::LD_A_L:
            LoadFromRegister(m_regA, m_regL);
            break;
        
        case Opcode::LD_A_ADDR_HL:
            LoadFromAddress(m_regA, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_A_A:
            LoadFromRegister(m_regA, m_regA);
            break;
        
        case Opcode::ADD_A_B:
            AddRegisters(m_regA, m_regB);
            break;
        
        case Opcode::ADD_A_C:
            AddRegisters(m_regA, m_regC);
            break;
        
        case Opcode::ADD_A_D:
            AddRegisters(m_regA, m_regD);
            break;

        case Opcode::ADD_A_E:
            AddRegisters(m_regA, m_regE);
            break;
        
        case Opcode::ADD_A_H:
            AddRegisters(m_regA, m_regH);
            break;
        
        case Opcode::ADD_A_L:
            AddRegisters(m_regA, m_regL);
            break;
        
        case Opcode::ADD_A_ADDR_HL:
            UnimplementedOperation("ADD A, (HL)");
            break;
            
        case Opcode::ADD_A_A:
            AddRegisters(m_regA, m_regA);
            break;

        case Opcode::ADC_A_B:
            UnimplementedOperation("ADC A, B");
            m_programCounter++;
            break;

        case Opcode::ADC_A_C:
            UnimplementedOperation("ADC, A, C");
            break;

        case Opcode::ADC_A_D:
            UnimplementedOperation("ADC A, D");
            break;
        
        case Opcode::ADC_A_E:
            UnimplementedOperation("ADC A, E");
            break;
        
        case Opcode::ADC_A_H:
            UnimplementedOperation("ADC A, H");
            break;
        
        case Opcode::ADC_A_L:
            UnimplementedOperation("ADC, A, L");
            break;
        
        case Opcode::ADC_A_ADDR_HL:
            UnimplementedOperation("ADC A, (HL)");
            break;
        
        case Opcode::ADC_A_A:
            UnimplementedOperation("ADC A, A");
            break;
        
        case Opcode::SUB_B:
            SubtractFromA(m_regB);
            break;
        
        case Opcode::SUB_C:
            SubtractFromA(m_regC);
            break;
        
        case Opcode::SUB_D:
            SubtractFromA(m_regD);
            break;
        
        case Opcode::SUB_E:
            SubtractFromA(m_regE);
            break;
        
        case Opcode::SUB_H:
            SubtractFromA(m_regH);
            break;
        
        case Opcode::SUB_L:
            SubtractFromA(m_regL);
            break;
        
        case Opcode::SUB_ADDR_HL:
            UnimplementedOperation("SUB (HL)");
            break;
        
        case Opcode::SUB_A:
            SubtractFromA(m_regA);
            break;
        
        case Opcode::SBC_A_B:
            UnimplementedOperation("SBC A, B");
            break;
        
        case Opcode::SBC_A_C:
            UnimplementedOperation("SBC A, C");
            break;
        
        case Opcode::SBC_A_D:
            UnimplementedOperation("SBC A, D");
            break;
        
        case Opcode::SBC_A_E:
            UnimplementedOperation("SBC A, E");
            break;
        
        case Opcode::SBC_A_H:
            UnimplementedOperation("SBC A, H");
            break;
        
        case Opcode::SBC_A_L:
            UnimplementedOperation("SBC, A, L");
            break;
        
        case Opcode::SBC_A_ADDR_HL:
            UnimplementedOperation("SBC A, (HL)");
            break;

        case Opcode::SBC_A_A:
            UnimplementedOperation("SBC A, A");
            break;
        
        case Opcode::AND_B:
            AndWithA(m_regB);
            m_programCounter++;
            break;
        
        case Opcode::AND_C:
            AndWithA(m_regC);
            m_programCounter++;
            break;
        
        case Opcode::AND_D:
            AndWithA(m_regD);
            m_programCounter++;
            break;
        
        case Opcode::AND_E:
            AndWithA(m_regE);
            m_programCounter++;
            break;
        
        case Opcode::AND_H:
            AndWithA(m_regH);
            m_programCounter++;
            break;
        
        case Opcode::AND_L:
            AndWithA(m_regL);
            m_programCounter++;
            break;
        
        case Opcode::AND_ADDR_HL:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            AndWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case Opcode::AND_A:
            AndWithA(m_regA);
            m_programCounter++;
            break;
        
        case Opcode::XOR_B:
            XorWithA(m_regB);
            m_programCounter++;
            break;
        
        case Opcode::XOR_C:
            XorWithA(m_regC);
            m_programCounter++;
            break;
        
        case Opcode::XOR_D:
            XorWithA(m_regD);
            m_programCounter++;
            break;
        
        case Opcode::XOR_E:
            XorWithA(m_regE);
            m_programCounter++;
            break;
        
        case Opcode::XOR_H:
            XorWithA(m_regH);
            m_programCounter++;
            break;
        
        case Opcode::XOR_L:
            XorWithA(m_regL);
            m_programCounter++;
            break;
        
        case Opcode::XOR_ADDR_HL:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            XorWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case Opcode::XOR_A:
            XorWithA(m_regA);
            m_programCounter++;
            break;
        
        case Opcode::OR_B:
            OrWithA(m_regB);
            m_programCounter++;
            break;
        
        case Opcode::OR_C:
            OrWithA(m_regC);
            m_programCounter++;
            break;
        
        case Opcode::OR_D:
            OrWithA(m_regD);
            m_programCounter++;
            break;
        
        case Opcode::OR_E:
            OrWithA(m_regE);
            m_programCounter++;
            break;
        
        case Opcode::OR_H:
            OrWithA(m_regH);
            m_programCounter++;
            break;
        
        case Opcode::OR_L:
            OrWithA(m_regL);
            m_programCounter++;
            break;
        
        case Opcode::OR_ADDR_HL:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            OrWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case Opcode::OR_A:
            OrWithA(m_regA);
            m_programCounter++;
            break;
        
        case Opcode::CP_B:
            CompareWithA(m_regB);
            m_programCounter++;
            break;
        
        case Opcode::CP_C:
            CompareWithA(m_regC);
            m_programCounter++;
            break;
        
        case Opcode::CP_D:
            CompareWithA(m_regD);
            m_programCounter++;
            break;
        
        case Opcode::CP_E:
            CompareWithA(m_regE);
            m_programCounter++;
            break;
        
        case Opcode::CP_H:
            CompareWithA(m_regH);
            m_programCounter++;
            break;
        
        case Opcode::CP_L:
            CompareWithA(m_regL);
            m_programCounter++;
            break;
        
        case Opcode::CP_ADDR_HL:
            UnimplementedOperation("CP (HL)");
            break;
        
        case Opcode::CP_A:
            CompareWithA(m_regA);
            m_programCounter++;
            break;
        
        case Opcode::RET_NZ:
            RetNZ();
            break;
        
        case Opcode::POP_BC:
            Pop(m_regB, m_regC);
            break;
        
        case Opcode::JP_NZ_A16:
            UnimplementedOperation("JP NZ, a16");
            break;
        
        case Opcode::JP_A16:
            Jump();
            break;
        
        case Opcode::CALL_NZ_A16:
            UnimplementedOperation("CALL NZ, a16");
            break;
        
        case Opcode::PUSH_BC:
            Push(m_regB, m_regC);
            break;
        
        case Opcode::ADD_A_D8:
            UnimplementedOperation("ADD A, n");
            break;
        
        case Opcode::RST_00H:
            Restart(0x00);
            break;
        
        case Opcode::RET_Z:
            UnimplementedOperation("RET Z");
            break;
        
        case Opcode::RET:
            Ret();
            break;
        
        case Opcode::JP_Z_A16:
            UnimplementedOperation("JP Z, a16");
            break;
        
        case Opcode::PREFIX_CB:
            m_programCounter++;
            ExecuteCB();
            break;
        
        case Opcode::CALL_Z_A16: 
            UnimplementedOperation("CALL Z, a16");
            break;
        
        case Opcode::CALL_A16:
            Call();
            break;
        
        case Opcode::ADC_A_D8:
            UnimplementedOperation("ADC A, d8");
            break;
        
        case Opcode::RST_08H:
            Restart(0x08);
            break;
        
        case Opcode::RET_NC:
            UnimplementedOperation("RET NC");
            break;
        
        case Opcode::POP_DE:
            Pop(m_regD, m_regE);
            break;
        
        case Opcode::JP_NC_A16:
            UnimplementedOperation("JP NC, a16");
            break;
        
        case Opcode::CALL_NC_A16:
            UnimplementedOperation("CALL NC, a16");
            break;
        
        case Opcode::PUSH_DE:
            Push(m_regD, m_regE);
            break;
        
        case Opcode::SUB_D8:
            SubtractImmediateByte();
            break;
        
        case Opcode::RST_10H:
            Restart(0x10);
            break;
        
        case Opcode::RET_C:
            UnimplementedOperation("RET C");
            break;
        
        case Opcode::RETI:
            UnimplementedOperation("RETI");
            break;
        
        case Opcode::JP_C_A16:
            UnimplementedOperation("JP C, a16");
            break;
        
        case Opcode::CALL_C_A16:
            UnimplementedOperation("CALL C, a16");
            break;
        
        case Opcode::SBC_A_D8:
            UnimplementedOperation("SBC A, d8");
            break;
        
        case Opcode::RST_18H:
            Restart(0x18);
            break;
        
        case Opcode::LDH_ADDR_A8_A:
            {
                uint16_t address = 0xFF00 + m_mainMemory->Read(m_programCounter + 1);
                m_mainMemory->Write(address, m_regA);
                m_programCounter += 2;
            }
            break;
        
        case Opcode::POP_HL:
            Pop(m_regH, m_regL);
            break;
        
        case Opcode::LD_ADDR_C_A:
            UnimplementedOperation("LD (C), A");
            break;
        
        
        case Opcode::PUSH_HL:
            Push(m_regH, m_regL);
            break;
        
        case Opcode::AND_D8:
            AndWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case Opcode::RST_20H:
            Restart(0x20);
            break;
        
        case Opcode::ADD_SP_R8:
            UnimplementedOperation("ADD SP, r8");
            break;
        
        case Opcode::JP_ADDR_HL:
            UnimplementedOperation("JP (HL)");
            break;
        
        case Opcode::LD_ADDR_A16_A:
            {
            auto address = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter +1));
            m_mainMemory->Write(address, m_regA);
            m_programCounter += 3;
            m_cycles += 16;
            break;
            }

        case Opcode::XOR_D8:
            XorWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case Opcode::RST_28H:
            Restart(0x28);
            break;
        
        case Opcode::LDH_A_ADDR_A8:
            LDHAN();
            m_programCounter++;
            break;
        
        case Opcode::POP_AF:
            Pop(m_regA, m_regF);
            break;
        
        case Opcode::LD_A_ADDR_C:
            UnimplementedOperation("LD A, (C)");
            break;
        
        case Opcode::DI:
            DisableInterrupts();
            break;
        
        case Opcode::PUSH_AF:
            Push(m_regA, m_regF);
            break;
        
        case Opcode::OR_D8:
            OrWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case Opcode::RST_30H:
            Restart(0x30);
            break;
        
        case Opcode::LD_HL_SPR8:
            UnimplementedOperation("LD HL, SP+r8");
            break;
        
        case Opcode::LD_SP_HL:
            LoadStackPointerFromHL();
            break;
        
        case Opcode::LD_A_ADDR_A16:
            {
            auto address = CombineRegisters(m_programCounter + 2, m_programCounter + 1);
            m_regA = m_mainMemory->Read(address);
            m_programCounter += 3;
            }
            break;
        
        case Opcode::EI:
            UnimplementedOperation("EI");
            break;
        
        case Opcode::CP_D8:
            CompareWithA(m_mainMemory->Read(m_programCounter+1));
            m_programCounter += 2;
            break;
        
        case Opcode::RST_38H:
            Restart(0x38);
            break;

        default:
            UnimplementedOperation("Invalid Opcode");
    }

}

void Cpu::NoOperation() {
    m_programCounter++;
    return;
}

void Cpu::LoadToRegister(Byte& to, const Byte& from) {
    to = from;
}

void Cpu::IncrementRegister(Byte& reg) {

    if ( (((reg & 0xf) + (1 & 0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    }

    reg++;

    if (reg == 0) {
        m_regF.set(7);
    }


    m_regF.reset(6);
 
    m_programCounter++;
    m_cycles += 4;
}

void Cpu::DecrementRegister(Byte& reg) {
    
    Logger::Log(LogLevel::Debug, "Decrement register");

    if((((reg  & 0x0f) - (1 & 0x0f)) & 0x10) == 0x10) {
        m_regF.set(5);
    } 

    reg--;

    if (reg == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);
    
    // Set if no borrow from bit 4

    m_programCounter++;
    m_cycles += 4;
}

uint16_t Cpu::CombineRegisters(const Byte& high, const Byte& low) const {

    uint16_t combinedRegister = (high << 8) | low;

    return combinedRegister;
}

void Cpu::AddRegisters(Byte& to, const Byte& from) {

    if ( (((to & 0xf) + ( (from +1) &0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    } 

    if( (static_cast<int>(to) + static_cast<int>(from)) > 0xFF) {
        m_regF.set(4);
    }

    if(to == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);

    to += from;

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::SubtractFromA(uint8_t value) {

    Logger::Log(LogLevel::Debug, "Subtract Register from A");
    if (value > m_regA) {
        m_regF.set(4);
    }

    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);

    m_programCounter++;
    m_cycles += 8;
    //Check borrow from 4 bit

}

void Cpu::SubtractFromAddress(uint16_t address) {

    Logger::Log(LogLevel::Debug, "Subtract address from A");

    auto value = m_mainMemory->Read(address);    

    if (value > m_regA) {
        m_regF.set(4);
    }

    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);


    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_cycles += 8;
    m_programCounter++;
}

void Cpu::SubtractImmediateByte() {

    Logger::Log(LogLevel::Debug, "Subtract n From A");

    auto value = m_mainMemory->Read(m_programCounter + 1);
    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);

    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::UnimplementedOperation(const std::string& operation) {

    Logger::Log(LogLevel::Error, "Unimplemented operation: \t" + operation);
    std::cin.get();
}

void Cpu::AndWithA(const Byte& reg) {
    m_regA &= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.set(5);
    m_regF.reset(4);
}

void Cpu::OrWithA(const Byte& reg) {
    m_regA |= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);
    m_regF.reset(4);
}

void Cpu::XorWithA(const Byte& reg) {
    m_regA ^= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);
    m_regF.reset(4);
}

void Cpu::CompareWithA(const Byte& reg) {

    Logger::Log(LogLevel::Debug, "Compare register with A");

    if(m_regA == reg) {
        m_regF.set(7);
    }

    m_regF.set(6);

    //Set H if no borrow from bit 4

    if(m_regA < reg) {
        m_regF.set(4);
    }
}

void Cpu::DisableInterrupts() {
    
    m_programCounter++;
}

 
 void Cpu::ComplementA() {

    m_regA = ~m_regA;

    m_regF.set(6);
    m_regF.set(5);

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::ComplementCarryFlag() {

    m_regF.flip(4);

    m_regF.reset(6);
    m_regF.reset(5);

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::SetCarryFlag() {
     
     m_regF.set(4);
     m_regF.reset(6);
     m_regF.reset(5);

     m_programCounter++;
     m_cycles += 4;
 }

 void Cpu::Call() {

    auto address = m_programCounter + 3;

    m_mainMemory->Write(m_stackPtr, address);
    m_mainMemory->Write(m_stackPtr - 1, (address >> 8));
    m_stackPtr -= 2;

    m_programCounter = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
    m_cycles += 12;
 }


 void Cpu::Ret() {
     auto address = CombineRegisters(m_mainMemory->Read(m_stackPtr + 1), m_mainMemory->Read(m_stackPtr));
     m_stackPtr += 2;

     m_programCounter = address;
     m_cycles += 12;
 }

 void Cpu::ExecuteCB() {

     auto opcode = m_mainMemory->Read(m_programCounter);

    Logger::Log(LogLevel::Debug, "Program counter: \t" + std::to_string(m_programCounter));
    Logger::Log(LogLevel::Debug, "Opcode: \t" + std::to_string(opcode));

     switch (opcode) {
         case 0x00:
            UnimplementedOperation("RLC B");
            break;
        
        case 0x01:
            UnimplementedOperation("RLC C");
            break;
        
        case 0x02:
            UnimplementedOperation("RLC D");
            break;
        
        case 0x03:
            UnimplementedOperation("RLC E");
            break;
        
        case 0x04:
            UnimplementedOperation("RLC H");
            break;
        
        case 0x05:
            UnimplementedOperation("RLC L");
            break;
        
        case 0x06:
            UnimplementedOperation("RLC (HL)");
            break;
        
        case 0x07:
            UnimplementedOperation("RLC A");
            break;
        
        case 0x08:
            UnimplementedOperation("RRC B");
            break;
        
        case 0x09:
            UnimplementedOperation("RRC C");
            break;
        
        case 0x0A:
            UnimplementedOperation("RRC D");
            break;
        
        case 0x0B:
            UnimplementedOperation("RRC E");
            break;
        
        case 0x0C:
            UnimplementedOperation("RRC H");
            break;
        
        case 0x0D:
            UnimplementedOperation("RRC L");
            break;
        
        case 0x0E:
            UnimplementedOperation("RRC (HL");
            break;
        
        case 0x0F:
            UnimplementedOperation("RRC A");
            break;
        
        case 0x19:
            RR(m_regC);
            break;
        
        case 0x1A:
            RR(m_regD);
            break;

        case 0x38:
            SRL(m_regB);
            break;

        
        case 0xB7:
            m_regA &= ~(1ul << 6);
            m_programCounter++;
            break;
        
        default:
            UnimplementedOperation("Unavailable Opcode\n");
            break;
     }

 }

void Cpu::JumpRelativeNZ() {
    if (!m_regF.test(7)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeNC() {
    if (!m_regF.test(4)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeC() {
    if (m_regF.test(4)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::Pop(uint8_t& high, uint8_t& low) {
    high = m_mainMemory->Read(m_stackPtr + 1);
    low = m_mainMemory->Read(m_stackPtr);

    m_stackPtr += 2;
    m_programCounter++;
}

void Cpu::Restart(uint8_t address) {
    m_mainMemory->Write(m_stackPtr, m_programCounter);
    m_stackPtr--;

    m_programCounter += 0x000 + address;
    m_cycles += 32;
}

void Cpu::LDHAN() {
    auto address = +0xFF00 + m_mainMemory->Read(m_programCounter + 1);

    m_regA = m_mainMemory->Read(address);

    m_programCounter++;
}

void Cpu::Push(uint8_t high, uint8_t low) {
    m_mainMemory->Write(m_stackPtr, high);
    m_stackPtr--;

    m_mainMemory->Write(m_stackPtr, low);
    m_stackPtr--;

    m_programCounter++;
}

void Cpu::Push(uint8_t high, std::bitset<8> low) {

    uint8_t lowBit = low.to_ulong();
    Push(high, lowBit);
}

void Cpu::LoadFromImmediateByte(uint8_t& to) {
    to = m_mainMemory->Read(m_programCounter + 1);

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::LoadFromRegister(uint8_t& to, uint8_t from) {
    to = from;

    m_programCounter++;
    m_cycles += 4;
}


void Cpu::LoadFromAddress(Byte& to, uint16_t address) {
    to = m_mainMemory->Read(address);
    
    m_programCounter++;
    m_cycles += 8;
}

void Cpu::LoadToAddress(uint16_t address, uint8_t value) {
    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::LoadImmediate16BitValue(uint8_t& high, uint8_t& low) {
    high = m_mainMemory->Read(m_programCounter + 2);
    low = m_mainMemory->Read(m_programCounter + 1);

    m_programCounter += 3;
    m_cycles += 12;
}

void Cpu::LoadImmediate16BitValue(uint16_t& to) {
    auto value = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    to = value;

    m_programCounter += 3;
    m_cycles += 12;
}

void Cpu::LoadStackPointerFromHL() {
    auto value = CombineRegisters(m_regH, m_regL);
    m_stackPtr = value;

    m_programCounter++;
    m_cycles += 8;
}
    

void Cpu::IncrementAtAddress(uint16_t address) {
    
    uint8_t value = m_mainMemory->Read(address);

    if ( (((value & 0xf) + ( (value +1) &0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    } 

    value++;

    if(value == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);

    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 12;
}

void Cpu::IncrementRegisterPair(uint8_t& high, uint8_t& low) {
    
    uint16_t value = CombineRegisters(high, low);
    value++;

    high = value >> 8;
    low = value;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::IncrementStackpointer() {
    m_stackPtr++;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::DecrementRegisterPair(uint8_t& high, uint8_t& low) {
        uint16_t value = CombineRegisters(high, low);
        value--;

        high = value >> 8;
        low = value;

        m_programCounter++;
        m_cycles+= 8;
}

void Cpu::DecrementStackPointer() {
    m_stackPtr--;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::DecrementAtAddress(uint16_t address) {
    
    auto value = m_mainMemory->Read(address);
    value--;

    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 12;
}


void Cpu::RLCA() {

    if ( (m_regA & 0b10000000) == 0b10000000) {
        m_regF.set(4);
    } else {
        m_regF.reset(4);
    }

    m_regA = m_regA << 1;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::JumpRelative() {

    auto r8 = m_mainMemory->Read(m_programCounter + 1);
    m_programCounter += static_cast<int16_t>(r8);
    m_cycles += 8;
}

void Cpu::JumpRelativeZ() {

    if(m_regF.test(7)) {
        m_programCounter += static_cast<int16_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter++;
    }

    m_cycles += 8;
}

void Cpu::RetNZ() {
    if(!m_regF.test(7)) {
        Ret();
    } else {
        m_programCounter++;
        m_cycles += 8;
    }
}

void Cpu::Jump() {
    auto address = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
    m_programCounter = address;
    m_cycles += 12;
}