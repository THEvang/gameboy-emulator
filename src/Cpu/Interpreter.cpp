#include "Cpu/Interpreter.hpp"

#include "Cpu/Operations.hpp"
#include "Cpu/CBOperations.hpp"

Instruction fetch(Opcode opcode) {
    
    switch (opcode) {
    case Opcode::NOP:
        return NOP();

    case Opcode::LD_BC_D16:
        return LD_BC_D16();

    case Opcode::LD_ADDR_BC_A:
        return LD_ADDR_BC_A();

    case Opcode::INC_BC:
        return INC_BC();

    case Opcode::INC_B:
        return INC_B();

    case Opcode::DEC_B:
        return DEC_B();

    case Opcode::LD_B_D8:
        return LD_B_D8();

    case Opcode::RLCA:
        return RLCA();

    case Opcode::LD_ADDR_A16_SP:
        return LD_ADDR_A16_SP();

    case Opcode::ADD_HL_BC:
        return ADD_HL_BC();

    case Opcode::LD_A_ADDR_BC:
        return LD_A_ADDR_BC();

    case Opcode::DEC_BC:
        return DEC_BC();

    case Opcode::INC_C:
        return INC_C();

    case Opcode::DEC_C:
        return DEC_C();

    case Opcode::LD_C_D8:
        return LD_C_D8();

    case Opcode::RRCA:
        return RRCA();

    case Opcode::STOP:
        return STOP();

    case Opcode::LD_DE_D16:
        return LD_DE_D16();

    case Opcode::LD_ADDR_DE_A:
        return LD_ADDR_DE_A();

    case Opcode::INC_DE:
        return INC_DE();

    case Opcode::INC_D:
        return INC_D();

    case Opcode::DEC_D:
        return DEC_D();

    case Opcode::LD_D_D8:
        return LD_D_D8();

    case Opcode::RLA:
        return RLA();

    case Opcode::JR_R8:
        return JR();

    case Opcode::ADD_HL_DE:
        return ADD_HL_DE();

    case Opcode::LD_A_ADDR_DE:
        return LD_A_ADDR_DE();

    case Opcode::DEC_DE:
        return DEC_DE();

    case Opcode::INC_E:
        return INC_E();

    case Opcode::DEC_E:
        return DEC_E();

    case Opcode::LD_E_D8:
        return LD_E_D8();

    case Opcode::RRA:
        return RRA();

    case Opcode::JR_NZ_R8:
        return JR_NZ();

    case Opcode::LD_HL_D16:
        return LD_HL_D16();

    case Opcode::LD_ADDR_HLI_A:
        return LDI_ADDR_HL_A();

    case Opcode::INC_HL:
        return INC_HL();

    case Opcode::INC_H:
        return INC_H();

    case Opcode::DEC_H:
        return DEC_H();

    case Opcode::LD_H_D8:
        return LD_H_D8();

    case Opcode::DAA:
        return DAA();

    case Opcode::JR_Z_R8:
        return JR_Z();

    case Opcode::ADD_HL_HL:
        return ADD_HL_HL();

    case Opcode::LD_A_ADDR_HLI:
        return LDI_A_ADDR_HL();

    case Opcode::DEC_HL:
        return DEC_HL();

    case Opcode::INC_L:
        return INC_L();

    case Opcode::DEC_L:
        return DEC_L();

    case Opcode::LD_L_D8:
        return LD_L_D8();

    case Opcode::CPL:
        return CPL();

    case Opcode::JR_NC_R8:
        return JR_NC();

    case Opcode::LD_SP_D16:
        return LD_SP_D16();

    case Opcode::LD_ADDR_HLD_A:
        return LD_ADDR_HLD_A();

    case Opcode::INC_SP:
        return INC_SP();

    case Opcode::INC_ADDR_HL:
        return INC_ADDR_HL();

    case Opcode::DEC_ADDR_HL:
        return DEC_ADDR_HL();

    case Opcode::LD_ADDR_HL_D8:
        return LD_ADDR_HL_D8();

    case Opcode::SCF:
        return SCF();

    case Opcode::JR_C_R8:
        return JR_C();

    case Opcode::ADD_HL_SP:
        return ADD_HL_SP();

    case Opcode::LD_A_ADDR_HLD:
        return LD_A_ADDR_HLD();

    case Opcode::DEC_SP:
        return DEC_SP();

    case Opcode::INC_A:
        return INC_A();

    case Opcode::DEC_A:
        return DEC_A();

    case Opcode::LD_A_D8:
        return LD_A_D8();

    case Opcode::CCF:
        return CCF();

    case Opcode::LD_B_B:
        return LD_B_B();

    case Opcode::LD_B_C:
        return LD_B_C();

    case Opcode::LD_B_D:
        return LD_B_D();

    case Opcode::LD_B_E:
        return LD_B_E();

    case Opcode::LD_B_H:
        return LD_B_H();

    case Opcode::LD_B_L:
        return LD_B_L();

    case Opcode::LD_B_ADDR_HL:
        return LD_B_ADDR_HL();

    case Opcode::LD_B_A:
        return LD_B_A();

    case Opcode::LD_C_B:
        return LD_C_B();

    case Opcode::LD_C_C:
        return LD_C_C();

    case Opcode::LD_C_D:
        return LD_C_D();

    case Opcode::LD_C_E:
        return LD_C_E();

    case Opcode::LD_C_H:
        return LD_C_H();

    case Opcode::LD_C_L:
        return LD_C_L();

    case Opcode::LD_C_ADDR_HL:
        return LD_C_ADDR_HL();

    case Opcode::LD_C_A:
        return LD_C_A();

    case Opcode::LD_D_B:
        return LD_D_B();

    case Opcode::LD_D_C:
        return LD_D_C();

    case Opcode::LD_D_D:
        return LD_D_D();

    case Opcode::LD_D_E:
        return LD_D_E();

    case Opcode::LD_D_H:
        return LD_D_H();

    case Opcode::LD_D_L:
        return LD_D_L();

    case Opcode::LD_D_ADDR_HL:
        return LD_D_ADDR_HL();

    case Opcode::LD_D_A:
        return LD_D_A();

    case Opcode::LD_E_B:
        return LD_E_B();

    case Opcode::LD_E_C:
        return LD_E_C();

    case Opcode::LD_E_D:
        return LD_E_D();

    case Opcode::LD_E_E:
        return LD_E_E();

    case Opcode::LD_E_H:
        return LD_E_H();

    case Opcode::LD_E_L:
        return LD_E_L();

    case Opcode::LD_E_ADDR_HL:
        return LD_E_ADDR_HL();

    case Opcode::LD_E_A:
        return LD_E_A();

    case Opcode::LD_H_B:
        return LD_H_B();

    case Opcode::LD_H_C:
        return LD_H_C();

    case Opcode::LD_H_D:
        return LD_H_D();

    case Opcode::LD_H_E:
        return LD_H_E();

    case Opcode::LD_H_H:
        return LD_H_H();

    case Opcode::LD_H_L:
        return LD_H_L();

    case Opcode::LD_H_ADDR_HL:
        return LD_H_ADDR_HL();

    case Opcode::LD_H_A:
        return LD_H_A();

    case Opcode::LD_L_B:
        return LD_L_B();

    case Opcode::LD_L_C:
        return LD_L_C();

    case Opcode::LD_L_D:
        return LD_L_D();

    case Opcode::LD_L_E:
        return LD_L_E();

    case Opcode::LD_L_H:
        return LD_L_H();

    case Opcode::LD_L_L:
        return LD_L_L();

    case Opcode::LD_L_ADDR_HL:
        return LD_L_ADDR_HL();

    case Opcode::LD_L_A:
        return LD_L_A();

    case Opcode::LD_ADDR_HL_B:
        return LD_ADDR_HL_B();

    case Opcode::LD_ADDR_HL_C:
        return LD_ADDR_HL_C();

    case Opcode::LD_ADDR_HL_D:
        return LD_ADDR_HL_D();

    case Opcode::LD_ADDR_HL_E:
        return LD_ADDR_HL_E();

    case Opcode::LD_ADDR_HL_H:
        return LD_ADDR_HL_H();

    case Opcode::LD_ADDR_HL_L:
        return LD_ADDR_HL_L();

    case Opcode::HALT:
        return HALT();

    case Opcode::LD_ADDR_HL_A:
        return LD_ADDR_HL_A();

    case Opcode::LD_A_B:
        return LD_A_B();

    case Opcode::LD_A_C:
        return LD_A_C();

    case Opcode::LD_A_D:
        return LD_A_D();

    case Opcode::LD_A_E:
        return LD_A_E();

    case Opcode::LD_A_H:
        return LD_A_H();

    case Opcode::LD_A_L:
        return LD_A_L();

    case Opcode::LD_A_ADDR_HL:
        return LD_A_ADDR_HL();

    case Opcode::LD_A_A:
        return LD_A_A();

    case Opcode::ADD_A_B:
        return ADD_A_B();

    case Opcode::ADD_A_C:
        return ADD_A_C();

    case Opcode::ADD_A_D:
        return ADD_A_D();

    case Opcode::ADD_A_E:
        return ADD_A_E();

    case Opcode::ADD_A_H:
        return ADD_A_H();

    case Opcode::ADD_A_L:
        return ADD_A_L();

    case Opcode::ADD_A_ADDR_HL:
        return ADD_A_ADDR_HL();

    case Opcode::ADD_A_A:
        return ADD_A_A();

    case Opcode::ADC_A_B:
        return ADC_A_B();

    case Opcode::ADC_A_C:
        return ADC_A_C();

    case Opcode::ADC_A_D:
        return ADC_A_D();

    case Opcode::ADC_A_E:
        return ADC_A_E();

    case Opcode::ADC_A_H:
        return ADC_A_H();

    case Opcode::ADC_A_L:
        return ADC_A_L();

    case Opcode::ADC_A_ADDR_HL:
        return ADC_A_ADDR_HL();

    case Opcode::ADC_A_A:
        return ADC_A_A();

    case Opcode::SUB_B:
        return SUB_B();

    case Opcode::SUB_C:
        return SUB_C();

    case Opcode::SUB_D:
        return SUB_D();

    case Opcode::SUB_E:
        return SUB_E();

    case Opcode::SUB_H:
        return SUB_H();

    case Opcode::SUB_L:
        return SUB_L();

    case Opcode::SUB_ADDR_HL:
        return SUB_ADDR_HL();

    case Opcode::SUB_A:
        return SUB_A();

    case Opcode::SBC_A_B:
        return SBC_A_B();

    case Opcode::SBC_A_C:
        return SBC_A_C();

    case Opcode::SBC_A_D:
        return SBC_A_D();

    case Opcode::SBC_A_E:
        return SBC_A_E();

    case Opcode::SBC_A_H:
        return SBC_A_H();

    case Opcode::SBC_A_L:
        return SBC_A_L();

    case Opcode::SBC_A_ADDR_HL:
        return SBC_A_ADDR_HL();

    case Opcode::SBC_A_A:
        return SBC_A_A();

    case Opcode::AND_B:
        return AND_B();

    case Opcode::AND_C:
        return AND_C();

    case Opcode::AND_D:
        return AND_D();

    case Opcode::AND_E:
        return AND_E();

    case Opcode::AND_H:
        return AND_H();

    case Opcode::AND_L:
        return AND_L();

    case Opcode::AND_ADDR_HL:
        return AND_ADDR_HL();

    case Opcode::AND_A:
        return AND_A();

    case Opcode::XOR_B:
        return XOR_B();

    case Opcode::XOR_C:
        return XOR_C();

    case Opcode::XOR_D:
        return XOR_D();

    case Opcode::XOR_E:
        return XOR_E();

    case Opcode::XOR_H:
        return XOR_H();

    case Opcode::XOR_L:
        return XOR_L();

    case Opcode::XOR_ADDR_HL:
        return XOR_ADDR_HL();

    case Opcode::XOR_A:
        return XOR_A();

    case Opcode::OR_B:
        return OR_B();

    case Opcode::OR_C:
        return OR_C();

    case Opcode::OR_D:
        return OR_D();

    case Opcode::OR_E:
        return OR_E();

    case Opcode::OR_H:
        return OR_H();

    case Opcode::OR_L:
        return OR_L();

    case Opcode::OR_ADDR_HL:
        return OR_ADDR_HL();

    case Opcode::OR_A:
        return OR_A();

    case Opcode::CP_B:
        return CP_B();

    case Opcode::CP_C:
        return CP_C();

    case Opcode::CP_D:
        return CP_D();

    case Opcode::CP_E:
        return CP_E();

    case Opcode::CP_H:
        return CP_H();

    case Opcode::CP_L:
        return CP_L();

    case Opcode::CP_ADDR_HL:
        return CP_ADDR_HL();

    case Opcode::CP_A:
        return CP_A();

    case Opcode::RET_NZ:
        return RET_NZ();

    case Opcode::POP_BC:
        return POP_BC();

    case Opcode::JP_NZ_A16:
        return JUMP_NZ();

    case Opcode::JP_A16:
        return JUMP();

    case Opcode::CALL_NZ_A16:
        return CALL_NZ();

    case Opcode::PUSH_BC:
        return PUSH_BC();

    case Opcode::ADD_A_D8:
        return ADD_A_D8();

    case Opcode::RST_00H:
        return RST(0x00);

    case Opcode::RET_Z:
        return RET_Z();

    case Opcode::RET:
        return RET();

    case Opcode::JP_Z_A16:
        return JUMP_Z();

    case Opcode::PREFIX_CB:
        return PREFIX_CB();

    case Opcode::CALL_Z_A16:
        return CALL_Z();

    case Opcode::CALL_A16:
        return CALL();

    case Opcode::ADC_A_D8:
        return ADC_A_D8();

    case Opcode::RST_08H:
        return RST(0x08);

    case Opcode::RET_NC:
        return RET_NC();

    case Opcode::POP_DE:
        return POP_DE();

    case Opcode::JP_NC_A16:
        return JUMP_NC();

    case Opcode::CALL_NC_A16:
        return CALL_NC();

    case Opcode::PUSH_DE:
        return PUSH_DE();

    case Opcode::SUB_D8:
        return SUB_D8();

    case Opcode::RST_10H:
        return RST(0x10);

    case Opcode::RET_C:
        return RET_C();

    case Opcode::RETI:
        return RETI();

    case Opcode::JP_C_A16:
        return JUMP_C();

    case Opcode::CALL_C_A16:
        return CALL_C();

    case Opcode::SBC_A_D8:
        return SBC_A_D8();

    case Opcode::RST_18H:
        return RST(0x18);

    case Opcode::LDH_ADDR_A8_A:
        return LDH_ADDR_A8_A();

    case Opcode::POP_HL:
        return POP_HL();

    case Opcode::LD_ADDR_C_A:
        return LD_ADDR_C_A();

    case Opcode::PUSH_HL:
        return PUSH_HL();

    case Opcode::AND_D8:
        return AND_D8();

    case Opcode::RST_20H:
        return RST(0x20);

    case Opcode::ADD_SP_R8:
        return ADD_SP_R8();

    case Opcode::JP_ADDR_HL:
        return JUMP_ADDR_HL();

    case Opcode::LD_ADDR_A16_A:
        return LD_ADDR_A16_A();

    case Opcode::XOR_D8:
        return XOR_D8();

    case Opcode::RST_28H:
        return RST(0x28);

    case Opcode::LDH_A_ADDR_A8:
        return LDH_A_ADDR_A8();

    case Opcode::POP_AF:
        return POP_AF();

    case Opcode::LD_A_ADDR_C:
        return LD_A_ADDR_C();

    case Opcode::DI:
        return DI();

    case Opcode::PUSH_AF:
        return PUSH_AF();

    case Opcode::OR_D8:
        return OR_D8();

    case Opcode::RST_30H:
        return RST(0x30);

    case Opcode::LD_HL_SPR8:
        return LD_HL_SPR8();

    case Opcode::LD_SP_HL:
        return LD_SP_HL();

    case Opcode::LD_A_ADDR_A16:
        return LD_A_ADDR_A16();

    case Opcode::EI:
        return EI();

    case Opcode::CP_D8:
        return CP_D8();

    case Opcode::RST_38H:
        return RST(0x38);

    default:
        throw UnimplementedOperation("Invalid Opcode");
        break;
    }
}

