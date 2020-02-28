#include <cpu/Cpu.h>
#include <cpu/Operations.h>
#include <cpu/Opcodes.h>
#include <cpu/CBOperations.h>
#include <cpu/CBOpcodes.h>
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
    //std::cout << "Opcode: " << std::hex << (int) opcode << "\n";
    //std::cout << "Program Counter: " << (int) cpu.m_program_counter << "\n";

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
            LD_ADDR_A16_SP(cpu);
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
            CPL(cpu);
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
            ADD_HL_SP(cpu);
            break;
        
        case Opcode::LD_A_ADDR_HLD:
            LD_A_ADDR_HLD(cpu);
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
            RST(cpu, 0x00);
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
            RST(cpu, 0x08);
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
            RST(cpu, 0x10);
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
            RST(cpu, 0x18);
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
            RST(cpu, 0x20);
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
            RST(cpu, 0x28);
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
            RST(cpu, 0x30);
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
            RST(cpu, 0x38);
            break;

        default:
            throw UnimplementedOperation("Invalid Opcode");
            break;
    }
}

 void step_cb(Cpu& cpu) {

     auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter);

     switch (static_cast<CBCode>(opcode)) {
         case CBCode::RLC_B:
            throw UnimplementedOperation("RLC B");
            break;
        
        case CBCode::RLC_C :
            throw UnimplementedOperation("RLC C");
            break;
        
        case CBCode::RLC_D:
            throw UnimplementedOperation("RLC D");
            break;
        
        case CBCode::RLC_E:
            throw UnimplementedOperation("RLC E");
            break;
        
        case CBCode::RLC_H:
            throw UnimplementedOperation("RLC H");
            break;
        
        case CBCode::RLC_L:
            throw UnimplementedOperation("RLC L");
            break;
        
        case CBCode::RLC_ADDR_HL:
            throw UnimplementedOperation("RLC (HL)");
            break;
        
        case CBCode::RLC_A:
            throw UnimplementedOperation("RLC A");
            break;
        
        case CBCode::RRC_B:
            throw UnimplementedOperation("RRC B");
            break;
        
        case CBCode::RRC_C:
            throw UnimplementedOperation("RRC C");
            break;
        
        case CBCode::RRC_D:
            throw UnimplementedOperation("RRC D");
            break;
        
        case CBCode::RRC_E:
            throw UnimplementedOperation("RRC E");
            break;
        
        case CBCode::RRC_H:
            throw UnimplementedOperation("RRC H");
            break;
        
        case CBCode::RRC_L:
            throw UnimplementedOperation("RRC L");
            break;
        
        case CBCode::RRC_ADDR_HL:
            throw UnimplementedOperation("RRC (HL");
            break;
        
        case CBCode::RRC_A:
            throw UnimplementedOperation("RRC A");
            break;
        
        case CBCode::RL_B:
            throw UnimplementedOperation("RL B\n");
            break;
        
        case CBCode::RL_C:
            throw UnimplementedOperation("RL C\n");
            break;
        
        case CBCode::RL_D:
            throw UnimplementedOperation("RL D\n");
            break;
        
        case CBCode::RL_E:
            throw UnimplementedOperation("RL E\n");
            break;
        
        case CBCode::RL_H:
            throw UnimplementedOperation("RL H\n");
            break;

        case CBCode::RL_ADDR_HL:
            throw UnimplementedOperation("RL ADDR HL\n");
            break;
        
        case CBCode::RL_A:
            throw UnimplementedOperation("RL A\n");
            break;

        case CBCode::RR_B:
            throw UnimplementedOperation("RR B\n");
            break;

        case CBCode::RR_C:
            RR_C(cpu);
            break;
        
        case CBCode::RR_D:
            RR_D(cpu);
            break;

        case CBCode::RR_E:
            RR_E(cpu);
            break;

        case CBCode::RR_H:
            throw UnimplementedOperation("RR H\n");
            break;

        case CBCode::RR_L:
            throw UnimplementedOperation("RR L\n");
            break;    
            
        case CBCode::RR_ADDR_HL:
            throw UnimplementedOperation("RR ADDR HL\n");
            break;

        case CBCode::RR_A:
            throw UnimplementedOperation("RR A\n");
            break;
        
        case CBCode::SLA_B:
            throw UnimplementedOperation("SLA B\n");
            break;

        case CBCode::SLA_C:
            throw UnimplementedOperation("SLA C\n");
            break;

        case CBCode::SLA_D:
            throw UnimplementedOperation("SLA D\n");
            break;

        case CBCode::SLA_E:
            throw UnimplementedOperation("SLA E\n");
            break;

        case CBCode::SLA_H:
            throw UnimplementedOperation("SLA H\n");
            break;

        case CBCode::SLA_L:
            throw UnimplementedOperation("SLA L\n");
            break;

        case CBCode::SLA_ADDR_HL:
            throw UnimplementedOperation("SLA HL\n");
            break;

        case CBCode::SLA_A:
            throw UnimplementedOperation("SLA A\n");
            break;

        case CBCode::SRA_B:
            throw UnimplementedOperation("SRL B\n");
            break;

        case CBCode::SRA_C:
            throw UnimplementedOperation("SRL C\n");
            break;

        case CBCode::SRA_D:
            throw UnimplementedOperation("SRL D\n");
            break;

        case CBCode::SRA_E:
            throw UnimplementedOperation("SRL E\n");
            break;

        case CBCode::SRA_H:
            throw UnimplementedOperation("SRL H\n");
            break;

        case CBCode::SRA_L:
            throw UnimplementedOperation("SRL L\n");
            break;

        case CBCode::SRA_ADDR_HL:
            throw UnimplementedOperation("SRL HL\n");
            break;
        
        case CBCode::SRA_A:
            throw UnimplementedOperation("SRL A\n");
            break;
        
        case CBCode::SWAP_B:
            throw UnimplementedOperation("SWAP B\n");
            break;

        case CBCode::SWAP_C:
            throw UnimplementedOperation("SWAP C\n");
            break;

        case CBCode::SWAP_D:
            throw UnimplementedOperation("SWAP D\n");
            break;

        case CBCode::SWAP_E:
            throw UnimplementedOperation("SWAP E\n");
            break;

        case CBCode::SWAP_H:
            throw UnimplementedOperation("SWAP H\n");
            break;

        case CBCode::SWAP_L:
            throw UnimplementedOperation("SWAP L\n");
            break;

        case CBCode::SWAP_ADDR_HL:
            throw UnimplementedOperation("SWAP ADDR HL\n");
            break;

        case CBCode::SWAP_A:
            SWAP_A(cpu);
            break;
        
        case CBCode::SRL_B:
            SRL_B(cpu);            
            break;

        case CBCode::SRL_C:
            throw UnimplementedOperation("SRL C\n");
            break;

        case CBCode::SRL_D:
            throw UnimplementedOperation("SRL D\n");
            break;

        case CBCode::SRL_E:
            throw UnimplementedOperation("SRL E\n");
            break;

        case CBCode::SRL_H:
            throw UnimplementedOperation("SRL H\n");
            break;

        case CBCode::SRL_L:
            throw UnimplementedOperation("SRL L\n");
            break;

        case CBCode::SRL_ADDR_HL:
            throw UnimplementedOperation("SRL ADDR HL\n");
            break;

        case CBCode::SRL_A:
            SRL_A(cpu);
            break;
        
        case CBCode::BIT_0_B:
            BIT_0_B(cpu);
            break;
        
        case CBCode::BIT_0_C:
            BIT_0_C(cpu);
            break;

        case CBCode::BIT_0_D:
            BIT_0_D(cpu);
            break;

        case CBCode::BIT_0_E:
            BIT_0_E(cpu);
            break;

        case CBCode::BIT_0_H:
            BIT_0_H(cpu);
            break;

        case CBCode::BIT_0_L:
            BIT_0_L(cpu);
            break;

        case CBCode::BIT_0_ADDR_HL:
            BIT_0_ADDR_HL(cpu);
            break;

        case CBCode::BIT_0_A:
            BIT_0_A(cpu);
            break;

        case CBCode::BIT_1_B:
            BIT_1_B(cpu);
            break;
        
        case CBCode::BIT_1_C:
            BIT_1_C(cpu);
            break;

        case CBCode::BIT_1_D:
            BIT_1_D(cpu);
            break;

        case CBCode::BIT_1_E:
            BIT_1_E(cpu);
            break;

        case CBCode::BIT_1_H:
            BIT_1_H(cpu);
            break;

        case CBCode::BIT_1_L:
            BIT_1_L(cpu);
            break;

        case CBCode::BIT_1_ADDR_HL:
            BIT_1_ADDR_HL(cpu);
            break;

        case CBCode::BIT_1_A:
            BIT_1_A(cpu);
            break;

        case CBCode::BIT_2_B:
            BIT_2_B(cpu);
            break;
        
        case CBCode::BIT_2_C:
            BIT_2_C(cpu);
            break;

        case CBCode::BIT_2_D:
            BIT_2_D(cpu);
            break;

        case CBCode::BIT_2_E:
            BIT_2_E(cpu);
            break;

        case CBCode::BIT_2_H:
            BIT_2_H(cpu);
            break;

        case CBCode::BIT_2_L:
            BIT_2_L(cpu);
            break;

        case CBCode::BIT_2_ADDR_HL:
            BIT_2_ADDR_HL(cpu);
            break;

        case CBCode::BIT_2_A:
            BIT_2_A(cpu);
            break;

        case CBCode::BIT_3_B:
            BIT_3_B(cpu);
            break;
        
        case CBCode::BIT_3_C:
            BIT_3_C(cpu);
            break;

        case CBCode::BIT_3_D:
            BIT_3_D(cpu);
            break;

        case CBCode::BIT_3_E:
            BIT_3_E(cpu);
            break;

        case CBCode::BIT_3_H:
            BIT_3_H(cpu);
            break;

        case CBCode::BIT_3_L:
            BIT_3_L(cpu);
            break;

        case CBCode::BIT_3_ADDR_HL:
            BIT_3_ADDR_HL(cpu);
            break;

        case CBCode::BIT_3_A:
            BIT_3_A(cpu);
            break;
       
       case CBCode::BIT_4_B:
            BIT_4_B(cpu);
            break;
        
        case CBCode::BIT_4_C:
            BIT_4_C(cpu);
            break;

        case CBCode::BIT_4_D:
            BIT_4_D(cpu);
            break;

        case CBCode::BIT_4_E:
            BIT_4_E(cpu);
            break;

        case CBCode::BIT_4_H:
            BIT_4_H(cpu);
            break;

        case CBCode::BIT_4_L:
            BIT_4_L(cpu);
            break;

        case CBCode::BIT_4_ADDR_HL:
            BIT_4_ADDR_HL(cpu);
            break;

        case CBCode::BIT_4_A:
            BIT_4_A(cpu);
            break;

       case CBCode::BIT_5_B:
            BIT_5_B(cpu);
            break;
        
        case CBCode::BIT_5_C:
            BIT_5_C(cpu);
            break;

        case CBCode::BIT_5_D:
            BIT_5_D(cpu);
            break;

        case CBCode::BIT_5_E:
            BIT_5_E(cpu);
            break;

        case CBCode::BIT_5_H:
            BIT_5_H(cpu);
            break;

        case CBCode::BIT_5_L:
            BIT_5_L(cpu);
            break;

        case CBCode::BIT_5_ADDR_HL:
            BIT_5_ADDR_HL(cpu);
            break;

        case CBCode::BIT_5_A:
            BIT_5_A(cpu);
            break;
        
        case CBCode::BIT_6_B:
            BIT_6_B(cpu);
            break;
        
        case CBCode::BIT_6_C:
            BIT_6_C(cpu);
            break;

        case CBCode::BIT_6_D:
            BIT_6_D(cpu);
            break;

        case CBCode::BIT_6_E:
            BIT_6_E(cpu);
            break;

        case CBCode::BIT_6_H:
            BIT_6_H(cpu);
            break;

        case CBCode::BIT_6_L:
            BIT_6_L(cpu);
            break;

        case CBCode::BIT_6_ADDR_HL:
            BIT_6_ADDR_HL(cpu);
            break;

        case CBCode::BIT_6_A:
            BIT_6_A(cpu);
            break;

        case CBCode::BIT_7_B:
            BIT_7_B(cpu);
            break;
        
        case CBCode::BIT_7_C:
            BIT_7_C(cpu);
            break;

        case CBCode::BIT_7_D:
            BIT_7_D(cpu);
            break;

        case CBCode::BIT_7_E:
            BIT_7_E(cpu);
            break;

        case CBCode::BIT_7_H:
            BIT_7_H(cpu);
            break;

        case CBCode::BIT_7_L:
            BIT_7_L(cpu);
            break;

        case CBCode::BIT_7_ADDR_HL:
            BIT_7_ADDR_HL(cpu);
            break;

        case CBCode::BIT_7_A:
            BIT_7_A(cpu);
            break;
        
        case CBCode::RES_0_B:
            RES_0_B(cpu);
            break;

        case CBCode::RES_0_C:
            RES_0_C(cpu);
            break;

        case CBCode::RES_0_D:
            RES_0_D(cpu);
            break;

        case CBCode::RES_0_E:
            RES_0_E(cpu);
            break;

        case CBCode::RES_0_H:
            RES_0_H(cpu);
            break;

        case CBCode::RES_0_L:
            RES_0_L(cpu);
            break;

        case CBCode::RES_0_ADDR_HL:
            RES_0_ADDR_HL(cpu);
            break;

        case CBCode::RES_0_A:
            RES_0_A(cpu);
            break;
            
        case CBCode::RES_1_B:
            RES_1_B(cpu);
            break;

        case CBCode::RES_1_C:
            RES_1_C(cpu);
            break;

        case CBCode::RES_1_D:
            RES_1_D(cpu);
            break;

        case CBCode::RES_1_E:
            RES_1_E(cpu);
            break;

        case CBCode::RES_1_H:
            RES_1_H(cpu);
            break;

        case CBCode::RES_1_L:
            RES_1_L(cpu);
            break;

        case CBCode::RES_1_ADDR_HL:
            RES_1_ADDR_HL(cpu);
            break;

        case CBCode::RES_1_A:
            RES_1_A(cpu);
            break;
        
        case CBCode::RES_2_B:
            RES_2_B(cpu);
            break;

        case CBCode::RES_2_C:
            RES_2_C(cpu);
            break;

        case CBCode::RES_2_D:
            RES_2_D(cpu);
            break;

        case CBCode::RES_2_E:
            RES_2_E(cpu);
            break;

        case CBCode::RES_2_H:
            RES_2_H(cpu);
            break;

        case CBCode::RES_2_L:
            RES_2_L(cpu);
            break;

        case CBCode::RES_2_ADDR_HL:
            RES_2_ADDR_HL(cpu);
            break;

        case CBCode::RES_2_A:
            RES_2_A(cpu);
            break;

        case CBCode::RES_3_B:
            RES_3_B(cpu);
            break;

        case CBCode::RES_3_C:
            RES_3_C(cpu);
            break;

        case CBCode::RES_3_D:
            RES_3_D(cpu);
            break;

        case CBCode::RES_3_E:
            RES_3_E(cpu);
            break;

        case CBCode::RES_3_H:
            RES_3_H(cpu);
            break;

        case CBCode::RES_3_L:
            RES_3_L(cpu);
            break;

        case CBCode::RES_3_ADDR_HL:
            RES_3_ADDR_HL(cpu);
            break;

        case CBCode::RES_3_A:
            RES_3_A(cpu);
            break;

        case CBCode::RES_4_B:
            RES_4_B(cpu);
            break;

        case CBCode::RES_4_C:
            RES_4_C(cpu);
            break;

        case CBCode::RES_4_D:
            RES_4_D(cpu);
            break;

        case CBCode::RES_4_E:
            RES_4_E(cpu);
            break;

        case CBCode::RES_4_H:
            RES_4_H(cpu);
            break;

        case CBCode::RES_4_L:
            RES_4_L(cpu);
            break;

        case CBCode::RES_4_ADDR_HL:
            RES_4_ADDR_HL(cpu);
            break;

        case CBCode::RES_4_A:
            RES_4_A(cpu);
            break;
        
        case CBCode::RES_5_B:
            RES_5_B(cpu);
            break;

        case CBCode::RES_5_C:
            RES_5_C(cpu);
            break;

        case CBCode::RES_5_D:
            RES_5_D(cpu);
            break;

        case CBCode::RES_5_E:
            RES_5_E(cpu);
            break;

        case CBCode::RES_5_H:
            RES_5_H(cpu);
            break;

        case CBCode::RES_5_L:
            RES_5_L(cpu);
            break;

        case CBCode::RES_5_ADDR_HL:
            RES_5_ADDR_HL(cpu);
            break;

        case CBCode::RES_5_A:
            RES_5_A(cpu);
            break;
        
        case CBCode::RES_6_B:
            RES_6_B(cpu);
            break;

        case CBCode::RES_6_C:
            RES_6_C(cpu);
            break;

        case CBCode::RES_6_D:
            RES_6_D(cpu);
            break;

        case CBCode::RES_6_E:
            RES_6_E(cpu);
            break;

        case CBCode::RES_6_H:
            RES_6_H(cpu);
            break;

        case CBCode::RES_6_L:
            RES_6_L(cpu);
            break;

        case CBCode::RES_6_ADDR_HL:
            RES_6_ADDR_HL(cpu);
            break;

        case CBCode::RES_6_A:
            RES_6_A(cpu);
            break;
        
        case CBCode::RES_7_B:
            RES_7_B(cpu);
            break;

        case CBCode::RES_7_C:
            RES_7_C(cpu);
            break;

        case CBCode::RES_7_D:
            RES_7_D(cpu);
            break;

        case CBCode::RES_7_E:
            RES_7_E(cpu);
            break;

        case CBCode::RES_7_H:
            RES_7_H(cpu);
            break;

        case CBCode::RES_7_L:
            RES_7_L(cpu);
            break;

        case CBCode::RES_7_ADDR_HL:
            RES_7_ADDR_HL(cpu);
            break;

        case CBCode::RES_7_A:
            RES_7_A(cpu);
            break;
        
        case CBCode::SET_0_B:
            SET_0_B(cpu);
            break;

        case CBCode::SET_0_C:
            SET_0_C(cpu);
            break;

        case CBCode::SET_0_D:
            SET_0_D(cpu);
            break;

        case CBCode::SET_0_E:
            SET_0_E(cpu);
            break;

        case CBCode::SET_0_H:
            SET_0_H(cpu);
            break;

        case CBCode::SET_0_L:
            SET_0_L(cpu);
            break;

        case CBCode::SET_0_ADDR_HL:
            SET_0_ADDR_HL(cpu);
            break;

        case CBCode::SET_0_A:
            SET_0_A(cpu);
            break;

        case CBCode::SET_1_B:
            throw UnimplementedOperation("SET 1 B");
            break;

        case CBCode::SET_1_C:
            throw UnimplementedOperation("SET 1 C");
            break;

        case CBCode::SET_1_D:
            throw UnimplementedOperation("SET 1 D");
            break;

        case CBCode::SET_1_E:
            throw UnimplementedOperation("SET 1 E");
            break;

        case CBCode::SET_1_H:
            throw UnimplementedOperation("SET 1 H");
            break;

        case CBCode::SET_1_L:
            throw UnimplementedOperation("SET 1 L");
            break;

        case CBCode::SET_1_ADDR_HL:
            throw UnimplementedOperation("SET 1 ADDR HL");
            break;

        case CBCode::SET_1_A:
            throw UnimplementedOperation("SET 1 A");
            break;
                
        case CBCode::SET_2_B:
            throw UnimplementedOperation("SET 2 B");
            break;

        case CBCode::SET_2_C:
            throw UnimplementedOperation("SET 2 C");
            break;

        case CBCode::SET_2_D:
            throw UnimplementedOperation("SET 2 D");
            break;

        case CBCode::SET_2_E:
            throw UnimplementedOperation("SET 2 E");
            break;

        case CBCode::SET_2_H:
            throw UnimplementedOperation("SET 2 H");
            break;

        case CBCode::SET_2_L:
            throw UnimplementedOperation("SET 2 L");
            break;

        case CBCode::SET_2_ADDR_HL:
            throw UnimplementedOperation("SET 2 ADDR HL");
            break;

        case CBCode::SET_2_A:
            throw UnimplementedOperation("SET 2 A");
            break;

        case CBCode::SET_3_B:
            throw UnimplementedOperation("SET 3 B");
            break;

        case CBCode::SET_3_C:
            throw UnimplementedOperation("SET 3 C");
            break;

        case CBCode::SET_3_D:
            throw UnimplementedOperation("SET 3 D");
            break;

        case CBCode::SET_3_E:
            throw UnimplementedOperation("SET 3 E");
            break;

        case CBCode::SET_3_H:
            throw UnimplementedOperation("SET 3 H");
            break;

        case CBCode::SET_3_L:
            throw UnimplementedOperation("SET 3 L");
            break;

        case CBCode::SET_3_ADDR_HL:
            throw UnimplementedOperation("SET 3 ADDR HL");
            break;

        case CBCode::SET_3_A:
            throw UnimplementedOperation("SET 3 A");
            break;
        
        case CBCode::SET_4_B:
            throw UnimplementedOperation("SET 4 B");
            break;

        case CBCode::SET_4_C:
            throw UnimplementedOperation("SET 4 C");
            break;

        case CBCode::SET_4_D:
            throw UnimplementedOperation("SET 4 D");
            break;

        case CBCode::SET_4_E:
            throw UnimplementedOperation("SET 4 E");
            break;

        case CBCode::SET_4_H:
            throw UnimplementedOperation("SET 4 H");
            break;

        case CBCode::SET_4_L:
            throw UnimplementedOperation("SET 4 L");
            break;

        case CBCode::SET_4_ADDR_HL:
            throw UnimplementedOperation("SET 4 ADDR HL");
            break;

        case CBCode::SET_4_A:
            throw UnimplementedOperation("SET 0 A");
            break;
        
        case CBCode::SET_5_B:
            throw UnimplementedOperation("SET 5 B");
            break;

        case CBCode::SET_5_C:
            throw UnimplementedOperation("SET 5 C");
            break;

        case CBCode::SET_5_D:
            throw UnimplementedOperation("SET 5 D");
            break;

        case CBCode::SET_5_E:
            throw UnimplementedOperation("SET 5 E");
            break;

        case CBCode::SET_5_H:
            throw UnimplementedOperation("SET 5 H");
            break;

        case CBCode::SET_5_L:
            throw UnimplementedOperation("SET 5 L");
            break;

        case CBCode::SET_5_ADDR_HL:
            throw UnimplementedOperation("SET 5 ADDR HL");
            break;

        case CBCode::SET_5_A:
            throw UnimplementedOperation("SET 0 A");
            break;
        
        case CBCode::SET_6_B:
            throw UnimplementedOperation("SET 6 B");
            break;

        case CBCode::SET_6_C:
            throw UnimplementedOperation("SET 6 C");
            break;

        case CBCode::SET_6_D:
            throw UnimplementedOperation("SET 6 D");
            break;

        case CBCode::SET_6_E:
            throw UnimplementedOperation("SET 6 E");
            break;

        case CBCode::SET_6_H:
            throw UnimplementedOperation("SET 6 H");
            break;

        case CBCode::SET_6_L:
            throw UnimplementedOperation("SET 6 L");
            break;

        case CBCode::SET_6_ADDR_HL:
            throw UnimplementedOperation("SET 6 ADDR HL");
            break;

        case CBCode::SET_6_A:
            throw UnimplementedOperation("SET 6 A");
            break;
        
        case CBCode::SET_7_B:
            throw UnimplementedOperation("SET 7 B");
            break;

        case CBCode::SET_7_C:
            throw UnimplementedOperation("SET 7 C");
            break;

        case CBCode::SET_7_D:
            throw UnimplementedOperation("SET 7 D");
            break;

        case CBCode::SET_7_E:
            throw UnimplementedOperation("SET 7 E");
            break;

        case CBCode::SET_7_H:
            throw UnimplementedOperation("SET 7 H");
            break;

        case CBCode::SET_7_L:
            throw UnimplementedOperation("SET 7 L");
            break;

        case CBCode::SET_7_ADDR_HL:
            throw UnimplementedOperation("SET 7 ADDR HL");
            break;

        case CBCode::SET_7_A:
            throw UnimplementedOperation("SET 7 A");
            break;
        default:
            throw UnimplementedOperation("Unimplemented CB Code\n");
            break;
     }
 }