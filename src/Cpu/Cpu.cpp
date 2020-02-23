#include <cpu/Cpu.h>
#include <cpu/Operations.h>
#include <cpu/Opcodes.h>
#include <cpu/CBCode.h>
#include <iostream>

Cpu::Cpu(MemoryBankController* memory_controller)     
    : m_memory_controller(memory_controller) 
{

    m_memory_controller->write(0xFF05, 0);
    m_memory_controller->write(0xFF06, 0);
    m_memory_controller->write(0xFF07, 0);

    m_memory_controller->write(0xFF10, 0x80);
    m_memory_controller->write(0xFF11, 0xBF);
    m_memory_controller->write(0xFF12, 0xF3);

    m_memory_controller->write(0xFF14, 0xBF);
    m_memory_controller->write(0xFF16, 0x3F);
    m_memory_controller->write(0xFF17, 0x00);
    m_memory_controller->write(0xFF19, 0xBF);

    m_memory_controller->write(0xFF1A, 0x7F);
    m_memory_controller->write(0xFF1B, 0xFF);
    m_memory_controller->write(0xFF1C, 0x9F);
    m_memory_controller->write(0xFF1E, 0xBF);

    m_memory_controller->write(0xFF20, 0xFF);
    m_memory_controller->write(0xFF21, 0x00);
    m_memory_controller->write(0xFF22, 0x00);
    m_memory_controller->write(0xFF23, 0xBF);
    m_memory_controller->write(0xFF24, 0x77);
    m_memory_controller->write(0xFF25, 0xF3);
    m_memory_controller->write(0xFF26, 0xF1);

    
    m_memory_controller->write(0xFF40, 0x91);
    m_memory_controller->write(0xFF42, 0x00);
    m_memory_controller->write(0xFF43, 0x00);
    m_memory_controller->write(0xFF45, 0x00);
    m_memory_controller->write(0xFF47, 0xFC);
    m_memory_controller->write(0xFF48, 0xFF);
    m_memory_controller->write(0xFF49, 0xFF);

    m_memory_controller->write(0xFF4A, 0x00);
    m_memory_controller->write(0xFF4B, 0x00);
    m_memory_controller->write(0xFFFF, 0x00);
}

