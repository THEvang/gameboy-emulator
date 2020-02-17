#include <cpu/Cpu.h>
#include <cpu/Operations.h>
#include <Opcodes.h>
#include <CBCode.h>

void step(Cpu& cpu) {

    const auto opcode = cpu.m_memory_controller->read(m_programCounter);

    switch(static_cast<Opcode>(opcode)) {
        case Opcode::NOP:
            NOP();
            break;

        case Opcode::LD_BC_D16:
            // LoadImmediate16BitValue(m_regB, m_regC);
            break;

        case Opcode::LD_ADDR_BC_A:
            // Load(CombineRegisters(m_regB, m_regC), m_regA);
            break;

        case Opcode::INC_BC:
            INCBC(cpu);
            break;
        
        case Opcode::INC_B:
            INCB(cpu);
            break;
        
        case Opcode::DEC_B:
            DECB(cpu);
            break;

        case Opcode::LD_B_D8:
            LDB(cpu);
            break;
        
        case Opcode::RLCA:
            RLCA(cpu);
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
            Load(m_regA, CombineRegisters(m_regB, m_regC));
            break;

        case Opcode::DEC_BC:
            DECBC(cpu);
            break;
        
        case Opcode::INC_C:
            INCC(cpu);
            break;
        
        case Opcode::DEC_C:
            DECC(cpu);
            break;
        
        case Opcode::LD_C_D8:
            LDC(cpu);
            break;
        
        case Opcode::RRCA:
            UnimplementedOperation("RRCA");
            m_programCounter++;
            break;
        
        case Opcode::STOP:
            STOP();
            break;

        case Opcode::LD_DE_D16:
            LoadImmediate16BitValue(m_regD, m_regE);
            break;
        
        case Opcode::LD_ADDR_DE_A:
            Load(CombineRegisters(m_regD, m_regE), m_regA);
            break;
        
        case Opcode::INC_DE:
            IncrementRegisterPair(m_regD, m_regE);
            break;
        
        case Opcode::INC_D:
            INCD(cpu);
            break;
        
        case Opcode::DEC_D:
            DECD(cpu);
            break;
        
        case Opcode::LD_D_D8:
            LDD(cpu);
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
            Load(m_regA, CombineRegisters(m_regD, m_regE));
            break;
        
        case Opcode::DEC_DE:
            DECDE(cpu);
            break;
        
        case Opcode::INC_E:
            INCE(cpu);
            break;

        case Opcode::DEC_E:
            DecrementRegister(m_regE);
            break;
        
        case Opcode::LD_E_D8:
            LDE(cpu);
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
            INCH(cpu);
            break;
        
        case Opcode::DEC_H:
            DECH(cpu);
            break;
        
        case Opcode::LD_H_D8:
            LDH(cpu);
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
            DECHL(cpu);
            break;
        
        case Opcode::INC_L:
            INCL(cpu);
            break;
        
        case Opcode::DEC_L:
            DecrementRegister(m_regL);
            break;
        
        case Opcode::LD_L_D8:
            Load(m_regL);
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
            SCF(cpu);
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
            DECSP(cpu);
            break;
        
        case Opcode::INC_A:
            INCA(cpu);
            break;
        
        case Opcode::DEC_A:
            DECA(cpu);
            break;
        
        case Opcode::LD_A_D8:
            Load(m_regA);
            break;

        case Opcode::CCF:
            CCF(cpu);
            break;
        
        case Opcode::LD_B_B:
            Load(m_regB, m_regB);
            break;
        
        case Opcode::LD_B_C:
            Load(m_regB, m_regC);
            break;
        
        case Opcode::LD_B_D:
            Load(m_regB, m_regD);
            break;
        
        case Opcode::LD_B_E:
            Load(m_regB, m_regE);
            break;
        
        case Opcode::LD_B_H:
            Load(m_regB, m_regH);
            break;
        
        case Opcode::LD_B_L:
            Load(m_regB, m_regL);
            break;
        
        case Opcode::LD_B_ADDR_HL:
            Load(m_regB, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_B_A:
            Load(m_regB, m_regA);
            break;
        
        case Opcode::LD_C_B:
            Load(m_regC, m_regB);
            break;
        
        case Opcode::LD_C_C:
            Load(m_regC, m_regC);
            break;
        
        case Opcode::LD_C_D:
            Load(m_regC, m_regD);
            break;
        
        case Opcode::LD_C_E:
            Load(m_regC, m_regE);
            break;
        
        case Opcode::LD_C_H:
            Load(m_regC, m_regH);
            break;
        
        case Opcode::LD_C_L:
            Load(m_regC, m_regL);
            break;
        
        case Opcode::LD_C_ADDR_HL:
            Load(m_regC, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_C_A:
            Load(m_regC, m_regA);
            break;

        case Opcode::LD_D_B:
            Load(m_regD, m_regB);
            break;

        case Opcode::LD_D_C:
            Load(m_regD, m_regC);
            break;

        case Opcode::LD_D_D:
            Load(m_regD, m_regD);
            break;

        case Opcode::LD_D_E:
            Load(m_regD, m_regE);
            break;

        case Opcode::LD_D_H:
            Load(m_regD, m_regH);
            break;

        case Opcode::LD_D_L:
            Load(m_regD, m_regL);
            break;

        case Opcode::LD_D_ADDR_HL:
            Load(m_regD, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_D_A:
            Load(m_regD, m_regA);
            break;

        case Opcode::LD_E_B:
            Load(m_regE, m_regB);
            break;

        case Opcode::LD_E_C:
            Load(m_regE, m_regC);
            break;

        case Opcode::LD_E_D:
            Load(m_regE, m_regD);
            break;

        case Opcode::LD_E_E:
            Load(m_regE, m_regE);
            break;

        case Opcode::LD_E_H:
            Load(m_regE, m_regH);
            break;

        case Opcode::LD_E_L:
            Load(m_regE, m_regL);
            break;

        case Opcode::LD_E_ADDR_HL:
            Load(m_regE, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_E_A:
            Load(m_regE, m_regA);
            break;

        case Opcode::LD_H_B:
            Load(m_regH, m_regB);
            break;

        case Opcode::LD_H_C:
            Load(m_regH, m_regC);
            break;

        case Opcode::LD_H_D:
            Load(m_regH, m_regD);
            break;

        case Opcode::LD_H_E:
            Load(m_regH, m_regE);
            break;

        case Opcode::LD_H_H:
            Load(m_regH, m_regH);
            break;

        case Opcode::LD_H_L:
            Load(m_regH, m_regL);
            break;

        case Opcode::LD_H_ADDR_HL:
            Load(m_regH, CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::LD_H_A:
            Load(m_regH, m_regA);
            break;

        case Opcode::LD_L_B: 
            Load(m_regL, m_regB);
            break;
        
        case Opcode::LD_L_C:
            Load(m_regL, m_regC);
            break;
        
        case Opcode::LD_L_D:
            Load(m_regL, m_regD);
            break;
        
        case Opcode::LD_L_E:
            Load(m_regL, m_regE);
            break;
        
        case Opcode::LD_L_H:
            Load(m_regL, m_regH);
            break;
        
        case Opcode::LD_L_L:
            Load(m_regL, m_regL);
            break;
        
        case Opcode::LD_L_ADDR_HL:
            Load(m_regL, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_L_A:
            Load(m_regL, m_regA);
            break;
        
        case Opcode::LD_ADDR_HL_B:
            Load(CombineRegisters(m_regH, m_regL), m_regB);
            break;

        case Opcode::LD_ADDR_HL_C:
            Load(CombineRegisters(m_regH, m_regL), m_regC);
            break;

        case Opcode::LD_ADDR_HL_D:
            Load(CombineRegisters(m_regH, m_regL), m_regD);
            break;
        
        case Opcode::LD_ADDR_HL_E:
            Load(CombineRegisters(m_regH, m_regL), m_regE); 
            break;
        
        case Opcode::LD_ADDR_HL_H:
            Load(CombineRegisters(m_regH, m_regL), m_regH);
            break;
        
        case Opcode::LD_ADDR_HL_L:
            Load(CombineRegisters(m_regH, m_regL), m_regL);
            break;
        
        case Opcode::HALT:
            HALT();
            break;
        
        case Opcode::LD_ADDR_HL_A:
            Load(CombineRegisters(m_regH, m_regL), m_regA);
            break;

        case Opcode::LD_A_B:
            Load(m_regA, m_regB);
            break;
        
        case Opcode::LD_A_C:
            Load(m_regA, m_regC);
            break;
        
        case Opcode::LD_A_D:
            Load(m_regA, m_regD);
            break;
        
        case Opcode::LD_A_E:
            Load(m_regA, m_regE);
            break;
        
        case Opcode::LD_A_H:
            Load(m_regA, m_regH);
            break;
        
        case Opcode::LD_A_L:
            Load(m_regA, m_regL);
            break;
        
        case Opcode::LD_A_ADDR_HL:
            Load(m_regA, CombineRegisters(m_regH, m_regL));
            break;
        
        case Opcode::LD_A_A:
            Load(m_regA, m_regA);
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
            And(m_regB);
            break;
        
        case Opcode::AND_C:
            And(m_regC);
            break;
        
        case Opcode::AND_D:
            And(m_regD);
            break;
        
        case Opcode::AND_E:
            And(m_regE);
            break;
        
        case Opcode::AND_H:
            And(m_regH);
            break;
        
        case Opcode::AND_L:
            And(m_regL);
            break;
        
        case Opcode::AND_ADDR_HL:
            And(CombineRegisters(m_regH, m_regL));
            break;

        case Opcode::AND_A:
            And(m_regA);
            break;
        
        case Opcode::XOR_B:
            Xor(m_regB);
            break;
        
        case Opcode::XOR_C:
            Xor(m_regC);
            break;
        
        case Opcode::XOR_D:
            Xor(m_regD);
            break;
        
        case Opcode::XOR_E:
            Xor(m_regE);
            break;
        
        case Opcode::XOR_H:
            Xor(m_regH);
            break;
        
        case Opcode::XOR_L:
            Xor(m_regL);
            break;
        
        case Opcode::XOR_ADDR_HL:
            Xor(CombineRegisters(m_regH, m_regL)); 
            break;
        
        case Opcode::XOR_A:
            Xor(m_regA);
            break;
        
        case Opcode::OR_B:
            Or(m_regB);
            break;
        
        case Opcode::OR_C:
            Or(m_regC);
            break;
        
        case Opcode::OR_D:
            Or(m_regD);
            break;
        
        case Opcode::OR_E:
            Or(m_regE);
            break;
        
        case Opcode::OR_H:
            Or(m_regH);
            break;
        
        case Opcode::OR_L:
            Or(m_regL);
            break;
        
        case Opcode::OR_ADDR_HL:
            Or(CombineRegisters(m_regH, m_regL));
            break;
            
        case Opcode::OR_A:
            Or(m_regA);
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
            And();
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
            Xor();
            break;
        
        case Opcode::RST_28H:
            Restart(0x28);
            break;
        
        case Opcode::LDH_A_ADDR_A8:
            LDHAN();
            m_programCounter++;
            break;
        
        case Opcode::POP_AF:
            UnimplementedOperation("POP AF");
            //Pop(m_regA, m_flags.asByte());
            break;
        
        case Opcode::LD_A_ADDR_C:
            UnimplementedOperation("LD A, (C)");
            break;
        
        case Opcode::DI:
            DisableInterrupts();
            break;
        
        case Opcode::PUSH_AF:
            Push(m_regA, m_flags.asByte());
            break;
        
        case Opcode::OR_D8:
            Or();
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

void Cpu::Load(uint8_t & reg) {
    reg = m_mainMemory->Read(m_programCounter + 1);
    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::Load(uint8_t & reg, uint8_t value) {
    reg = value;
    m_programCounter++;
    m_cycles += 4;
}

void Cpu::Load(uint8_t & reg, uint16_t const addr) {
    reg = m_mainMemory->Read(addr);
    m_programCounter++;
    m_cycles += 8;
}

void Cpu::Load(uint16_t const address, uint8_t const value) {
    m_mainMemory->Write(address, value);
    m_programCounter++;
    m_cycles += 8;
}

void Cpu::IncrementRegister(Byte& reg) {

    m_flags.resetSubtract();

    if ( (((reg & 0xf) + (1 & 0xf)) & 0x10) == 0x10) {
        m_flags.setHalfCarry();
    }

    reg++;

    if (reg == 0) {
        m_flags.setZero();
    }

 
    m_programCounter++;
    m_cycles += 4;
}

void Cpu::DecrementRegister(Byte& reg) {
    
    Logger::Log(LogLevel::Debug, "Decrement register");

    m_flags.resetSubtract();

    if((((reg  & 0x0f) - (1 & 0x0f)) & 0x10) == 0x10) {
        m_flags.setHalfCarry();
    } 

    reg--;

    if (reg == 0) {
        m_flags.setZero();
    }

    
    // Set if no borrow from bit 4

    m_programCounter++;
    m_cycles += 4;
}

uint16_t Cpu::CombineRegisters(const Byte& high, const Byte& low) const {

    uint16_t combinedRegister = (high << 8) | low;

    return combinedRegister;
}

void Cpu::AddRegisters(Byte& to, const Byte& from) {

    m_flags.resetSubtract();

    if ( (((to & 0xf) + ( (from +1) &0xf)) & 0x10) == 0x10) {
        m_flags.setHalfCarry();
    } 

    if( (static_cast<int>(to) + static_cast<int>(from)) > 0xFF) {
        m_flags.setCarry();
    }

    if(to == 0) {
        m_flags.setZero();
    }


    to += from;

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::SubtractFromA(uint8_t value) {

    Logger::Log(LogLevel::Debug, "Subtract Register from A");

    m_flags.setSubtract();

    if (value > m_regA) {
        m_flags.setCarry();
    }

    m_regA -= value;

    if(m_regA == 0) {
        m_flags.setZero();
    }


    m_programCounter++;
    m_cycles += 8;
    //Check borrow from 4 bit

}

void Cpu::SubtractFromAddress(uint16_t address) {

    Logger::Log(LogLevel::Debug, "Subtract address from A");

    m_flags.setSubtract();

    auto value = m_mainMemory->Read(address);    

    if (value > m_regA) {
        m_flags.setCarry();
    }

    m_regA -= value;

    if(m_regA == 0) {
        m_flags.setZero();
    }



    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_cycles += 8;
    m_programCounter++;
}

void Cpu::SubtractImmediateByte() {

    Logger::Log(LogLevel::Debug, "Subtract n From A");

    m_flags.setSubtract();

    auto value = m_mainMemory->Read(m_programCounter + 1);
    m_regA -= value;

    if(m_regA == 0) {
        m_flags.setZero();
    }

    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::UnimplementedOperation(std::string const & message) const {

    Logger::Log(LogLevel::Error, "Unimplemented operation: \t" + message);
    std::cin.get();
}

void Cpu::And() {
    auto value = m_mainMemory->Read(m_programCounter + 1);

    m_regA &= value;
    SetAndFlags(m_regA);

    m_programCounter +=2;
    m_cycles += 8;
}

void Cpu::And(uint8_t const value) {
    
    m_regA &= value;
    SetAndFlags(m_regA);

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::And(uint16_t const address) {
    auto value = m_mainMemory->Read(address);

    m_regA &= value;
    SetAndFlags(m_regA);

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::SetAndFlags(uint8_t const value) {
    
    if (value == 0) {
        m_flags.setZero();
    }

    m_flags.resetSubtract();
    m_flags.setHalfCarry();
    m_flags.resetCarry();
}

void Cpu::Or() {

    auto value = m_mainMemory->Read(m_programCounter + 1);
    
    m_regA |= value;
    SetOrFlags(m_regA);

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::Or(uint8_t const value) {

    m_regA |= value;
    SetOrFlags(m_regA);

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::Or(uint16_t const address) {

    auto value = m_mainMemory->Read(address);

    m_regA |= value;

    SetOrFlags(m_regA);

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::SetOrFlags(uint8_t const result) {
    
    if (result == 0) {
        m_flags.setZero();
    }

    m_flags.resetSubtract();
    m_flags.resetHalfCarry();
    m_flags.resetCarry();
}

void Cpu::Xor() {
    auto value = m_mainMemory->Read(m_programCounter + 1);

    m_regA ^= value;
    SetOrFlags(m_regA);

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::Xor(uint8_t const value) {
    
    m_regA ^= value;
    SetOrFlags(m_regA);

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::Xor(uint16_t const address) {
    auto value = m_mainMemory->Read(address);

    m_regA ^= value;
    SetOrFlags(m_regA);

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::CompareWithA(const Byte& reg) {

    Logger::Log(LogLevel::Debug, "Compare register with A");

    if(m_regA == reg) {
       m_flags.setZero();
    }

    m_flags.setSubtract();

    //Set H if no borrow from bit 4

    if(m_regA < reg) {
        m_flags.setCarry();
    }
}

void Cpu::DisableInterrupts() {
    
    m_programCounter++;
}

 
 void Cpu::ComplementA() {

    m_regA = ~m_regA;

    m_flags.setSubtract();
    m_flags.setHalfCarry();

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::ComplementCarryFlag() {

    m_flags.flipCarry();

    m_flags.resetSubtract();
    m_flags.resetHalfCarry();

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::SetCarryFlag() {

    m_flags.setCarry();
    m_flags.resetSubtract();
    m_flags.resetHalfCarry();

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

     switch (static_cast<CBCode>(opcode)) {
         case CBCode::RLC_B:
            UnimplementedOperation("RLC B");
            break;
        
        case CBCode::RLC_C :
            UnimplementedOperation("RLC C");
            break;
        
        case CBCode::RLC_D:
            UnimplementedOperation("RLC D");
            break;
        
        case CBCode::RLC_E:
            UnimplementedOperation("RLC E");
            break;
        
        case CBCode::RLC_H:
            UnimplementedOperation("RLC H");
            break;
        
        case CBCode::RLC_L:
            UnimplementedOperation("RLC L");
            break;
        
        case CBCode::RLC_ADDR_HL:
            UnimplementedOperation("RLC (HL)");
            break;
        
        case CBCode::RLC_A:
            UnimplementedOperation("RLC A");
            break;
        
        case CBCode::RRC_B:
            UnimplementedOperation("RRC B");
            break;
        
        case CBCode::RRC_C:
            UnimplementedOperation("RRC C");
            break;
        
        case CBCode::RRC_D:
            UnimplementedOperation("RRC D");
            break;
        
        case CBCode::RRC_E:
            UnimplementedOperation("RRC E");
            break;
        
        case CBCode::RRC_H:
            UnimplementedOperation("RRC H");
            break;
        
        case CBCode::RRC_L:
            UnimplementedOperation("RRC L");
            break;
        
        case CBCode::RRC_ADDR_HL:
            UnimplementedOperation("RRC (HL");
            break;
        
        case CBCode::RRC_A:
            UnimplementedOperation("RRC A");
            break;
        
        case CBCode::RR_C:
            RR(m_regC);
            break;
        
        case CBCode::RR_D:
            RR(m_regD);
            break;

        case CBCode::SRL_B:
            SRL(m_regB);
            break;

        case CBCode::RES_6_A:
            m_regA &= ~(1ul << 6);
            m_programCounter++;
            break;
        
        default:
            UnimplementedOperation("Unavailable Opcode\n");
            break;
     }

 }

void Cpu::JumpRelativeNZ() {

    if (m_flags.zeroFlag() == FlagState::Reset) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeNC() {

    if (m_flags.carryFlag() == FlagState::Reset) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeC() {

    if (m_flags.carryFlag() == FlagState::Set) {
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
        m_flags.setHalfCarry();
    } 

    value++;

    if(value == 0) {
        m_flags.setZero();
    }

    m_flags.resetSubtract();

    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 12;
}

void Cpu::IncrementRegisterPair(uint8_t& high, uint8_t& low) {
    
    auto value = CombineRegisters(high, low);
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
        m_flags.setCarry();
    } else {
        m_flags.resetCarry();
    }

    m_regA = m_regA << 1;

    if (m_regA == 0) {
        m_flags.zeroFlag();
    }

    m_flags.resetSubtract();
    m_flags.resetHalfCarry();

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::JumpRelative() {

    auto r8 = m_mainMemory->Read(m_programCounter + 1);
    m_programCounter += static_cast<int16_t>(r8);
    m_cycles += 8;
}

void Cpu::JumpRelativeZ() {

    if(m_flags.zeroFlag() == FlagState::Set)
    {
        m_programCounter += static_cast<int16_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter++;
    }

    m_cycles += 8;
}

void Cpu::RetNZ() {

    if(m_flags.zeroFlag() == FlagState::Reset) {
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