Instruction fetch_cb(CBCode opcode)
{
    switch (opcode) {
    case CBCode::RLC_B:
        return RLC_B();

    case CBCode::RLC_C:
        return RLC_C();

    case CBCode::RLC_D:
        return RLC_D();

    case CBCode::RLC_E:
        return RLC_E();

    case CBCode::RLC_H:
        return RLC_H();

    case CBCode::RLC_L:
        return RLC_L();

    case CBCode::RLC_ADDR_HL:
        return RLC_ADDR_HL();

    case CBCode::RLC_A:
        return RLC_A();

    case CBCode::RRC_B:
        return RRC_B();

    case CBCode::RRC_C:
        return RRC_C();

    case CBCode::RRC_D:
        return RRC_D();

    case CBCode::RRC_E:
        return RRC_E();

    case CBCode::RRC_H:
        return RRC_H();

    case CBCode::RRC_L:
        return RRC_L();

    case CBCode::RRC_ADDR_HL:
        return RRC_ADDR_HL();

    case CBCode::RRC_A:
        return RRC_A();

    case CBCode::RL_B:
        return RL_B();

    case CBCode::RL_C:
        return RL_C();

    case CBCode::RL_D:
        return RL_D();

    case CBCode::RL_E:
        return RL_E();

    case CBCode::RL_H:
        return RL_H();

    case CBCode::RL_L:
        return RL_L();

    case CBCode::RL_ADDR_HL:
        return RL_ADDR_HL();

    case CBCode::RL_A:
        return RL_A();

    case CBCode::RR_B:
        return RR_B();

    case CBCode::RR_C:
        return RR_C();

    case CBCode::RR_D:
        return RR_D();

    case CBCode::RR_E:
        return RR_E();

    case CBCode::RR_H:
        return RR_H();

    case CBCode::RR_L:
        return RR_L();

    case CBCode::RR_ADDR_HL:
        return RR_ADDR_HL();

    case CBCode::RR_A:
        return RR_A();

    case CBCode::SLA_B:
        return SLA_B();

    case CBCode::SLA_C:
        return SLA_C();

    case CBCode::SLA_D:
        return SLA_D();

    case CBCode::SLA_E:
        return SLA_E();

    case CBCode::SLA_H:
        return SLA_H();

    case CBCode::SLA_L:
        return SLA_L();

    case CBCode::SLA_ADDR_HL:
        return SLA_ADDR_HL();

    case CBCode::SLA_A:
        return SLA_A();

    case CBCode::SRA_B:
        return SRA_B();

    case CBCode::SRA_C:
        return SRA_C();

    case CBCode::SRA_D:
        return SRA_D();

    case CBCode::SRA_E:
        return SRA_E();

    case CBCode::SRA_H:
        return SRA_H();

    case CBCode::SRA_L:
        return SRA_L();

    case CBCode::SRA_ADDR_HL:
        return SRA_ADDR_HL();

    case CBCode::SRA_A:
        return SRA_A();

    case CBCode::SWAP_B:
        return SWAP_B();

    case CBCode::SWAP_C:
        return SWAP_C();

    case CBCode::SWAP_D:
        return SWAP_D();

    case CBCode::SWAP_E:
        return SWAP_E();

    case CBCode::SWAP_H:
        return SWAP_H();

    case CBCode::SWAP_L:
        return SWAP_L();

    case CBCode::SWAP_ADDR_HL:
        return SWAP_ADDR_HL();

    case CBCode::SWAP_A:
        return SWAP_A();

    case CBCode::SRL_B:
        return SRL_B();

    case CBCode::SRL_C:
        return SRL_C();

    case CBCode::SRL_D:
        return SRL_D();

    case CBCode::SRL_E:
        return SRL_E();

    case CBCode::SRL_H:
        return SRL_H();

    case CBCode::SRL_L:
        return SRL_L();

    case CBCode::SRL_ADDR_HL:
        return SRL_ADDR_HL();

    case CBCode::SRL_A:
        return SRL_A();

    case CBCode::BIT_0_B:
        return BIT_0_B();

    case CBCode::BIT_0_C:
        return BIT_0_C();

    case CBCode::BIT_0_D:
        return BIT_0_D();

    case CBCode::BIT_0_E:
        return BIT_0_E();

    case CBCode::BIT_0_H:
        return BIT_0_H();

    case CBCode::BIT_0_L:
        return BIT_0_L();

    case CBCode::BIT_0_ADDR_HL:
        return BIT_0_ADDR_HL();

    case CBCode::BIT_0_A:
        return BIT_0_A();

    case CBCode::BIT_1_B:
        return BIT_1_B();

    case CBCode::BIT_1_C:
        return BIT_1_C();

    case CBCode::BIT_1_D:
        return BIT_1_D();

    case CBCode::BIT_1_E:
        return BIT_1_E();

    case CBCode::BIT_1_H:
        return BIT_1_H();

    case CBCode::BIT_1_L:
        return BIT_1_L();

    case CBCode::BIT_1_ADDR_HL:
        return BIT_1_ADDR_HL();

    case CBCode::BIT_1_A:
        return BIT_1_A();

    case CBCode::BIT_2_B:
        return BIT_2_B();

    case CBCode::BIT_2_C:
        return BIT_2_C();

    case CBCode::BIT_2_D:
        return BIT_2_D();

    case CBCode::BIT_2_E:
        return BIT_2_E();

    case CBCode::BIT_2_H:
        return BIT_2_H();

    case CBCode::BIT_2_L:
        return BIT_2_L();

    case CBCode::BIT_2_ADDR_HL:
        return BIT_2_ADDR_HL();

    case CBCode::BIT_2_A:
        return BIT_2_A();

    case CBCode::BIT_3_B:
        return BIT_3_B();

    case CBCode::BIT_3_C:
        return BIT_3_C();

    case CBCode::BIT_3_D:
        return BIT_3_D();

    case CBCode::BIT_3_E:
        return BIT_3_E();

    case CBCode::BIT_3_H:
        return BIT_3_H();

    case CBCode::BIT_3_L:
        return BIT_3_L();

    case CBCode::BIT_3_ADDR_HL:
        return BIT_3_ADDR_HL();

    case CBCode::BIT_3_A:
        return BIT_3_A();

    case CBCode::BIT_4_B:
        return BIT_4_B();

    case CBCode::BIT_4_C:
        return BIT_4_C();

    case CBCode::BIT_4_D:
        return BIT_4_D();

    case CBCode::BIT_4_E:
        return BIT_4_E();

    case CBCode::BIT_4_H:
        return BIT_4_H();

    case CBCode::BIT_4_L:
        return BIT_4_L();

    case CBCode::BIT_4_ADDR_HL:
        return BIT_4_ADDR_HL();

    case CBCode::BIT_4_A:
        return BIT_4_A();

    case CBCode::BIT_5_B:
        return BIT_5_B();

    case CBCode::BIT_5_C:
        return BIT_5_C();

    case CBCode::BIT_5_D:
        return BIT_5_D();

    case CBCode::BIT_5_E:
        return BIT_5_E();

    case CBCode::BIT_5_H:
        return BIT_5_H();

    case CBCode::BIT_5_L:
        return BIT_5_L();

    case CBCode::BIT_5_ADDR_HL:
        return BIT_5_ADDR_HL();

    case CBCode::BIT_5_A:
        return BIT_5_A();

    case CBCode::BIT_6_B:
        return BIT_6_B();

    case CBCode::BIT_6_C:
        return BIT_6_C();

    case CBCode::BIT_6_D:
        return BIT_6_D();

    case CBCode::BIT_6_E:
        return BIT_6_E();

    case CBCode::BIT_6_H:
        return BIT_6_H();

    case CBCode::BIT_6_L:
        return BIT_6_L();

    case CBCode::BIT_6_ADDR_HL:
        return BIT_6_ADDR_HL();

    case CBCode::BIT_6_A:
        return BIT_6_A();

    case CBCode::BIT_7_B:
        return BIT_7_B();

    case CBCode::BIT_7_C:
        return BIT_7_C();

    case CBCode::BIT_7_D:
        return BIT_7_D();

    case CBCode::BIT_7_E:
        return BIT_7_E();

    case CBCode::BIT_7_H:
        return BIT_7_H();

    case CBCode::BIT_7_L:
        return BIT_7_L();

    case CBCode::BIT_7_ADDR_HL:
        return BIT_7_ADDR_HL();

    case CBCode::BIT_7_A:
        return BIT_7_A();

    case CBCode::RES_0_B:
        return RES_0_B();

    case CBCode::RES_0_C:
        return RES_0_C();

    case CBCode::RES_0_D:
        return RES_0_D();

    case CBCode::RES_0_E:
        return RES_0_E();

    case CBCode::RES_0_H:
        return RES_0_H();

    case CBCode::RES_0_L:
        return RES_0_L();

    case CBCode::RES_0_ADDR_HL:
        return RES_0_ADDR_HL();

    case CBCode::RES_0_A:
        return RES_0_A();

    case CBCode::RES_1_B:
        return RES_1_B();

    case CBCode::RES_1_C:
        return RES_1_C();

    case CBCode::RES_1_D:
        return RES_1_D();

    case CBCode::RES_1_E:
        return RES_1_E();

    case CBCode::RES_1_H:
        return RES_1_H();

    case CBCode::RES_1_L:
        return RES_1_L();

    case CBCode::RES_1_ADDR_HL:
        return RES_1_ADDR_HL();

    case CBCode::RES_1_A:
        return RES_1_A();

    case CBCode::RES_2_B:
        return RES_2_B();

    case CBCode::RES_2_C:
        return RES_2_C();

    case CBCode::RES_2_D:
        return RES_2_D();

    case CBCode::RES_2_E:
        return RES_2_E();

    case CBCode::RES_2_H:
        return RES_2_H();

    case CBCode::RES_2_L:
        return RES_2_L();

    case CBCode::RES_2_ADDR_HL:
        return RES_2_ADDR_HL();

    case CBCode::RES_2_A:
        return RES_2_A();

    case CBCode::RES_3_B:
        return RES_3_B();

    case CBCode::RES_3_C:
        return RES_3_C();

    case CBCode::RES_3_D:
        return RES_3_D();

    case CBCode::RES_3_E:
        return RES_3_E();

    case CBCode::RES_3_H:
        return RES_3_H();

    case CBCode::RES_3_L:
        return RES_3_L();

    case CBCode::RES_3_ADDR_HL:
        return RES_3_ADDR_HL();

    case CBCode::RES_3_A:
        return RES_3_A();

    case CBCode::RES_4_B:
        return RES_4_B();

    case CBCode::RES_4_C:
        return RES_4_C();

    case CBCode::RES_4_D:
        return RES_4_D();

    case CBCode::RES_4_E:
        return RES_4_E();

    case CBCode::RES_4_H:
        return RES_4_H();

    case CBCode::RES_4_L:
        return RES_4_L();

    case CBCode::RES_4_ADDR_HL:
        return RES_4_ADDR_HL();

    case CBCode::RES_4_A:
        return RES_4_A();

    case CBCode::RES_5_B:
        return RES_5_B();

    case CBCode::RES_5_C:
        return RES_5_C();

    case CBCode::RES_5_D:
        return RES_5_D();

    case CBCode::RES_5_E:
        return RES_5_E();

    case CBCode::RES_5_H:
        return RES_5_H();

    case CBCode::RES_5_L:
        return RES_5_L();

    case CBCode::RES_5_ADDR_HL:
        return RES_5_ADDR_HL();

    case CBCode::RES_5_A:
        return RES_5_A();

    case CBCode::RES_6_B:
        return RES_6_B();

    case CBCode::RES_6_C:
        return RES_6_C();

    case CBCode::RES_6_D:
        return RES_6_D();

    case CBCode::RES_6_E:
        return RES_6_E();

    case CBCode::RES_6_H:
        return RES_6_H();

    case CBCode::RES_6_L:
        return RES_6_L();

    case CBCode::RES_6_ADDR_HL:
        return RES_6_ADDR_HL();

    case CBCode::RES_6_A:
        return RES_6_A();

    case CBCode::RES_7_B:
        return RES_7_B();

    case CBCode::RES_7_C:
        return RES_7_C();

    case CBCode::RES_7_D:
        return RES_7_D();

    case CBCode::RES_7_E:
        return RES_7_E();

    case CBCode::RES_7_H:
        return RES_7_H();

    case CBCode::RES_7_L:
        return RES_7_L();

    case CBCode::RES_7_ADDR_HL:
        return RES_7_ADDR_HL();

    case CBCode::RES_7_A:
        return RES_7_A();

    case CBCode::SET_0_B:
        return SET_0_B();

    case CBCode::SET_0_C:
        return SET_0_C();

    case CBCode::SET_0_D:
        return SET_0_D();

    case CBCode::SET_0_E:
        return SET_0_E();

    case CBCode::SET_0_H:
        return SET_0_H();

    case CBCode::SET_0_L:
        return SET_0_L();

    case CBCode::SET_0_ADDR_HL:
        return SET_0_ADDR_HL();

    case CBCode::SET_0_A:
        return SET_0_A();

    case CBCode::SET_1_B:
        return SET_1_B();

    case CBCode::SET_1_C:
        return SET_1_C();

    case CBCode::SET_1_D:
        return SET_1_D();

    case CBCode::SET_1_E:
        return SET_1_E();

    case CBCode::SET_1_H:
        return SET_1_H();

    case CBCode::SET_1_L:
        return SET_1_L();

    case CBCode::SET_1_ADDR_HL:
        return SET_1_ADDR_HL();

    case CBCode::SET_1_A:
        return SET_1_A();

    case CBCode::SET_2_B:
        return SET_2_B();

    case CBCode::SET_2_C:
        return SET_2_C();

    case CBCode::SET_2_D:
        return SET_2_D();

    case CBCode::SET_2_E:
        return SET_2_E();

    case CBCode::SET_2_H:
        return SET_2_H();

    case CBCode::SET_2_L:
        return SET_2_L();

    case CBCode::SET_2_ADDR_HL:
        return SET_2_ADDR_HL();

    case CBCode::SET_2_A:
        return SET_2_A();

    case CBCode::SET_3_B:
        return SET_3_B();

    case CBCode::SET_3_C:
        return SET_3_C();

    case CBCode::SET_3_D:
        return SET_3_D();

    case CBCode::SET_3_E:
        return SET_3_E();

    case CBCode::SET_3_H:
        return SET_3_H();

    case CBCode::SET_3_L:
        return SET_3_L();

    case CBCode::SET_3_ADDR_HL:
        return SET_3_ADDR_HL();

    case CBCode::SET_3_A:
        return SET_3_A();

    case CBCode::SET_4_B:
        return SET_4_B();

    case CBCode::SET_4_C:
        return SET_4_C();

    case CBCode::SET_4_D:
        return SET_4_D();

    case CBCode::SET_4_E:
        return SET_4_E();

    case CBCode::SET_4_H:
        return SET_4_H();

    case CBCode::SET_4_L:
        return SET_4_L();

    case CBCode::SET_4_ADDR_HL:
        return SET_4_ADDR_HL();

    case CBCode::SET_4_A:
        return SET_4_A();

    case CBCode::SET_5_B:
        return SET_5_B();

    case CBCode::SET_5_C:
        return SET_5_C();

    case CBCode::SET_5_D:
        return SET_5_D();

    case CBCode::SET_5_E:
        return SET_5_E();

    case CBCode::SET_5_H:
        return SET_5_H();

    case CBCode::SET_5_L:
        return SET_5_L();

    case CBCode::SET_5_ADDR_HL:
        return SET_5_ADDR_HL();

    case CBCode::SET_5_A:
        return SET_5_A();

    case CBCode::SET_6_B:
        return SET_6_B();

    case CBCode::SET_6_C:
        return SET_6_C();

    case CBCode::SET_6_D:
        return SET_6_D();

    case CBCode::SET_6_E:
        return SET_6_E();

    case CBCode::SET_6_H:
        return SET_6_H();

    case CBCode::SET_6_L:
        return SET_6_L();

    case CBCode::SET_6_ADDR_HL:
        return SET_6_ADDR_HL();

    case CBCode::SET_6_A:
        return SET_6_A();

    case CBCode::SET_7_B:
        return SET_7_B();

    case CBCode::SET_7_C:
        return SET_7_C();

    case CBCode::SET_7_D:
        return SET_7_D();

    case CBCode::SET_7_E:
        return SET_7_E();

    case CBCode::SET_7_H:
        return SET_7_H();

    case CBCode::SET_7_L:
        return SET_7_L();

    case CBCode::SET_7_ADDR_HL:
        return SET_7_ADDR_HL();

    case CBCode::SET_7_A:
        return SET_7_A();

    default:
        throw UnimplementedOperation("Unimplemented CB Code\n");
        break;
    }
}