void step(Cpu& cpu) {


    const auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter);
    std::cout << "Opcode: " << std::hex << (int) opcode << "\n";
    std::cout << "Program Counter: " << (int) cpu.m_program_counter << "\n";

    switch(static_cast<Opcode>(opcode)) {
        case Opcode::NOP:
            NOP(cpu);
            break;

        case Opcode::LD_BC_D16:
            LD_BC_D16(cpu);
            break;

        case Opcode::LD_ADDR_BC_A:
            LD_ADDR_BC_A(cpu);
            break;

        case Opcode::INC_BC:
            INC_BC(cpu);
            break;
        
        case Opcode::INC_B:
            INC_B(cpu);
            break;
        
        case Opcode::DEC_B:
            DEC_B(cpu);
            break;

        case Opcode::LD_B_D8:
            LD_B_D8(cpu);
            break;
        
        case Opcode::RLCA:
            RLCA(cpu);
            break;

        case Opcode::LD_ADDR_A16_SP:
            LD_ADDR_SP(cpu);
            break;

        case Opcode::ADD_HL_BC:
            ADD_HL_BC(cpu);
            break;

        case Opcode::LD_A_ADDR_BC:
            LD_A_ADDR_BC(cpu);
            break;

        case Opcode::DEC_BC:
            DEC_BC(cpu);
            break;
        
        case Opcode::INC_C:
            INC_C(cpu);
            break;
        
        case Opcode::DEC_C:
            DEC_C(cpu);
            break;
        
        case Opcode::LD_C_D8:
            LD_C_D8(cpu);
            break;
        
        case Opcode::RRCA:
            RRCA(cpu);
            break;
        
        case Opcode::STOP:
            STOP(cpu);
            break;

        case Opcode::LD_DE_D16:
            LD_DE_D16(cpu);
            break;
        
        case Opcode::LD_ADDR_DE_A:
            LD_ADDR_DE_A(cpu);
            break;
        
        case Opcode::INC_DE:
            INC_DE(cpu);
            break;
        
        case Opcode::INC_D:
            INC_D(cpu);
            break;
        
        case Opcode::DEC_D:
            DEC_D(cpu);
            break;
        
        case Opcode::LD_D_D8:
            LD_D_D8(cpu);
            break;
        
        case Opcode::RLA:
            RLA(cpu);
            break;

        case Opcode::JR_R8:
            JR(cpu);
            break;
        
        case Opcode::ADD_HL_DE:
            ADD_HL_DE(cpu);
            break;
        
        case Opcode::LD_A_ADDR_DE:
            LD_A_ADDR_DE(cpu);
            break;
        
        case Opcode::DEC_DE:
            DEC_DE(cpu);
            break;
        
        case Opcode::INC_E:
            INC_E(cpu);
            break;

        case Opcode::DEC_E:
            DEC_E(cpu);
            break;
        
        case Opcode::LD_E_D8:
            LD_E_D8(cpu);
            break;
        
        case Opcode::RRA:
            RRA(cpu);
            break;

        case Opcode::JR_NZ_R8:
            JR_NZ(cpu);
            break;
        
        case Opcode::LD_HL_D16:
            LD_HL_D16(cpu);
            break;
        
        case Opcode::LD_ADDR_HLI_A:
            LDI_ADDR_HL_A(cpu);
            break;
        
        case Opcode::INC_HL:
            INC_HL(cpu);
            break;

        case Opcode::INC_H:
            INC_H(cpu);
            break;
        
        case Opcode::DEC_H:
            DEC_H(cpu);
            break;
        
        case Opcode::LD_H_D8:
            LD_H_D8(cpu);
            break;
        
        case Opcode::DAA:
            DDA(cpu);
            break;
        
        case Opcode::JR_Z_R8:
            JR_Z(cpu);
            break;

        case Opcode::ADD_HL_HL:
            ADD_HL_HL(cpu);
            break;
        
        case Opcode::LD_A_ADDR_HLI:
            LDI_A_ADDR_HL(cpu);
            break;
        
        case Opcode::DEC_HL:
            DEC_HL(cpu);
            break;
        
        case Opcode::INC_L:
            INC_L(cpu);
            break;
        
        case Opcode::DEC_L:
            DEC_L(cpu);
            break;
        
        case Opcode::LD_L_D8:
            LD_L_D8(cpu);
            break;
        
        case Opcode::CPL:
            CP_L(cpu);
            break;
        
        case Opcode::JR_NC_R8:
            JR_NC(cpu);
            break;
        
        case Opcode::LD_SP_D16:
            LD_SP_D16(cpu);
            break;
        
        case Opcode::LD_ADDR_HLD_A:
            LD_ADDR_HLD_A(cpu);
            break;
        
        case Opcode::INC_SP:
            INC_SP(cpu);
            break;
        
        case Opcode::INC_ADDR_HL:
            INC_ADDR_HL(cpu);
            break;
        
        case Opcode::DEC_ADDR_HL:
            DEC_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_D8:
            LD_A_ADDR_HL(cpu);
            break;
        
        case Opcode::SCF:
            SCF(cpu);
            break;
        
        case Opcode::JR_C_R8:
            JR_C(cpu);
            break;
        
        case Opcode::ADD_HL_SP:
            UnimplementedOperation("ADD HL, SP");
            break;
        
        case Opcode::LD_A_ADDR_HLD:
            UnimplementedOperation("LD A, (HL-)");
            break;
        
        case Opcode::DEC_SP:
            DEC_SP(cpu);
            break;
        
        case Opcode::INC_A:
            INC_A(cpu);
            break;
        
        case Opcode::DEC_A:
            DEC_A(cpu);
            break;
        
        case Opcode::LD_A_D8:
            LD_A_D8(cpu);
            break;

        case Opcode::CCF:
            CCF(cpu);
            break;
        
        case Opcode::LD_B_B:
            LD_B_B(cpu);
            break;
        
        case Opcode::LD_B_C:
            LD_B_C(cpu);
            break;
        
        case Opcode::LD_B_D:
            LD_B_D(cpu);
            break;
        
        case Opcode::LD_B_E:
            LD_B_E(cpu);
            break;
        
        case Opcode::LD_B_H:
            LD_B_H(cpu);
            break;
        
        case Opcode::LD_B_L:
            LD_B_L(cpu);
            break;
        
        case Opcode::LD_B_ADDR_HL:
            LD_B_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_B_A:
            LD_B_A(cpu);
            break;
        
        case Opcode::LD_C_B:
            LD_C_B(cpu);
            break;
        
        case Opcode::LD_C_C:
            LD_C_C(cpu);
            break;
        
        case Opcode::LD_C_D:
            LD_C_D(cpu);
            break;
        
        case Opcode::LD_C_E:
            LD_C_E(cpu);
            break;
        
        case Opcode::LD_C_H:
            LD_C_H(cpu);
            break;
        
        case Opcode::LD_C_L:
            LD_C_L(cpu);
            break;
        
        case Opcode::LD_C_ADDR_HL:
            LD_C_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_C_A:
            LD_C_A(cpu);
            break;

        case Opcode::LD_D_B:
            LD_D_B(cpu);
            break;

        case Opcode::LD_D_C:
            LD_D_C(cpu);
            break;

        case Opcode::LD_D_D:
            LD_D_D(cpu);
            break;

        case Opcode::LD_D_E:
            LD_D_E(cpu);
            break;

        case Opcode::LD_D_H:
            LD_D_H(cpu);
            break;

        case Opcode::LD_D_L:
            LD_D_L(cpu);
            break;

        case Opcode::LD_D_ADDR_HL:
            LD_D_ADDR_HL(cpu);
            break;

        case Opcode::LD_D_A:
            LD_D_A(cpu);
            break;

        case Opcode::LD_E_B:
            LD_E_B(cpu);
            break;

        case Opcode::LD_E_C:
            LD_E_C(cpu);
            break;

        case Opcode::LD_E_D:
            LD_E_D(cpu);
            break;

        case Opcode::LD_E_E:
            LD_E_E(cpu);
            break;

        case Opcode::LD_E_H:
            LD_E_H(cpu);
            break;

        case Opcode::LD_E_L:
            LD_E_L(cpu);
            break;

        case Opcode::LD_E_ADDR_HL:
            LD_E_ADDR_HL(cpu);
            break;

        case Opcode::LD_E_A:
            LD_E_A(cpu);
            break;

        case Opcode::LD_H_B:
            LD_H_B(cpu);
            break;

        case Opcode::LD_H_C:
            LD_H_C(cpu);
            break;

        case Opcode::LD_H_D:
            LD_H_D(cpu);
            break;

        case Opcode::LD_H_E:
            LD_H_E(cpu);
            break;

        case Opcode::LD_H_H:
            LD_H_H(cpu);
            break;

        case Opcode::LD_H_L:
            LD_H_L(cpu);
            break;

        case Opcode::LD_H_ADDR_HL:
            LD_H_ADDR_HL(cpu);
            break;

        case Opcode::LD_H_A:
            LD_H_A(cpu);
            break;

        case Opcode::LD_L_B: 
            LD_L_B(cpu);
            break;
        
        case Opcode::LD_L_C:
            LD_L_C(cpu);
            break;
        
        case Opcode::LD_L_D:
            LD_L_D(cpu);
            break;
        
        case Opcode::LD_L_E:
            LD_L_E(cpu);
            break;
        
        case Opcode::LD_L_H:
            LD_L_H(cpu);
            break;
        
        case Opcode::LD_L_L:
            LD_L_L(cpu);
            break;
        
        case Opcode::LD_L_ADDR_HL:
            LD_L_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_L_A:
            LD_L_A(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_B:
            LD_ADDR_HL_B(cpu);
            break;

        case Opcode::LD_ADDR_HL_C:
            LD_ADDR_HL_C(cpu);
            break;

        case Opcode::LD_ADDR_HL_D:
            LD_ADDR_HL_D(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_E:
            LD_ADDR_HL_E(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_H:
            LD_ADDR_HL_H(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_L:
            LD_ADDR_HL_L(cpu);
            break;
        
        case Opcode::HALT:
            HALT(cpu);
            break;
        
        case Opcode::LD_ADDR_HL_A:
            LD_ADDR_HL_A(cpu);
            break;

        case Opcode::LD_A_B:
            LD_A_B(cpu);
            break;
        
        case Opcode::LD_A_C:
            LD_A_C(cpu);
            break;
        
        case Opcode::LD_A_D:
            LD_A_D(cpu);
            break;
        
        case Opcode::LD_A_E:
            LD_A_E(cpu);
            break;
        
        case Opcode::LD_A_H:
            LD_A_H(cpu);
            break;
        
        case Opcode::LD_A_L:
            LD_A_L(cpu);
            break;
        
        case Opcode::LD_A_ADDR_HL:
            LD_A_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_A_A:
            LD_A_A(cpu);
            break;
        
        case Opcode::ADD_A_B:
            ADD_A_B(cpu);
            break;
        
        case Opcode::ADD_A_C:
            ADD_A_C(cpu);
            break;
        
        case Opcode::ADD_A_D:
            ADD_A_D(cpu);
            break;

        case Opcode::ADD_A_E:
            ADD_A_E(cpu);
            break;
        
        case Opcode::ADD_A_H:
            ADD_A_H(cpu);
            break;
        
        case Opcode::ADD_A_L:
            ADD_A_L(cpu);
            break;
        
        case Opcode::ADD_A_ADDR_HL:
            ADD_A_ADDR_HL(cpu);
            break;
            
        case Opcode::ADD_A_A:
            ADD_A_A(cpu);
            break;

        case Opcode::ADC_A_B:
            ADC_A_B(cpu);
            break;

        case Opcode::ADC_A_C:
            ADC_A_C(cpu);
            break;

        case Opcode::ADC_A_D:
            ADC_A_D(cpu);
            break;
        
        case Opcode::ADC_A_E:
            ADC_A_E(cpu);
            break;
        
        case Opcode::ADC_A_H:
            ADC_A_H(cpu);
            break;
        
        case Opcode::ADC_A_L:
            ADC_A_L(cpu);
            break;
        
        case Opcode::ADC_A_ADDR_HL:
            ADC_A_ADDR_HL(cpu);
            break;
        
        case Opcode::ADC_A_A:
            ADC_A_A(cpu);
            break;
        
        case Opcode::SUB_B:
            SUB_B(cpu);
            break;
        
        case Opcode::SUB_C:
            SUB_C(cpu);
            break;
        
        case Opcode::SUB_D:
            SUB_D(cpu);
            break;
        
        case Opcode::SUB_E:
            SUB_E(cpu);
            break;
        
        case Opcode::SUB_H:
            SUB_H(cpu);
            break;
        
        case Opcode::SUB_L:
            SUB_L(cpu);
            break;
        
        case Opcode::SUB_ADDR_HL:
            SUB_ADDR_HL(cpu);
            break;
        
        case Opcode::SUB_A:
            SUB_A(cpu);
            break;
        
        case Opcode::SBC_A_B:
            SBC_A_B(cpu);
            break;
        
        case Opcode::SBC_A_C:
            SBC_A_C(cpu);
            break;
        
        case Opcode::SBC_A_D:
            SBC_A_D(cpu);
            break;
        
        case Opcode::SBC_A_E:
            SBC_A_E(cpu);
            break;
        
        case Opcode::SBC_A_H:
            SBC_A_H(cpu);
            break;
        
        case Opcode::SBC_A_L:
            SBC_A_L(cpu);
            break;
        
        case Opcode::SBC_A_ADDR_HL:
            SBC_A_ADDR_HL(cpu);
            break;

        case Opcode::SBC_A_A:
            SBC_A_A(cpu);
            break;
        
        case Opcode::AND_B:
            AND_B(cpu);
            break;
        
        case Opcode::AND_C:
            AND_C(cpu);
            break;
        
        case Opcode::AND_D:
            AND_D(cpu);
            break;
        
        case Opcode::AND_E:
            AND_E(cpu);
            break;
        
        case Opcode::AND_H:
            AND_H(cpu);
            break;
        
        case Opcode::AND_L:
            AND_L(cpu);
            break;
        
        case Opcode::AND_ADDR_HL:
            AND_ADDR_HL(cpu);
            break;

        case Opcode::AND_A:
            AND_A(cpu);
            break;
        
        case Opcode::XOR_B:
            XOR_B(cpu);
            break;
        
        case Opcode::XOR_C:
            XOR_C(cpu);
            break;
        
        case Opcode::XOR_D:
            XOR_D(cpu);
            break;
        
        case Opcode::XOR_E:
            XOR_E(cpu);
            break;
        
        case Opcode::XOR_H:
            XOR_H(cpu);
            break;
        
        case Opcode::XOR_L:
            XOR_L(cpu);
            break;
        
        case Opcode::XOR_ADDR_HL:
            XOR_ADDR_HL(cpu);
            break;
        
        case Opcode::XOR_A:
            XOR_A(cpu);
            break;
        
        case Opcode::OR_B:
            OR_B(cpu);
            break;
        
        case Opcode::OR_C:
            OR_C(cpu);
            break;
        
        case Opcode::OR_D:
            OR_D(cpu);
            break;
        
        case Opcode::OR_E:
            OR_E(cpu);
            break;
        
        case Opcode::OR_H:
            OR_H(cpu);
            break;
        
        case Opcode::OR_L:
            OR_L(cpu);
            break;
        
        case Opcode::OR_ADDR_HL:
            OR_ADDR_HL(cpu);
            break;
            
        case Opcode::OR_A:
            OR_A(cpu);
            break;
        
        case Opcode::CP_B:
            CP_B(cpu);
            break;
        
        case Opcode::CP_C:
            CP_C(cpu);
            break;
        
        case Opcode::CP_D:
            CP_D(cpu);
            break;
        
        case Opcode::CP_E:
            CP_E(cpu);
            break;
        
        case Opcode::CP_H:
            CP_H(cpu);
            break;
        
        case Opcode::CP_L:
            CP_L(cpu);
            break;
        
        case Opcode::CP_ADDR_HL:
            CP_ADDR_HL(cpu);
            break;
        
        case Opcode::CP_A:
            CP_A(cpu);
            break;
        
        case Opcode::RET_NZ:
            RET_NZ(cpu);
            break;
        
        case Opcode::POP_BC:
            POP_BC(cpu);
            break;
        
        case Opcode::JP_NZ_A16:
            JUMP_NZ(cpu);
            break;
        
        case Opcode::JP_A16:
            JUMP(cpu);
            break;
        
        case Opcode::CALL_NZ_A16:
            CALL_NZ(cpu);
            break;
        
        case Opcode::PUSH_BC:
            PUSH_BC(cpu);
            break;
        
        case Opcode::ADD_A_D8:
            ADD_A_D8(cpu);
            break;
        
        case Opcode::RST_00H:
            RST(0x00);
            break;
        
        case Opcode::RET_Z:
            RET_Z(cpu);
            break;
        
        case Opcode::RET:
            RET(cpu);
            break;
        
        case Opcode::JP_Z_A16:
            JUMP_Z(cpu);
            break;
        
        case Opcode::PREFIX_CB:
            PREFIX_CB(cpu);
            break;
        
        case Opcode::CALL_Z_A16: 
            CALL_Z(cpu);
            break;
        
        case Opcode::CALL_A16:
            CALL(cpu);
            break;
        
        case Opcode::ADC_A_D8:
            ADC_A_D8(cpu);
            break;
        
        case Opcode::RST_08H:
            RST(0x08);
            break;
        
        case Opcode::RET_NC:
            RET_NC(cpu);
            break;
        
        case Opcode::POP_DE:
            POP_DE(cpu);
            break;
        
        case Opcode::JP_NC_A16:
            JUMP_NC(cpu);
            break;
        
        case Opcode::CALL_NC_A16:
            CALL_NC(cpu);
            break;
        
        case Opcode::PUSH_DE:
            PUSH_DE(cpu);
            break;
        
        case Opcode::SUB_D8:
            SUB_D8(cpu);
            break;
        
        case Opcode::RST_10H:
            RST(0x10);
            break;
        
        case Opcode::RET_C:
            RET_C(cpu);
            break;
        
        case Opcode::RETI:
            RETI(cpu);
            break;
        
        case Opcode::JP_C_A16:
            JUMP_C(cpu);
            break;
        
        case Opcode::CALL_C_A16:
            CALL_C(cpu);
            break;
        
        case Opcode::SBC_A_D8:
            SBC_A_D8(cpu);
            break;
        
        case Opcode::RST_18H:
            RST(0x18);
            break;
        
        case Opcode::LDH_ADDR_A8_A:
            LDH_ADDR_A8_A(cpu);
            break;
        
        case Opcode::POP_HL:
            POP_HL(cpu);
            break;
        
        case Opcode::LD_ADDR_C_A:
            LD_ADDR_C_A(cpu); 
            break;

        case Opcode::PUSH_HL:
            PUSH_HL(cpu);
            break;
        
        case Opcode::AND_D8:
            AND_D8(cpu);
            break;
        
        case Opcode::RST_20H:
            RST(0x20);
            break;
        
        case Opcode::ADD_SP_R8:
            ADD_SP_R8(cpu);
            break;
        
        case Opcode::JP_ADDR_HL:
            JUMP_ADDR_HL(cpu);
            break;
        
        case Opcode::LD_ADDR_A16_A:
            LD_ADDR_A16_A(cpu);
            break;

        case Opcode::XOR_D8:
            XOR_D8(cpu);
            break;
        
        case Opcode::RST_28H:
            RST(0x28);
            break;
        
        case Opcode::LDH_A_ADDR_A8:
            LDH_A_ADDR_A8(cpu);
            break;
        
        case Opcode::POP_AF:
            POP_AF(cpu);
            break;
        
        case Opcode::LD_A_ADDR_C:
            LD_A_ADDR_C(cpu);
            break;
        
        case Opcode::DI:
            DI(cpu);
            break;
        
        case Opcode::PUSH_AF:
            PUSH_AF(cpu);
            break;
        
        case Opcode::OR_D8:
            OR_D8(cpu);
            break;
        
        case Opcode::RST_30H:
            RST(0x30);
            break;
        
        case Opcode::LD_HL_SPR8:
            LD_HL_SPR8(cpu);
            break;
        
        case Opcode::LD_SP_HL:
            LD_SP_HL(cpu);
            break;
        
        case Opcode::LD_A_ADDR_A16:
            LD_A_ADDR_A16(cpu);
            break;
        
        case Opcode::EI:
            EI(cpu);
            break;
        
        case Opcode::CP_D8:
            CP_D8(cpu);
            break;
        
        case Opcode::RST_38H:
            RST(0x38);
            break;

        default:
            throw UnimplementedOperation("Invalid Opcode");
            break;
    }
}

// void Cpu::Load(uint8_t & reg) {
//     reg = m_mainMemory->Read(m_programCounter + 1);
//     m_programCounter += 2;
//     m_cycles += 8;
// }

// void Cpu::Load(uint8_t & reg, uint8_t value) {
//     reg = value;
//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::Load(uint8_t & reg, uint16_t const addr) {
//     reg = m_mainMemory->Read(addr);
//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::Load(uint16_t const address, uint8_t const value) {
//     m_mainMemory->Write(address, value);
//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::IncrementRegister(Byte& reg) {

//     m_flags.resetSubtract();

//     if ( (((reg & 0xf) + (1 & 0xf)) & 0x10) == 0x10) {
//         m_flags.setHalfCarry();
//     }

//     reg++;

//     if (reg == 0) {
//         m_flags.setZero();
//     }

 
//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::DecrementRegister(Byte& reg) {
    
//     Logger::Log(LogLevel::Debug, "Decrement register");

//     m_flags.resetSubtract();

//     if((((reg  & 0x0f) - (1 & 0x0f)) & 0x10) == 0x10) {
//         m_flags.setHalfCarry();
//     } 

//     reg--;

//     if (reg == 0) {
//         m_flags.setZero();
//     }

    
//     // Set if no borrow from bit 4

//     m_programCounter++;
//     m_cycles += 4;
// }

// uint16_t Cpu::CombineRegisters(const Byte& high, const Byte& low) const {

//     uint16_t combinedRegister = (high << 8) | low;

//     return combinedRegister;
// }

// void Cpu::AddRegisters(Byte& to, const Byte& from) {

//     m_flags.resetSubtract();

//     if ( (((to & 0xf) + ( (from +1) &0xf)) & 0x10) == 0x10) {
//         m_flags.setHalfCarry();
//     } 

//     if( (static_cast<int>(to) + static_cast<int>(from)) > 0xFF) {
//         m_flags.setCarry();
//     }

//     if(to == 0) {
//         m_flags.setZero();
//     }


//     to += from;

//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::SubtractFromA(uint8_t value) {

//     Logger::Log(LogLevel::Debug, "Subtract Register from A");

//     m_flags.setSubtract();

//     if (value > m_regA) {
//         m_flags.setCarry();
//     }

//     m_regA -= value;

//     if(m_regA == 0) {
//         m_flags.setZero();
//     }


//     m_programCounter++;
//     m_cycles += 8;
//     //Check borrow from 4 bit

// }

// void Cpu::SubtractFromAddress(uint16_t address) {

//     Logger::Log(LogLevel::Debug, "Subtract address from A");

//     m_flags.setSubtract();

//     auto value = m_mainMemory->Read(address);    

//     if (value > m_regA) {
//         m_flags.setCarry();
//     }

//     m_regA -= value;

//     if(m_regA == 0) {
//         m_flags.setZero();
//     }



//     //H - set if no borrow from bit 4
//     //C - set if no borrow

//     m_cycles += 8;
//     m_programCounter++;
// }

// void Cpu::SubtractImmediateByte() {

//     Logger::Log(LogLevel::Debug, "Subtract n From A");

//     m_flags.setSubtract();

//     auto value = m_mainMemory->Read(m_programCounter + 1);
//     m_regA -= value;

//     if(m_regA == 0) {
//         m_flags.setZero();
//     }

//     //H - set if no borrow from bit 4
//     //C - set if no borrow

//     m_programCounter += 2;
//     m_cycles += 8;
// }

// void Cpu::UnimplementedOperation(std::string const & message) const {

//     Logger::Log(LogLevel::Error, "Unimplemented operation: \t" + message);
//     std::cin.get();
// }

// void Cpu::And() {
//     auto value = m_mainMemory->Read(m_programCounter + 1);

//     m_regA &= value;
//     SetAndFlags(m_regA);

//     m_programCounter +=2;
//     m_cycles += 8;
// }

// void Cpu::And(uint8_t const value) {
    
//     m_regA &= value;
//     SetAndFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::And(uint16_t const address) {
//     auto value = m_mainMemory->Read(address);

//     m_regA &= value;
//     SetAndFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::SetAndFlags(uint8_t const value) {
    
//     if (value == 0) {
//         m_flags.setZero();
//     }

//     m_flags.resetSubtract();
//     m_flags.setHalfCarry();
//     m_flags.resetCarry();
// }

// void Cpu::Or() {

//     auto value = m_mainMemory->Read(m_programCounter + 1);
    
//     m_regA |= value;
//     SetOrFlags(m_regA);

//     m_programCounter += 2;
//     m_cycles += 8;
// }

// void Cpu::Or(uint8_t const value) {

//     m_regA |= value;
//     SetOrFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::Or(uint16_t const address) {

//     auto value = m_mainMemory->Read(address);

//     m_regA |= value;

//     SetOrFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::SetOrFlags(uint8_t const result) {
    
//     if (result == 0) {
//         m_flags.setZero();
//     }

//     m_flags.resetSubtract();
//     m_flags.resetHalfCarry();
//     m_flags.resetCarry();
// }

// void Cpu::Xor() {
//     auto value = m_mainMemory->Read(m_programCounter + 1);

//     m_regA ^= value;
//     SetOrFlags(m_regA);

//     m_programCounter += 2;
//     m_cycles += 8;
// }

// void Cpu::Xor(uint8_t const value) {
    
//     m_regA ^= value;
//     SetOrFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::Xor(uint16_t const address) {
//     auto value = m_mainMemory->Read(address);

//     m_regA ^= value;
//     SetOrFlags(m_regA);

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::CompareWithA(const Byte& reg) {

//     Logger::Log(LogLevel::Debug, "Compare register with A");

//     if(m_regA == reg) {
//        m_flags.setZero();
//     }

//     m_flags.setSubtract();

//     //Set H if no borrow from bit 4

//     if(m_regA < reg) {
//         m_flags.setCarry();
//     }
// }

// void Cpu::DisableInterrupts() {
    
//     m_programCounter++;
// }

 
//  void Cpu::ComplementA() {

//     m_regA = ~m_regA;

//     m_flags.setSubtract();
//     m_flags.setHalfCarry();

//     m_programCounter++;
//     m_cycles += 4;
//  }

//  void Cpu::ComplementCarryFlag() {

//     m_flags.flipCarry();

//     m_flags.resetSubtract();
//     m_flags.resetHalfCarry();

//     m_programCounter++;
//     m_cycles += 4;
//  }

//  void Cpu::SetCarryFlag() {

//     m_flags.setCarry();
//     m_flags.resetSubtract();
//     m_flags.resetHalfCarry();

//     m_programCounter++;
//     m_cycles += 4;
//  }

//  void Cpu::Call() {

//     auto address = m_programCounter + 3;

//     m_mainMemory->Write(m_stackPtr, address);
//     m_mainMemory->Write(m_stackPtr - 1, (address >> 8));
//     m_stackPtr -= 2;

//     m_programCounter = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
//     m_cycles += 12;
//  }


//  void Cpu::Ret() {
//      auto address = CombineRegisters(m_mainMemory->Read(m_stackPtr + 1), m_mainMemory->Read(m_stackPtr));
//      m_stackPtr += 2;

//      m_programCounter = address;
//      m_cycles += 12;
//  }

//  void Cpu::ExecuteCB() {

//      auto opcode = m_mainMemory->Read(m_programCounter);

//     Logger::Log(LogLevel::Debug, "Program counter: \t" + std::to_string(m_programCounter));
//     Logger::Log(LogLevel::Debug, "Opcode: \t" + std::to_string(opcode));

//      switch (static_cast<CBCode>(opcode)) {
//          case CBCode::RLC_B:
//             UnimplementedOperation("RLC B");
//             break;
        
//         case CBCode::RLC_C :
//             UnimplementedOperation("RLC C");
//             break;
        
//         case CBCode::RLC_D:
//             UnimplementedOperation("RLC D");
//             break;
        
//         case CBCode::RLC_E:
//             UnimplementedOperation("RLC E");
//             break;
        
//         case CBCode::RLC_H:
//             UnimplementedOperation("RLC H");
//             break;
        
//         case CBCode::RLC_L:
//             UnimplementedOperation("RLC L");
//             break;
        
//         case CBCode::RLC_ADDR_HL:
//             UnimplementedOperation("RLC (HL)");
//             break;
        
//         case CBCode::RLC_A:
//             UnimplementedOperation("RLC A");
//             break;
        
//         case CBCode::RRC_B:
//             UnimplementedOperation("RRC B");
//             break;
        
//         case CBCode::RRC_C:
//             UnimplementedOperation("RRC C");
//             break;
        
//         case CBCode::RRC_D:
//             UnimplementedOperation("RRC D");
//             break;
        
//         case CBCode::RRC_E:
//             UnimplementedOperation("RRC E");
//             break;
        
//         case CBCode::RRC_H:
//             UnimplementedOperation("RRC H");
//             break;
        
//         case CBCode::RRC_L:
//             UnimplementedOperation("RRC L");
//             break;
        
//         case CBCode::RRC_ADDR_HL:
//             UnimplementedOperation("RRC (HL");
//             break;
        
//         case CBCode::RRC_A:
//             UnimplementedOperation("RRC A");
//             break;
        
//         case CBCode::RR_C:
//             RR(m_regC);
//             break;
        
//         case CBCode::RR_D:
//             RR(m_regD);
//             break;

//         case CBCode::SRL_B:
//             SRL(m_regB);
//             break;

//         case CBCode::RES_6_A:
//             m_regA &= ~(1ul << 6);
//             m_programCounter++;
//             break;
        
//         default:
//             UnimplementedOperation("Unavailable Opcode\n");
//             break;
//      }

//  }

// void Cpu::JumpRelativeNZ() {

//     if (m_flags.zeroFlag() == FlagState::Reset) {
//         m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
//     } else {
//         m_programCounter += 2;
//     }

//     m_cycles += 8;
// }

// void Cpu::JumpRelativeNC() {

//     if (m_flags.carryFlag() == FlagState::Reset) {
//         m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
//     } else {
//         m_programCounter += 2;
//     }

//     m_cycles += 8;
// }

// void Cpu::JumpRelativeC() {

//     if (m_flags.carryFlag() == FlagState::Set) {
//         m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
//     } else {
//         m_programCounter += 2;
//     }

//     m_cycles += 8;
// }

// void Cpu::Pop(uint8_t& high, uint8_t& low) {
//     high = m_mainMemory->Read(m_stackPtr + 1);
//     low = m_mainMemory->Read(m_stackPtr);

//     m_stackPtr += 2;
//     m_programCounter++;
// }

// void Cpu::Restart(uint8_t address) {
//     m_mainMemory->Write(m_stackPtr, m_programCounter);
//     m_stackPtr--;

//     m_programCounter += 0x000 + address;
//     m_cycles += 32;
// }

// void Cpu::LDHAN() {
//     auto address = +0xFF00 + m_mainMemory->Read(m_programCounter + 1);

//     m_regA = m_mainMemory->Read(address);

//     m_programCounter++;
// }

// void Cpu::Push(uint8_t high, uint8_t low) {
//     m_mainMemory->Write(m_stackPtr, high);
//     m_stackPtr--;

//     m_mainMemory->Write(m_stackPtr, low);
//     m_stackPtr--;

//     m_programCounter++;
// }

// void Cpu::LoadImmediate16BitValue(uint8_t& high, uint8_t& low) {

//     high = m_mainMemory->Read(m_programCounter + 2);
//     low = m_mainMemory->Read(m_programCounter + 1);

//     m_programCounter += 3;
//     m_cycles += 12;
// }

// void Cpu::LoadImmediate16BitValue(uint16_t& to) {
//     auto value = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
//     to = value;

//     m_programCounter += 3;
//     m_cycles += 12;
// }

// void Cpu::LoadStackPointerFromHL() {
//     auto value = CombineRegisters(m_regH, m_regL);
//     m_stackPtr = value;

//     m_programCounter++;
//     m_cycles += 8;
// }
    

// void Cpu::IncrementAtAddress(uint16_t address) {
    
//     uint8_t value = m_mainMemory->Read(address);

//     if ( (((value & 0xf) + ( (value +1) &0xf)) & 0x10) == 0x10) {
//         m_flags.setHalfCarry();
//     } 

//     value++;

//     if(value == 0) {
//         m_flags.setZero();
//     }

//     m_flags.resetSubtract();

//     m_mainMemory->Write(address, value);

//     m_programCounter++;
//     m_cycles += 12;
// }

// void Cpu::IncrementRegisterPair(uint8_t& high, uint8_t& low) {
    
//     auto value = CombineRegisters(high, low);
//     value++;

//     high = value >> 8;
//     low = value;

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::IncrementStackpointer() {
//     m_stackPtr++;

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::DecrementRegisterPair(uint8_t& high, uint8_t& low) {
//         uint16_t value = CombineRegisters(high, low);
//         value--;

//         high = value >> 8;
//         low = value;

//         m_programCounter++;
//         m_cycles+= 8;
// }

// void Cpu::DecrementStackPointer() {
//     m_stackPtr--;

//     m_programCounter++;
//     m_cycles += 8;
// }

// void Cpu::DecrementAtAddress(uint16_t address) {
    
//     auto value = m_mainMemory->Read(address);
//     value--;

//     m_mainMemory->Write(address, value);

//     m_programCounter++;
//     m_cycles += 12;
// }


// void Cpu::RLCA() {

//     if ( (m_regA & 0b10000000) == 0b10000000) {
//         m_flags.setCarry();
//     } else {
//         m_flags.resetCarry();
//     }

//     m_regA = m_regA << 1;

//     if (m_regA == 0) {
//         m_flags.zeroFlag();
//     }

//     m_flags.resetSubtract();
//     m_flags.resetHalfCarry();

//     m_programCounter++;
//     m_cycles += 4;
// }

// void Cpu::JumpRelative() {

//     auto r8 = m_mainMemory->Read(m_programCounter + 1);
//     m_programCounter += static_cast<int16_t>(r8);
//     m_cycles += 8;
// }

// void Cpu::JumpRelativeZ() {

//     if(m_flags.zeroFlag() == FlagState::Set)
//     {
//         m_programCounter += static_cast<int16_t>(m_mainMemory->Read(m_programCounter + 1));
//     } else {
//         m_programCounter++;
//     }

//     m_cycles += 8;
// }

// void Cpu::RetNZ() {

//     if(m_flags.zeroFlag() == FlagState::Reset) {
//         Ret();
//     } else {
//         m_programCounter++;
//         m_cycles += 8;
//     }
// }

// void Cpu::Jump() {
//     auto address = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
//     m_programCounter = address;
//     m_cycles += 12;
// }