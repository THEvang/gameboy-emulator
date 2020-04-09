#include <cpu/Cpu.h>
#include <cpu/Operations.h>
#include <cpu/Opcodes.h>
#include <cpu/CBOperations.h>
#include <cpu/CBOpcodes.h>
#include <iostream>
#include <BitOperations.h>

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

FetchResult fetch(Cpu& cpu) {

    const auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter);

    switch(static_cast<Opcode>(opcode)) {
        case Opcode::NOP:
            return NOP(cpu);

        case Opcode::LD_BC_D16:
            return LD_BC_D16(cpu);

        case Opcode::LD_ADDR_BC_A:
            return LD_ADDR_BC_A(cpu);

        case Opcode::INC_BC:
            return INC_BC(cpu);
        
        case Opcode::INC_B:
            return INC_B(cpu);
        
        case Opcode::DEC_B:
            return DEC_B(cpu);

        case Opcode::LD_B_D8:
            return LD_B_D8(cpu);
        
        case Opcode::RLCA:
            return RLCA(cpu);

        case Opcode::LD_ADDR_A16_SP:
            return LD_ADDR_A16_SP(cpu);

        case Opcode::ADD_HL_BC:
            return ADD_HL_BC(cpu);

        case Opcode::LD_A_ADDR_BC:
            return LD_A_ADDR_BC(cpu);

        case Opcode::DEC_BC:
            return DEC_BC(cpu);
        
        case Opcode::INC_C:
            return INC_C(cpu);
        
        case Opcode::DEC_C:
            return DEC_C(cpu);
        
        case Opcode::LD_C_D8:
            return LD_C_D8(cpu);
        
        case Opcode::RRCA:
            return RRCA(cpu);
        
        case Opcode::STOP:
            return STOP(cpu);

        case Opcode::LD_DE_D16:
            return LD_DE_D16(cpu);
        
        case Opcode::LD_ADDR_DE_A:
            return LD_ADDR_DE_A(cpu);
        
        case Opcode::INC_DE:
            return INC_DE(cpu);
        
        case Opcode::INC_D:
            return INC_D(cpu);
        
        case Opcode::DEC_D:
            return DEC_D(cpu);
        
        case Opcode::LD_D_D8:
            return LD_D_D8(cpu);
        
        case Opcode::RLA:
            return RLA(cpu);

        case Opcode::JR_R8:
            return JR(cpu);
        
        case Opcode::ADD_HL_DE:
            return ADD_HL_DE(cpu);
        
        case Opcode::LD_A_ADDR_DE:
            return LD_A_ADDR_DE(cpu);
        
        case Opcode::DEC_DE:
            return DEC_DE(cpu);
        
        case Opcode::INC_E:
            return INC_E(cpu);

        case Opcode::DEC_E:
            return DEC_E(cpu);
        
        case Opcode::LD_E_D8:
            return LD_E_D8(cpu);
        
        case Opcode::RRA:
            return RRA(cpu);

        case Opcode::JR_NZ_R8:
            return JR_NZ(cpu);
        
        case Opcode::LD_HL_D16:
            return LD_HL_D16(cpu);
        
        case Opcode::LD_ADDR_HLI_A:
            return LDI_ADDR_HL_A(cpu);
        
        case Opcode::INC_HL:
            return INC_HL(cpu);

        case Opcode::INC_H:
            return INC_H(cpu);
        
        case Opcode::DEC_H:
            return DEC_H(cpu);
        
        case Opcode::LD_H_D8:
            return LD_H_D8(cpu);
        
        case Opcode::DAA:
            return DAA(cpu);
        
        case Opcode::JR_Z_R8:
            return JR_Z(cpu);

        case Opcode::ADD_HL_HL:
            return ADD_HL_HL(cpu);
        
        case Opcode::LD_A_ADDR_HLI:
            return LDI_A_ADDR_HL(cpu);
        
        case Opcode::DEC_HL:
            return DEC_HL(cpu);
        
        case Opcode::INC_L:
            return INC_L(cpu);
        
        case Opcode::DEC_L:
            return DEC_L(cpu);
        
        case Opcode::LD_L_D8:
            return LD_L_D8(cpu);
        
        case Opcode::CPL:
            return CPL(cpu);
        
        case Opcode::JR_NC_R8:
            return JR_NC(cpu);
        
        case Opcode::LD_SP_D16:
            return LD_SP_D16(cpu);
        
        case Opcode::LD_ADDR_HLD_A:
            return LD_ADDR_HLD_A(cpu);
        
        case Opcode::INC_SP:
            return INC_SP(cpu);
        
        case Opcode::INC_ADDR_HL:
            return INC_ADDR_HL(cpu);
        
        case Opcode::DEC_ADDR_HL:
            return DEC_ADDR_HL(cpu);
        
        case Opcode::LD_ADDR_HL_D8:
            return LD_ADDR_HL_D8(cpu);
        
        case Opcode::SCF:
            return SCF(cpu);
        
        case Opcode::JR_C_R8:
            return JR_C(cpu);
        
        case Opcode::ADD_HL_SP:
            return ADD_HL_SP(cpu);
        
        case Opcode::LD_A_ADDR_HLD:
            return LD_A_ADDR_HLD(cpu);
        
        case Opcode::DEC_SP:
            return DEC_SP(cpu);
        
        case Opcode::INC_A:
            return INC_A(cpu);
        
        case Opcode::DEC_A:
            return DEC_A(cpu);
        
        case Opcode::LD_A_D8:
            return LD_A_D8(cpu);

        case Opcode::CCF:
            return CCF(cpu);
        
        case Opcode::LD_B_B:
            return LD_B_B(cpu);
        
        case Opcode::LD_B_C:
            return LD_B_C(cpu);
        
        case Opcode::LD_B_D:
            return LD_B_D(cpu);
        
        case Opcode::LD_B_E:
            return LD_B_E(cpu);
        
        case Opcode::LD_B_H:
            return LD_B_H(cpu);
        
        case Opcode::LD_B_L:
            return LD_B_L(cpu);
        
        case Opcode::LD_B_ADDR_HL:
            return LD_B_ADDR_HL(cpu);
        
        case Opcode::LD_B_A:
            return LD_B_A(cpu);
        
        case Opcode::LD_C_B:
            return LD_C_B(cpu);
        
        case Opcode::LD_C_C:
            return LD_C_C(cpu);
        
        case Opcode::LD_C_D:
            return LD_C_D(cpu);
        
        case Opcode::LD_C_E:
            return LD_C_E(cpu);
        
        case Opcode::LD_C_H:
            return LD_C_H(cpu);

        case Opcode::LD_C_L:
            return LD_C_L(cpu);
        
        case Opcode::LD_C_ADDR_HL:
            return LD_C_ADDR_HL(cpu);
        
        case Opcode::LD_C_A:
            return LD_C_A(cpu);

        case Opcode::LD_D_B:
            return LD_D_B(cpu);

        case Opcode::LD_D_C:
            return LD_D_C(cpu);

        case Opcode::LD_D_D:
            return LD_D_D(cpu);

        case Opcode::LD_D_E:
            return LD_D_E(cpu);

        case Opcode::LD_D_H:
            return LD_D_H(cpu);

        case Opcode::LD_D_L:
            return LD_D_L(cpu);

        case Opcode::LD_D_ADDR_HL:
            return LD_D_ADDR_HL(cpu);

        case Opcode::LD_D_A:
            return LD_D_A(cpu);

        case Opcode::LD_E_B:
            return LD_E_B(cpu);

        case Opcode::LD_E_C:
            return LD_E_C(cpu);

        case Opcode::LD_E_D:
            return LD_E_D(cpu);

        case Opcode::LD_E_E:
            return LD_E_E(cpu);

        case Opcode::LD_E_H:
            return LD_E_H(cpu);

        case Opcode::LD_E_L:
            return LD_E_L(cpu);

        case Opcode::LD_E_ADDR_HL:
            return LD_E_ADDR_HL(cpu);

        case Opcode::LD_E_A:
            return LD_E_A(cpu);

        case Opcode::LD_H_B:
            return LD_H_B(cpu);

        case Opcode::LD_H_C:
            return LD_H_C(cpu);

        case Opcode::LD_H_D:
            return LD_H_D(cpu);

        case Opcode::LD_H_E:
            return LD_H_E(cpu);

        case Opcode::LD_H_H:
            return LD_H_H(cpu);

        case Opcode::LD_H_L:
            return LD_H_L(cpu);

        case Opcode::LD_H_ADDR_HL:
            return LD_H_ADDR_HL(cpu);

        case Opcode::LD_H_A:
            return LD_H_A(cpu);

        case Opcode::LD_L_B: 
            return LD_L_B(cpu);
        
        case Opcode::LD_L_C:
            return LD_L_C(cpu);
        
        case Opcode::LD_L_D:
            return LD_L_D(cpu);
        
        case Opcode::LD_L_E:
            return LD_L_E(cpu);
        
        case Opcode::LD_L_H:
            return LD_L_H(cpu);
        
        case Opcode::LD_L_L:
            return LD_L_L(cpu);
        
        case Opcode::LD_L_ADDR_HL:
            return LD_L_ADDR_HL(cpu);
        
        case Opcode::LD_L_A:
            return LD_L_A(cpu);
        
        case Opcode::LD_ADDR_HL_B:
            return LD_ADDR_HL_B(cpu);

        case Opcode::LD_ADDR_HL_C:
            return LD_ADDR_HL_C(cpu);

        case Opcode::LD_ADDR_HL_D:
            return LD_ADDR_HL_D(cpu);
        
        case Opcode::LD_ADDR_HL_E:
            return LD_ADDR_HL_E(cpu);
        
        case Opcode::LD_ADDR_HL_H:
            return LD_ADDR_HL_H(cpu);
        
        case Opcode::LD_ADDR_HL_L:
            return LD_ADDR_HL_L(cpu);
        
        case Opcode::HALT:
            return HALT(cpu);
        
        case Opcode::LD_ADDR_HL_A:
            return LD_ADDR_HL_A(cpu);

        case Opcode::LD_A_B:
            return LD_A_B(cpu);
        
        case Opcode::LD_A_C:
            return LD_A_C(cpu);
        
        case Opcode::LD_A_D:
            return LD_A_D(cpu);
        
        case Opcode::LD_A_E:
            return LD_A_E(cpu);
        
        case Opcode::LD_A_H:
            return LD_A_H(cpu);
        
        case Opcode::LD_A_L:
            return LD_A_L(cpu);
        
        case Opcode::LD_A_ADDR_HL:
            return LD_A_ADDR_HL(cpu);
        
        case Opcode::LD_A_A:
            return LD_A_A(cpu);
        
        case Opcode::ADD_A_B:
            return ADD_A_B(cpu);
        
        case Opcode::ADD_A_C:
            return ADD_A_C(cpu);
        
        case Opcode::ADD_A_D:
            return ADD_A_D(cpu);

        case Opcode::ADD_A_E:
            return ADD_A_E(cpu);
        
        case Opcode::ADD_A_H:
            return ADD_A_H(cpu);
        
        case Opcode::ADD_A_L:
            return ADD_A_L(cpu);
        
        case Opcode::ADD_A_ADDR_HL:
            return ADD_A_ADDR_HL(cpu);
            
        case Opcode::ADD_A_A:
            return ADD_A_A(cpu);

        case Opcode::ADC_A_B:
            return ADC_A_B(cpu);

        case Opcode::ADC_A_C:
            return ADC_A_C(cpu);

        case Opcode::ADC_A_D:
            return ADC_A_D(cpu);
        
        case Opcode::ADC_A_E:
            return ADC_A_E(cpu);
        
        case Opcode::ADC_A_H:
            return ADC_A_H(cpu);
        
        case Opcode::ADC_A_L:
            return ADC_A_L(cpu);
        
        case Opcode::ADC_A_ADDR_HL:
            return ADC_A_ADDR_HL(cpu);
        
        case Opcode::ADC_A_A:
            return ADC_A_A(cpu);
        
        case Opcode::SUB_B:
            return SUB_B(cpu);
        
        case Opcode::SUB_C:
            return SUB_C(cpu);
        
        case Opcode::SUB_D:
            return SUB_D(cpu);
        
        case Opcode::SUB_E:
            return SUB_E(cpu);
        
        case Opcode::SUB_H:
            return SUB_H(cpu);
        
        case Opcode::SUB_L:
            return SUB_L(cpu);
        
        case Opcode::SUB_ADDR_HL:
            return SUB_ADDR_HL(cpu);
        
        case Opcode::SUB_A:
            return SUB_A(cpu);
        
        case Opcode::SBC_A_B:
            return SBC_A_B(cpu);
        
        case Opcode::SBC_A_C:
            return SBC_A_C(cpu);
        
        case Opcode::SBC_A_D:
            return SBC_A_D(cpu);
        
        case Opcode::SBC_A_E:
            return SBC_A_E(cpu);
        
        case Opcode::SBC_A_H:
            return SBC_A_H(cpu);
        
        case Opcode::SBC_A_L:
            return SBC_A_L(cpu);
        
        case Opcode::SBC_A_ADDR_HL:
            return SBC_A_ADDR_HL(cpu);

        case Opcode::SBC_A_A:
            return SBC_A_A(cpu);
        
        case Opcode::AND_B:
            return AND_B(cpu);
        
        case Opcode::AND_C:
            return AND_C(cpu);
        
        case Opcode::AND_D:
            return AND_D(cpu);
        
        case Opcode::AND_E:
            return AND_E(cpu);
        
        case Opcode::AND_H:
            return AND_H(cpu);
        
        case Opcode::AND_L:
            return AND_L(cpu);
        
        case Opcode::AND_ADDR_HL:
            return AND_ADDR_HL(cpu);

        case Opcode::AND_A:
            return AND_A(cpu);
        
        case Opcode::XOR_B:
            return XOR_B(cpu);
        
        case Opcode::XOR_C:
            return XOR_C(cpu);
        
        case Opcode::XOR_D:
            return XOR_D(cpu);
        
        case Opcode::XOR_E:
            return XOR_E(cpu);
        
        case Opcode::XOR_H:
            return XOR_H(cpu);
        
        case Opcode::XOR_L:
            return XOR_L(cpu);
        
        case Opcode::XOR_ADDR_HL:
            return XOR_ADDR_HL(cpu);
        
        case Opcode::XOR_A:
            return XOR_A(cpu);
        
        case Opcode::OR_B:
            return OR_B(cpu);
        
        case Opcode::OR_C:
            return OR_C(cpu);
        
        case Opcode::OR_D:
            return OR_D(cpu);
        
        case Opcode::OR_E:
            return OR_E(cpu);
        
        case Opcode::OR_H:
            return OR_H(cpu);
        
        case Opcode::OR_L:
            return OR_L(cpu);
        
        case Opcode::OR_ADDR_HL:
            return OR_ADDR_HL(cpu);
            
        case Opcode::OR_A:
            return OR_A(cpu);
        
        case Opcode::CP_B:
            return CP_B(cpu);
        
        case Opcode::CP_C:
            return CP_C(cpu);
        
        case Opcode::CP_D:
            return CP_D(cpu);
        
        case Opcode::CP_E:
            return CP_E(cpu);
        
        case Opcode::CP_H:
            return CP_H(cpu);
        
        case Opcode::CP_L:
            return CP_L(cpu);
        
        case Opcode::CP_ADDR_HL:
            return CP_ADDR_HL(cpu);
        
        case Opcode::CP_A:
            return CP_A(cpu);
        
        case Opcode::RET_NZ:
            return RET_NZ(cpu);
        
        case Opcode::POP_BC:
            return POP_BC(cpu);

        case Opcode::JP_NZ_A16:
            return JUMP_NZ(cpu);
        
        case Opcode::JP_A16:
            return JUMP(cpu);
        
        case Opcode::CALL_NZ_A16:
            return CALL_NZ(cpu);
        
        case Opcode::PUSH_BC:
            return PUSH_BC(cpu);
        
        case Opcode::ADD_A_D8:
            return ADD_A_D8(cpu);
        
        case Opcode::RST_00H:
            return RST(cpu, 0x00);
        
        case Opcode::RET_Z:
            return RET_Z(cpu);
        
        case Opcode::RET:
            return RET(cpu);
        
        case Opcode::JP_Z_A16:
            return JUMP_Z(cpu);
        
        case Opcode::PREFIX_CB:
            return PREFIX_CB(cpu);
        
        case Opcode::CALL_Z_A16: 
            return CALL_Z(cpu);
        
        case Opcode::CALL_A16:
            return CALL(cpu);
        
        case Opcode::ADC_A_D8:
            return ADC_A_D8(cpu);
        
        case Opcode::RST_08H:
            return RST(cpu, 0x08);
        
        case Opcode::RET_NC:
            return RET_NC(cpu);
        
        case Opcode::POP_DE:
            return POP_DE(cpu);
        
        case Opcode::JP_NC_A16:
            return JUMP_NC(cpu);
        
        case Opcode::CALL_NC_A16:
            return CALL_NC(cpu);
        
        case Opcode::PUSH_DE:
            return PUSH_DE(cpu);
        
        case Opcode::SUB_D8:
            return SUB_D8(cpu);
        
        case Opcode::RST_10H:
            return RST(cpu, 0x10);
        
        case Opcode::RET_C:
            return RET_C(cpu);
        
        case Opcode::RETI:
            return RETI(cpu);
        
        case Opcode::JP_C_A16:
            return JUMP_C(cpu);
        
        case Opcode::CALL_C_A16:
            return CALL_C(cpu);
        
        case Opcode::SBC_A_D8:
            return SBC_A_D8(cpu);
        
        case Opcode::RST_18H:
            return RST(cpu, 0x18);
        
        case Opcode::LDH_ADDR_A8_A:
            return LDH_ADDR_A8_A(cpu);
        
        case Opcode::POP_HL:
            return POP_HL(cpu);
        
        case Opcode::LD_ADDR_C_A:
            return LD_ADDR_C_A(cpu); 

        case Opcode::PUSH_HL:
            return PUSH_HL(cpu);
        
        case Opcode::AND_D8:
            return AND_D8(cpu);
        
        case Opcode::RST_20H:
            return RST(cpu, 0x20);
        
        case Opcode::ADD_SP_R8:
            return ADD_SP_R8(cpu);
        
        case Opcode::JP_ADDR_HL:
            return JUMP_ADDR_HL(cpu);
        
        case Opcode::LD_ADDR_A16_A:
            return LD_ADDR_A16_A(cpu);

        case Opcode::XOR_D8:
            return XOR_D8(cpu);
        
        case Opcode::RST_28H:
            return RST(cpu, 0x28);
        
        case Opcode::LDH_A_ADDR_A8:
            return LDH_A_ADDR_A8(cpu);
        
        case Opcode::POP_AF:
            return POP_AF(cpu);
        
        case Opcode::LD_A_ADDR_C:
            return LD_A_ADDR_C(cpu);
        
        case Opcode::DI:
            return DI(cpu);
        
        case Opcode::PUSH_AF:
            return PUSH_AF(cpu);
        
        case Opcode::OR_D8:
            return OR_D8(cpu);
        
        case Opcode::RST_30H:
            return RST(cpu, 0x30);
        
        case Opcode::LD_HL_SPR8:
            return LD_HL_SPR8(cpu);
        
        case Opcode::LD_SP_HL:
            return LD_SP_HL(cpu);
        
        case Opcode::LD_A_ADDR_A16:
            return LD_A_ADDR_A16(cpu);
        
        case Opcode::EI:
            return EI(cpu);
        
        case Opcode::CP_D8:
            return CP_D8(cpu);
        
        case Opcode::RST_38H:
            return RST(cpu, 0x38);

        default:
            throw UnimplementedOperation("Invalid Opcode");
            break;
    }
}

FetchResult fetch_cb(Cpu& cpu) {

     auto opcode = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    
     switch (static_cast<CBCode>(opcode)) {
         case CBCode::RLC_B:
            return RLC_B(cpu);
        
        case CBCode::RLC_C :
            return RLC_C(cpu);
        
        case CBCode::RLC_D:
            return RLC_D(cpu);
        
        case CBCode::RLC_E:
            return RLC_E(cpu);
        
        case CBCode::RLC_H:
            return RLC_H(cpu);
        
        case CBCode::RLC_L:
            return RLC_L(cpu);
        
        case CBCode::RLC_ADDR_HL:
            return RLC_ADDR_HL(cpu);
        
        case CBCode::RLC_A:
            return RLC_A(cpu);
        
        case CBCode::RRC_B:
            return RRC_B(cpu);
        
        case CBCode::RRC_C:
            return RRC_C(cpu);
        
        case CBCode::RRC_D:
            return RRC_D(cpu);
        
        case CBCode::RRC_E:
            return RRC_E(cpu);
        
        case CBCode::RRC_H:
            return RRC_H(cpu);
        
        case CBCode::RRC_L:
            return RRC_L(cpu);
        
        case CBCode::RRC_ADDR_HL:
            return RRC_ADDR_HL(cpu);
        
        case CBCode::RRC_A:
            return RRC_A(cpu);
        
        case CBCode::RL_B:
            return RL_B(cpu);
        
        case CBCode::RL_C:
            return RL_C(cpu);
        
        case CBCode::RL_D:
            return RL_D(cpu);
        
        case CBCode::RL_E:
            return RL_E(cpu);
        
        case CBCode::RL_H:
            return RL_H(cpu);
        
        case CBCode::RL_L:
            return RL_L(cpu);

        case CBCode::RL_ADDR_HL:
            return RL_ADDR_HL(cpu);
        
        case CBCode::RL_A:
            return RL_A(cpu);

        case CBCode::RR_B:
            return RR_B(cpu);

        case CBCode::RR_C:
            return RR_C(cpu);
        
        case CBCode::RR_D:
            return RR_D(cpu);

        case CBCode::RR_E:
            return RR_E(cpu);

        case CBCode::RR_H:
            return RR_H(cpu);

        case CBCode::RR_L:
            return RR_L(cpu);
            
        case CBCode::RR_ADDR_HL:
            return RR_ADDR_HL(cpu);

        case CBCode::RR_A:
            return RR_A(cpu);
        
        case CBCode::SLA_B:
            return SLA_B(cpu);

        case CBCode::SLA_C:
            return SLA_C(cpu);

        case CBCode::SLA_D:
            return SLA_D(cpu);

        case CBCode::SLA_E:
            return SLA_E(cpu);

        case CBCode::SLA_H:
            return SLA_H(cpu);

        case CBCode::SLA_L:
            return SLA_L(cpu);

        case CBCode::SLA_ADDR_HL:
            return SLA_ADDR_HL(cpu);

        case CBCode::SLA_A:
            return SLA_A(cpu);

        case CBCode::SRA_B:
            return SRA_B(cpu);

        case CBCode::SRA_C:
            return SRA_C(cpu);

        case CBCode::SRA_D:
            return SRA_D(cpu);

        case CBCode::SRA_E:
            return SRA_E(cpu);

        case CBCode::SRA_H:
            return SRA_H(cpu);

        case CBCode::SRA_L:
            return SRA_L(cpu);

        case CBCode::SRA_ADDR_HL:
            return SRA_ADDR_HL(cpu);
        
        case CBCode::SRA_A:
            return SRA_A(cpu);
        
        case CBCode::SWAP_B:
            return SWAP_B(cpu);

        case CBCode::SWAP_C:
            return SWAP_C(cpu);

        case CBCode::SWAP_D:
            return SWAP_D(cpu);

        case CBCode::SWAP_E:
            return SWAP_E(cpu);

        case CBCode::SWAP_H:
            return SWAP_H(cpu);

        case CBCode::SWAP_L:
            return SWAP_L(cpu);

        case CBCode::SWAP_ADDR_HL:
            return SWAP_ADDR_HL(cpu);

        case CBCode::SWAP_A:
            return SWAP_A(cpu);
        
        case CBCode::SRL_B:
            return SRL_B(cpu);            

        case CBCode::SRL_C:
            return SRL_C(cpu);

        case CBCode::SRL_D:
            return SRL_D(cpu);

        case CBCode::SRL_E:
            return SRL_E(cpu);

        case CBCode::SRL_H:
            return SRL_H(cpu);

        case CBCode::SRL_L:
            return SRL_L(cpu); 

        case CBCode::SRL_ADDR_HL:
            return SRL_ADDR_HL(cpu);

        case CBCode::SRL_A:
            return SRL_A(cpu);
        
        case CBCode::BIT_0_B:
            return BIT_0_B(cpu);
        
        case CBCode::BIT_0_C:
            return BIT_0_C(cpu);

        case CBCode::BIT_0_D:
            return BIT_0_D(cpu);

        case CBCode::BIT_0_E:
            return BIT_0_E(cpu);

        case CBCode::BIT_0_H:
            return BIT_0_H(cpu);

        case CBCode::BIT_0_L:
            return BIT_0_L(cpu);

        case CBCode::BIT_0_ADDR_HL:
            return BIT_0_ADDR_HL(cpu);

        case CBCode::BIT_0_A:
            return BIT_0_A(cpu);

        case CBCode::BIT_1_B:
            return BIT_1_B(cpu);
        
        case CBCode::BIT_1_C:
            return BIT_1_C(cpu);

        case CBCode::BIT_1_D:
            return BIT_1_D(cpu);

        case CBCode::BIT_1_E:
            return BIT_1_E(cpu);

        case CBCode::BIT_1_H:
            return BIT_1_H(cpu);

        case CBCode::BIT_1_L:
            return BIT_1_L(cpu);

        case CBCode::BIT_1_ADDR_HL:
            return BIT_1_ADDR_HL(cpu);

        case CBCode::BIT_1_A:
            return BIT_1_A(cpu);

        case CBCode::BIT_2_B:
            return BIT_2_B(cpu);
        
        case CBCode::BIT_2_C:
            return BIT_2_C(cpu);

        case CBCode::BIT_2_D:
            return BIT_2_D(cpu);

        case CBCode::BIT_2_E:
            return BIT_2_E(cpu);

        case CBCode::BIT_2_H:
            return BIT_2_H(cpu);

        case CBCode::BIT_2_L:
            return BIT_2_L(cpu);

        case CBCode::BIT_2_ADDR_HL:
            return BIT_2_ADDR_HL(cpu);

        case CBCode::BIT_2_A:
            return BIT_2_A(cpu);

        case CBCode::BIT_3_B:
            return BIT_3_B(cpu);
        
        case CBCode::BIT_3_C:
            return BIT_3_C(cpu);

        case CBCode::BIT_3_D:
            return BIT_3_D(cpu);

        case CBCode::BIT_3_E:
            return BIT_3_E(cpu);

        case CBCode::BIT_3_H:
            return BIT_3_H(cpu);

        case CBCode::BIT_3_L:
            return BIT_3_L(cpu);

        case CBCode::BIT_3_ADDR_HL:
            return BIT_3_ADDR_HL(cpu);

        case CBCode::BIT_3_A:
            return BIT_3_A(cpu);
       
       case CBCode::BIT_4_B:
            return BIT_4_B(cpu);
        
        case CBCode::BIT_4_C:
            return BIT_4_C(cpu);

        case CBCode::BIT_4_D:
            return BIT_4_D(cpu);

        case CBCode::BIT_4_E:
            return BIT_4_E(cpu);

        case CBCode::BIT_4_H:
            return BIT_4_H(cpu);

        case CBCode::BIT_4_L:
            return BIT_4_L(cpu);

        case CBCode::BIT_4_ADDR_HL:
            return BIT_4_ADDR_HL(cpu);

        case CBCode::BIT_4_A:
            return BIT_4_A(cpu);

       case CBCode::BIT_5_B:
            return BIT_5_B(cpu);
        
        case CBCode::BIT_5_C:
            return BIT_5_C(cpu);

        case CBCode::BIT_5_D:
            return BIT_5_D(cpu);

        case CBCode::BIT_5_E:
            return BIT_5_E(cpu);

        case CBCode::BIT_5_H:
            return BIT_5_H(cpu);

        case CBCode::BIT_5_L:
            return BIT_5_L(cpu);

        case CBCode::BIT_5_ADDR_HL:
            return BIT_5_ADDR_HL(cpu);

        case CBCode::BIT_5_A:
            return BIT_5_A(cpu);
        
        case CBCode::BIT_6_B:
            return BIT_6_B(cpu);
        
        case CBCode::BIT_6_C:
            return BIT_6_C(cpu);

        case CBCode::BIT_6_D:
            return BIT_6_D(cpu);

        case CBCode::BIT_6_E:
            return BIT_6_E(cpu);

        case CBCode::BIT_6_H:
            return BIT_6_H(cpu);

        case CBCode::BIT_6_L:
            return BIT_6_L(cpu);

        case CBCode::BIT_6_ADDR_HL:
            return BIT_6_ADDR_HL(cpu);

        case CBCode::BIT_6_A:
            return BIT_6_A(cpu);

        case CBCode::BIT_7_B:
            return BIT_7_B(cpu);
        
        case CBCode::BIT_7_C:
            return BIT_7_C(cpu);

        case CBCode::BIT_7_D:
            return BIT_7_D(cpu);

        case CBCode::BIT_7_E:
            return BIT_7_E(cpu);

        case CBCode::BIT_7_H:
            return BIT_7_H(cpu);

        case CBCode::BIT_7_L:
            return BIT_7_L(cpu);

        case CBCode::BIT_7_ADDR_HL:
            return BIT_7_ADDR_HL(cpu);

        case CBCode::BIT_7_A:
            return BIT_7_A(cpu);
        
        case CBCode::RES_0_B:
            return RES_0_B(cpu);

        case CBCode::RES_0_C:
            return RES_0_C(cpu);

        case CBCode::RES_0_D:
            return RES_0_D(cpu);

        case CBCode::RES_0_E:
            return RES_0_E(cpu);

        case CBCode::RES_0_H:
            return RES_0_H(cpu);

        case CBCode::RES_0_L:
            return RES_0_L(cpu);

        case CBCode::RES_0_ADDR_HL:
            return RES_0_ADDR_HL(cpu);

        case CBCode::RES_0_A:
            return RES_0_A(cpu);
            
        case CBCode::RES_1_B:
            return RES_1_B(cpu);

        case CBCode::RES_1_C:
            return RES_1_C(cpu);

        case CBCode::RES_1_D:
            return RES_1_D(cpu);

        case CBCode::RES_1_E:
            return RES_1_E(cpu);

        case CBCode::RES_1_H:
            return RES_1_H(cpu);

        case CBCode::RES_1_L:
            return RES_1_L(cpu);

        case CBCode::RES_1_ADDR_HL:
            return RES_1_ADDR_HL(cpu);

        case CBCode::RES_1_A:
            return RES_1_A(cpu);
        
        case CBCode::RES_2_B:
            return RES_2_B(cpu);

        case CBCode::RES_2_C:
            return RES_2_C(cpu);

        case CBCode::RES_2_D:
            return RES_2_D(cpu);

        case CBCode::RES_2_E:
            return RES_2_E(cpu);

        case CBCode::RES_2_H:
            return RES_2_H(cpu);

        case CBCode::RES_2_L:
            return RES_2_L(cpu);

        case CBCode::RES_2_ADDR_HL:
            return RES_2_ADDR_HL(cpu);

        case CBCode::RES_2_A:
            return RES_2_A(cpu);

        case CBCode::RES_3_B:
            return RES_3_B(cpu);

        case CBCode::RES_3_C:
            return RES_3_C(cpu);

        case CBCode::RES_3_D:
            return RES_3_D(cpu);

        case CBCode::RES_3_E:
            return RES_3_E(cpu);

        case CBCode::RES_3_H:
            return RES_3_H(cpu);

        case CBCode::RES_3_L:
            return RES_3_L(cpu);

        case CBCode::RES_3_ADDR_HL:
            return RES_3_ADDR_HL(cpu);

        case CBCode::RES_3_A:
            return RES_3_A(cpu);

        case CBCode::RES_4_B:
            return RES_4_B(cpu);

        case CBCode::RES_4_C:
            return RES_4_C(cpu);

        case CBCode::RES_4_D:
            return RES_4_D(cpu);

        case CBCode::RES_4_E:
            return RES_4_E(cpu);

        case CBCode::RES_4_H:
            return RES_4_H(cpu);

        case CBCode::RES_4_L:
            return RES_4_L(cpu);

        case CBCode::RES_4_ADDR_HL:
            return RES_4_ADDR_HL(cpu);

        case CBCode::RES_4_A:
            return RES_4_A(cpu);
        
        case CBCode::RES_5_B:
            return RES_5_B(cpu);

        case CBCode::RES_5_C:
            return RES_5_C(cpu);

        case CBCode::RES_5_D:
            return RES_5_D(cpu);

        case CBCode::RES_5_E:
            return RES_5_E(cpu);

        case CBCode::RES_5_H:
            return RES_5_H(cpu);

        case CBCode::RES_5_L:
            return RES_5_L(cpu);

        case CBCode::RES_5_ADDR_HL:
            return RES_5_ADDR_HL(cpu);

        case CBCode::RES_5_A:
            return RES_5_A(cpu);
        
        case CBCode::RES_6_B:
            return RES_6_B(cpu);

        case CBCode::RES_6_C:
            return RES_6_C(cpu);

        case CBCode::RES_6_D:
            return RES_6_D(cpu);

        case CBCode::RES_6_E:
            return RES_6_E(cpu);

        case CBCode::RES_6_H:
            return RES_6_H(cpu);

        case CBCode::RES_6_L:
            return RES_6_L(cpu);

        case CBCode::RES_6_ADDR_HL:
            return RES_6_ADDR_HL(cpu);

        case CBCode::RES_6_A:
            return RES_6_A(cpu);
        
        case CBCode::RES_7_B:
            return RES_7_B(cpu);

        case CBCode::RES_7_C:
            return RES_7_C(cpu);

        case CBCode::RES_7_D:
            return RES_7_D(cpu);

        case CBCode::RES_7_E:
            return RES_7_E(cpu);

        case CBCode::RES_7_H:
            return RES_7_H(cpu);

        case CBCode::RES_7_L:
            return RES_7_L(cpu);

        case CBCode::RES_7_ADDR_HL:
            return RES_7_ADDR_HL(cpu);

        case CBCode::RES_7_A:
            return RES_7_A(cpu);
        
        case CBCode::SET_0_B:
            return SET_0_B(cpu);

        case CBCode::SET_0_C:
            return SET_0_C(cpu);

        case CBCode::SET_0_D:
            return SET_0_D(cpu);

        case CBCode::SET_0_E:
            return SET_0_E(cpu);

        case CBCode::SET_0_H:
            return SET_0_H(cpu);

        case CBCode::SET_0_L:
            return SET_0_L(cpu);

        case CBCode::SET_0_ADDR_HL:
            return SET_0_ADDR_HL(cpu);

        case CBCode::SET_0_A:
            return SET_0_A(cpu);

        case CBCode::SET_1_B:
            return SET_1_B(cpu);

        case CBCode::SET_1_C:
            return SET_1_C(cpu);

        case CBCode::SET_1_D:
            return SET_1_D(cpu);

        case CBCode::SET_1_E:
            return SET_1_E(cpu);

        case CBCode::SET_1_H:
            return SET_1_H(cpu);

        case CBCode::SET_1_L:
            return SET_1_L(cpu);

        case CBCode::SET_1_ADDR_HL:
            return SET_1_ADDR_HL(cpu);

        case CBCode::SET_1_A:
            return SET_1_A(cpu);
                
        case CBCode::SET_2_B:
            return SET_2_B(cpu);

        case CBCode::SET_2_C:
            return SET_2_C(cpu);

        case CBCode::SET_2_D:
            return SET_2_D(cpu);

        case CBCode::SET_2_E:
            return SET_2_E(cpu);

        case CBCode::SET_2_H:
            return SET_2_H(cpu);

        case CBCode::SET_2_L:
            return SET_2_L(cpu);

        case CBCode::SET_2_ADDR_HL:
            return SET_2_ADDR_HL(cpu);

        case CBCode::SET_2_A:
            return SET_2_A(cpu);

        case CBCode::SET_3_B:
            return SET_3_B(cpu);

        case CBCode::SET_3_C:
            return SET_3_C(cpu);

        case CBCode::SET_3_D:
            return SET_3_D(cpu);

        case CBCode::SET_3_E:
            return SET_3_E(cpu);

        case CBCode::SET_3_H:
            return SET_3_H(cpu);

        case CBCode::SET_3_L:
            return SET_3_L(cpu);

        case CBCode::SET_3_ADDR_HL:
            return SET_3_ADDR_HL(cpu);

        case CBCode::SET_3_A:
            return SET_3_A(cpu);
        
        case CBCode::SET_4_B:
            return SET_4_B(cpu);

        case CBCode::SET_4_C:
            return SET_4_C(cpu);

        case CBCode::SET_4_D:
            return SET_4_D(cpu);

        case CBCode::SET_4_E:
            return SET_4_E(cpu);

        case CBCode::SET_4_H:
            return SET_4_H(cpu);

        case CBCode::SET_4_L:
            return SET_4_L(cpu);

        case CBCode::SET_4_ADDR_HL:
            return SET_4_ADDR_HL(cpu);

        case CBCode::SET_4_A:
            return SET_4_A(cpu);
        
        case CBCode::SET_5_B:
            return SET_5_B(cpu);

        case CBCode::SET_5_C:
            return SET_5_C(cpu);

        case CBCode::SET_5_D:
            return SET_5_D(cpu);

        case CBCode::SET_5_E:
            return SET_5_E(cpu);

        case CBCode::SET_5_H:
            return SET_5_H(cpu);

        case CBCode::SET_5_L:
            return SET_5_L(cpu);

        case CBCode::SET_5_ADDR_HL:
            return SET_5_ADDR_HL(cpu);

        case CBCode::SET_5_A:
            return SET_5_A(cpu);
        
        case CBCode::SET_6_B:
            return SET_6_B(cpu);

        case CBCode::SET_6_C:
            return SET_6_C(cpu);

        case CBCode::SET_6_D:
            return SET_6_D(cpu);

        case CBCode::SET_6_E:
            return SET_6_E(cpu);

        case CBCode::SET_6_H:
            return SET_6_H(cpu);

        case CBCode::SET_6_L:
            return SET_6_L(cpu);

        case CBCode::SET_6_ADDR_HL:
            return SET_6_ADDR_HL(cpu);

        case CBCode::SET_6_A:
            return SET_6_A(cpu);
        
        case CBCode::SET_7_B:
            return SET_7_B(cpu);

        case CBCode::SET_7_C:
            return SET_7_C(cpu);

        case CBCode::SET_7_D:
            return SET_7_D(cpu);

        case CBCode::SET_7_E:
            return SET_7_E(cpu);

        case CBCode::SET_7_H:
            return SET_7_H(cpu);

        case CBCode::SET_7_L:
            return SET_7_L(cpu);

        case CBCode::SET_7_ADDR_HL:
            return SET_7_ADDR_HL(cpu);

        case CBCode::SET_7_A:
            return SET_7_A(cpu);
            
        default:
            throw UnimplementedOperation("Unimplemented CB Code\n");
            break;
     }
 }