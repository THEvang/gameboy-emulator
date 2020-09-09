#include "Cpu/Interpreter.hpp"

#include "Cpu/Operations.hpp"
#include "Cpu/CBOperations.hpp"

Instruction fetch(Opcode opcode) {
    
    switch (opcode) {
    case Opcode::NOP:
        return NOP();

    case Opcode::LD_BC_D16:
        return LD_RR_D16({Cpu::Register::B, Cpu::Register::C});

    case Opcode::LD_ADDR_BC_A:
        return LD_ADDR_RR_A({Cpu::Register::B, Cpu::Register::C});

    case Opcode::INC_BC:
        return INC_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::INC_B:
        return INC_R(Cpu::Register::B);

    case Opcode::DEC_B:
        return DEC_R(Cpu::Register::B);

    case Opcode::LD_B_D8:
        return LD_R_D8(Cpu::Register::B);

    case Opcode::RLCA:
        return RLCA();

    case Opcode::LD_ADDR_A16_SP:
        return LD_ADDR_A16_SP();

    case Opcode::ADD_HL_BC:
        return ADD_HL_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::LD_A_ADDR_BC:
        return LD_A_ADDR_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::DEC_BC:
        return DEC_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::INC_C:
        return INC_R(Cpu::Register::C);

    case Opcode::DEC_C:
        return DEC_R(Cpu::Register::C);

    case Opcode::LD_C_D8:
        return LD_R_D8(Cpu::Register::C);

    case Opcode::RRCA:
        return RRCA();

    case Opcode::STOP:
        return STOP();

    case Opcode::LD_DE_D16:
        return LD_RR_D16({Cpu::Register::D, Cpu::Register::E});

    case Opcode::LD_ADDR_DE_A:
        return LD_ADDR_RR_A({Cpu::Register::D, Cpu::Register::E});

    case Opcode::INC_DE:
        return INC_RR({Cpu::Register::D, Cpu::Register::E});

    case Opcode::INC_D:
        return INC_R(Cpu::Register::D);

    case Opcode::DEC_D:
        return DEC_R(Cpu::Register::D);

    case Opcode::LD_D_D8:
        return LD_R_D8(Cpu::Register::D);

    case Opcode::RLA:
        return RLA();

    case Opcode::JR_R8:
        return JR();

    case Opcode::ADD_HL_DE:
        return ADD_HL_RR({Cpu::Register::D, Cpu::Register::E});

    case Opcode::LD_A_ADDR_DE:
        return LD_A_ADDR_RR({Cpu::Register::D, Cpu::Register::E});

    case Opcode::DEC_DE:
        return DEC_RR({Cpu::Register::D, Cpu::Register::E});

    case Opcode::INC_E:
        return INC_R(Cpu::Register::E);

    case Opcode::DEC_E:
        return DEC_R(Cpu::Register::E);

    case Opcode::LD_E_D8:
        return LD_R_D8(Cpu::Register::E);

    case Opcode::RRA:
        return RRA();

    case Opcode::JR_NZ_R8:
        return JR_NZ();

    case Opcode::LD_HL_D16:
        return LD_RR_D16({Cpu::Register::H, Cpu::Register::L});

    case Opcode::LD_ADDR_HLI_A:
        return LDI_ADDR_HL_A();

    case Opcode::INC_HL:
        return INC_RR({Cpu::Register::H, Cpu::Register::L});

    case Opcode::INC_H:
        return INC_R(Cpu::Register::H);

    case Opcode::DEC_H:
        return DEC_R(Cpu::Register::H);

    case Opcode::LD_H_D8:
        return LD_R_D8(Cpu::Register::H);

    case Opcode::DAA:
        return DAA();

    case Opcode::JR_Z_R8:
        return JR_Z();

    case Opcode::ADD_HL_HL:
        return ADD_HL_RR({Cpu::Register::H, Cpu::Register::L});

    case Opcode::LD_A_ADDR_HLI:
        return LDI_A_ADDR_HL();

    case Opcode::DEC_HL:
        return DEC_RR({Cpu::Register::H, Cpu::Register::L});

    case Opcode::INC_L:
        return INC_R(Cpu::Register::L);

    case Opcode::DEC_L:
        return DEC_R(Cpu::Register::L);

    case Opcode::LD_L_D8:
        return LD_R_D8(Cpu::Register::L);

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
        return INC_R(Cpu::Register::A);

    case Opcode::DEC_A:
        return DEC_R(Cpu::Register::A);

    case Opcode::LD_A_D8:
        return LD_R_D8(Cpu::Register::A);

    case Opcode::CCF:
        return CCF();

    case Opcode::LD_B_B:
        return LD_R_R(Cpu::Register::B, Cpu::Register::B);

    case Opcode::LD_B_C:
        return LD_R_R(Cpu::Register::B, Cpu::Register::C);

    case Opcode::LD_B_D:
        return LD_R_R(Cpu::Register::B, Cpu::Register::D);

    case Opcode::LD_B_E:
        return LD_R_R(Cpu::Register::B, Cpu::Register::E);

    case Opcode::LD_B_H:
        return LD_R_R(Cpu::Register::B, Cpu::Register::H);

    case Opcode::LD_B_L:
        return LD_R_R(Cpu::Register::B, Cpu::Register::L);

    case Opcode::LD_B_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::B);

    case Opcode::LD_B_A:
        return LD_R_R(Cpu::Register::B, Cpu::Register::A);

    case Opcode::LD_C_B:
        return LD_R_R(Cpu::Register::C, Cpu::Register::B);

    case Opcode::LD_C_C:
        return LD_R_R(Cpu::Register::C, Cpu::Register::C);

    case Opcode::LD_C_D:
        return LD_R_R(Cpu::Register::C, Cpu::Register::D);

    case Opcode::LD_C_E:
        return LD_R_R(Cpu::Register::C, Cpu::Register::E);

    case Opcode::LD_C_H:
        return LD_R_R(Cpu::Register::C, Cpu::Register::H);

    case Opcode::LD_C_L:
        return LD_R_R(Cpu::Register::C, Cpu::Register::L);

    case Opcode::LD_C_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::C);

    case Opcode::LD_C_A:
        return LD_R_R(Cpu::Register::C, Cpu::Register::A);

    case Opcode::LD_D_B:
        return LD_R_R(Cpu::Register::D, Cpu::Register::B);

    case Opcode::LD_D_C:
        return LD_R_R(Cpu::Register::D, Cpu::Register::C);

    case Opcode::LD_D_D:
        return LD_R_R(Cpu::Register::D, Cpu::Register::D);

    case Opcode::LD_D_E:
        return LD_R_R(Cpu::Register::D, Cpu::Register::E);

    case Opcode::LD_D_H:
        return LD_R_R(Cpu::Register::D, Cpu::Register::H);

    case Opcode::LD_D_L:
        return LD_R_R(Cpu::Register::D, Cpu::Register::L);

    case Opcode::LD_D_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::D);

    case Opcode::LD_D_A:
        return LD_R_R(Cpu::Register::D, Cpu::Register::A);

    case Opcode::LD_E_B:
        return LD_R_R(Cpu::Register::E, Cpu::Register::B);

    case Opcode::LD_E_C:
        return LD_R_R(Cpu::Register::E, Cpu::Register::C);

    case Opcode::LD_E_D:
        return LD_R_R(Cpu::Register::E, Cpu::Register::D);

    case Opcode::LD_E_E:
        return LD_R_R(Cpu::Register::E, Cpu::Register::E);

    case Opcode::LD_E_H:
        return LD_R_R(Cpu::Register::E, Cpu::Register::H);

    case Opcode::LD_E_L:
        return LD_R_R(Cpu::Register::E, Cpu::Register::L);

    case Opcode::LD_E_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::E);

    case Opcode::LD_E_A:
        return LD_R_R(Cpu::Register::E, Cpu::Register::A);

    case Opcode::LD_H_B:
        return LD_R_R(Cpu::Register::H, Cpu::Register::B);

    case Opcode::LD_H_C:
        return LD_R_R(Cpu::Register::H, Cpu::Register::C);

    case Opcode::LD_H_D:
        return LD_R_R(Cpu::Register::H, Cpu::Register::D);

    case Opcode::LD_H_E:
        return LD_R_R(Cpu::Register::H, Cpu::Register::E);

    case Opcode::LD_H_H:
        return LD_R_R(Cpu::Register::H, Cpu::Register::H);

    case Opcode::LD_H_L:
        return LD_R_R(Cpu::Register::H, Cpu::Register::L);

    case Opcode::LD_H_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::H);

    case Opcode::LD_H_A:
        return LD_R_R(Cpu::Register::H, Cpu::Register::A);

    case Opcode::LD_L_B:
        return LD_R_R(Cpu::Register::L, Cpu::Register::B);

    case Opcode::LD_L_C:
        return LD_R_R(Cpu::Register::L, Cpu::Register::C);

    case Opcode::LD_L_D:
        return LD_R_R(Cpu::Register::L, Cpu::Register::D);

    case Opcode::LD_L_E:
        return LD_R_R(Cpu::Register::L, Cpu::Register::E);

    case Opcode::LD_L_H:
        return LD_R_R(Cpu::Register::L, Cpu::Register::H);

    case Opcode::LD_L_L:
        return LD_R_R(Cpu::Register::L, Cpu::Register::L);

    case Opcode::LD_L_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::L);

    case Opcode::LD_L_A:
        return LD_R_R(Cpu::Register::L, Cpu::Register::A);

    case Opcode::LD_ADDR_HL_B:
        return LD_ADDR_HL_R(Cpu::Register::B);

    case Opcode::LD_ADDR_HL_C:
        return LD_ADDR_HL_R(Cpu::Register::C);

    case Opcode::LD_ADDR_HL_D:
        return LD_ADDR_HL_R(Cpu::Register::D);

    case Opcode::LD_ADDR_HL_E:
        return LD_ADDR_HL_R(Cpu::Register::E);

    case Opcode::LD_ADDR_HL_H:
        return LD_ADDR_HL_R(Cpu::Register::H);

    case Opcode::LD_ADDR_HL_L:
        return LD_ADDR_HL_R(Cpu::Register::L);

    case Opcode::HALT:
        return HALT();

    case Opcode::LD_ADDR_HL_A:
        return LD_ADDR_HL_R(Cpu::Register::A);

    case Opcode::LD_A_B:
        return LD_R_R(Cpu::Register::A, Cpu::Register::B);

    case Opcode::LD_A_C:
        return LD_R_R(Cpu::Register::A, Cpu::Register::C);

    case Opcode::LD_A_D:
        return LD_R_R(Cpu::Register::A, Cpu::Register::D);

    case Opcode::LD_A_E:
        return LD_R_R(Cpu::Register::A, Cpu::Register::E);

    case Opcode::LD_A_H:
        return LD_R_R(Cpu::Register::A, Cpu::Register::H);

    case Opcode::LD_A_L:
        return LD_R_R(Cpu::Register::A, Cpu::Register::L);

    case Opcode::LD_A_ADDR_HL:
        return LD_R_ADDR_HL(Cpu::Register::A);

    case Opcode::LD_A_A:
        return LD_R_R(Cpu::Register::A, Cpu::Register::A);

    case Opcode::ADD_A_B:
        return ADD_R(Cpu::Register::B);

    case Opcode::ADD_A_C:
        return ADD_R(Cpu::Register::C);

    case Opcode::ADD_A_D:
        return ADD_R(Cpu::Register::D);

    case Opcode::ADD_A_E:
        return ADD_R(Cpu::Register::E);

    case Opcode::ADD_A_H:
        return ADD_R(Cpu::Register::H);

    case Opcode::ADD_A_L:
        return ADD_R(Cpu::Register::L);

    case Opcode::ADD_A_ADDR_HL:
        return ADD_ADDR_HL();

    case Opcode::ADD_A_A:
        return ADD_R(Cpu::Register::A);

    case Opcode::ADC_A_B:
        return ADC_R(Cpu::Register::B);

    case Opcode::ADC_A_C:
        return ADC_R(Cpu::Register::C);

    case Opcode::ADC_A_D:
        return ADC_R(Cpu::Register::D);

    case Opcode::ADC_A_E:
        return ADC_R(Cpu::Register::E);

    case Opcode::ADC_A_H:
        return ADC_R(Cpu::Register::H);

    case Opcode::ADC_A_L:
        return ADC_R(Cpu::Register::L);

    case Opcode::ADC_A_ADDR_HL:
        return ADC_ADDR_HL();

    case Opcode::ADC_A_A:
        return ADC_R(Cpu::Register::A);

    case Opcode::SUB_B:
        return SUB_R(Cpu::Register::B);

    case Opcode::SUB_C:
        return SUB_R(Cpu::Register::C);

    case Opcode::SUB_D:
        return SUB_R(Cpu::Register::D);

    case Opcode::SUB_E:
        return SUB_R(Cpu::Register::E);

    case Opcode::SUB_H:
        return SUB_R(Cpu::Register::H);

    case Opcode::SUB_L:
        return SUB_R(Cpu::Register::L);

    case Opcode::SUB_ADDR_HL:
        return SUB_ADDR_HL();

    case Opcode::SUB_A:
        return SUB_R(Cpu::Register::A);

    case Opcode::SBC_A_B:
        return SBC_R(Cpu::Register::B);

    case Opcode::SBC_A_C:
        return SBC_R(Cpu::Register::C);

    case Opcode::SBC_A_D:
        return SBC_R(Cpu::Register::D);

    case Opcode::SBC_A_E:
        return SBC_R(Cpu::Register::E);

    case Opcode::SBC_A_H:
        return SBC_R(Cpu::Register::H);

    case Opcode::SBC_A_L:
        return SBC_R(Cpu::Register::L);

    case Opcode::SBC_A_ADDR_HL:
        return SBC_A_ADDR_HL();

    case Opcode::SBC_A_A:
        return SBC_R(Cpu::Register::A);

    case Opcode::AND_B:
        return AND_R(Cpu::Register::B);

    case Opcode::AND_C:
        return AND_R(Cpu::Register::C);

    case Opcode::AND_D:
        return AND_R(Cpu::Register::D);

    case Opcode::AND_E:
        return AND_R(Cpu::Register::E);

    case Opcode::AND_H:
        return AND_R(Cpu::Register::H);

    case Opcode::AND_L:
        return AND_R(Cpu::Register::L);

    case Opcode::AND_ADDR_HL:
        return AND_ADDR_HL();

    case Opcode::AND_A:
        return AND_R(Cpu::Register::A);

    case Opcode::XOR_B:
        return XOR_R(Cpu::Register::B);

    case Opcode::XOR_C:
        return XOR_R(Cpu::Register::C);

    case Opcode::XOR_D:
        return XOR_R(Cpu::Register::D);

    case Opcode::XOR_E:
        return XOR_R(Cpu::Register::E);

    case Opcode::XOR_H:
        return XOR_R(Cpu::Register::H);

    case Opcode::XOR_L:
        return XOR_R(Cpu::Register::L);

    case Opcode::XOR_ADDR_HL:
        return XOR_ADDR_HL();

    case Opcode::XOR_A:
        return XOR_R(Cpu::Register::A);

    case Opcode::OR_B:
        return OR_R(Cpu::Register::B);

    case Opcode::OR_C:
        return OR_R(Cpu::Register::C);

    case Opcode::OR_D:
        return OR_R(Cpu::Register::D);

    case Opcode::OR_E:
        return OR_R(Cpu::Register::E);

    case Opcode::OR_H:
        return OR_R(Cpu::Register::H);

    case Opcode::OR_L:
        return OR_R(Cpu::Register::L);

    case Opcode::OR_ADDR_HL:
        return OR_ADDR_HL();

    case Opcode::OR_A:
        return OR_R(Cpu::Register::A);

    case Opcode::CP_B:
        return CP_R(Cpu::Register::B);

    case Opcode::CP_C:
        return CP_R(Cpu::Register::C);

    case Opcode::CP_D:
        return CP_R(Cpu::Register::D);

    case Opcode::CP_E:
        return CP_R(Cpu::Register::E);

    case Opcode::CP_H:
        return CP_R(Cpu::Register::H);

    case Opcode::CP_L:
        return CP_R(Cpu::Register::L);

    case Opcode::CP_ADDR_HL:
        return CP_ADDR_HL();

    case Opcode::CP_A:
        return CP_R(Cpu::Register::A);

    case Opcode::RET_NZ:
        return RET_NZ();

    case Opcode::POP_BC:
        return POP_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::JP_NZ_A16:
        return JUMP_NZ();

    case Opcode::JP_A16:
        return JUMP();

    case Opcode::CALL_NZ_A16:
        return CALL_NZ();

    case Opcode::PUSH_BC:
        return PUSH_RR({Cpu::Register::B, Cpu::Register::C});

    case Opcode::ADD_A_D8:
        return ADD_D8();

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
        return ADC_D8();

    case Opcode::RST_08H:
        return RST(0x08);

    case Opcode::RET_NC:
        return RET_NC();

    case Opcode::POP_DE:
        return POP_RR({Cpu::Register::D, Cpu::Register::E});

    case Opcode::JP_NC_A16:
        return JUMP_NC();

    case Opcode::CALL_NC_A16:
        return CALL_NC();

    case Opcode::PUSH_DE:
        return PUSH_RR({Cpu::Register::D, Cpu::Register::E});

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
        return SBC_D8();

    case Opcode::RST_18H:
        return RST(0x18);

    case Opcode::LDH_ADDR_A8_A:
        return LDH_ADDR_A8_A();

    case Opcode::POP_HL:
        return POP_RR({Cpu::Register::H, Cpu::Register::L});

    case Opcode::LD_ADDR_C_A:
        return LD_ADDR_C_A();

    case Opcode::PUSH_HL:
        return PUSH_RR({Cpu::Register::H, Cpu::Register::L});

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
        return PUSH_RR({Cpu::Register::A, Cpu::Register::F});

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

Cpu::Register get_cb_register(CBCode opcode) {
    auto lower = static_cast<uint8_t>(opcode) & 0x0F;

    switch(lower) {
        case 0x00:
        case 0x08:
            return Cpu::Register::B;
        case 0x01:
        case 0x09:
            return Cpu::Register::C;
        case 0x02:
        case 0x0A:
            return Cpu::Register::D;
        case 0x03:
        case 0x0B:
            return Cpu::Register::E;
        case 0x04:
        case 0x0C:
            return Cpu::Register::H;
        case 0x05:
        case 0x0D:
            return Cpu::Register::L;
        case 0x07:
        case 0x0E:
        default:
            return Cpu::Register::A;
    }
}

Instruction fetch_cb(CBCode opcode)
{
    const auto reg = get_cb_register(opcode);
    switch (opcode) {
    case CBCode::RLC_B:
    case CBCode::RLC_C:
    case CBCode::RLC_D:
    case CBCode::RLC_E:
    case CBCode::RLC_H:
    case CBCode::RLC_L:
    case CBCode::RLC_A:
        return RLC_R(reg);

    case CBCode::RLC_ADDR_HL:
        return RLC_ADDR_HL();

    case CBCode::RRC_B:
    case CBCode::RRC_C:
    case CBCode::RRC_D:
    case CBCode::RRC_E:
    case CBCode::RRC_H:
    case CBCode::RRC_L:
    case CBCode::RRC_A:
        return RRC_R(reg);

    case CBCode::RRC_ADDR_HL:
        return RRC_ADDR_HL();

    case CBCode::RL_B:
    case CBCode::RL_C:
    case CBCode::RL_D:
    case CBCode::RL_E:
    case CBCode::RL_H:
    case CBCode::RL_L:
    case CBCode::RL_A:
        return RL_R(reg);

    case CBCode::RL_ADDR_HL:
        return RL_ADDR_HL();

    case CBCode::RR_B:
    case CBCode::RR_C:
    case CBCode::RR_D:
    case CBCode::RR_E:
    case CBCode::RR_H:
    case CBCode::RR_L:
    case CBCode::RR_A:
        return RR_R(reg);

    case CBCode::RR_ADDR_HL:
        return RR_ADDR_HL();

    case CBCode::SLA_B:
    case CBCode::SLA_C:
    case CBCode::SLA_D:
    case CBCode::SLA_E:
    case CBCode::SLA_H:
    case CBCode::SLA_L:
    case CBCode::SLA_A:
        return SLA_R(reg);

    case CBCode::SLA_ADDR_HL:
        return SLA_ADDR_HL();

    case CBCode::SRA_B:
    case CBCode::SRA_C:
    case CBCode::SRA_D:
    case CBCode::SRA_E:
    case CBCode::SRA_H:
    case CBCode::SRA_L:
    case CBCode::SRA_A:
        return SRA_R(reg);

    case CBCode::SRA_ADDR_HL:
        return SRA_ADDR_HL();

    case CBCode::SWAP_B:
    case CBCode::SWAP_C:
    case CBCode::SWAP_D:
    case CBCode::SWAP_E:
    case CBCode::SWAP_H:
    case CBCode::SWAP_L:
    case CBCode::SWAP_A:
        return SWAP_R(reg);

    case CBCode::SWAP_ADDR_HL:
        return SWAP_ADDR_HL();

    case CBCode::SRL_B:
    case CBCode::SRL_C:
    case CBCode::SRL_D:
    case CBCode::SRL_E:
    case CBCode::SRL_H:
    case CBCode::SRL_L:
    case CBCode::SRL_A:
        return SRL_R(reg);

    case CBCode::SRL_ADDR_HL:
        return SRL_ADDR_HL();

    case CBCode::BIT_0_B:
    case CBCode::BIT_0_C:
    case CBCode::BIT_0_D:
    case CBCode::BIT_0_E:
    case CBCode::BIT_0_H:
    case CBCode::BIT_0_L:
    case CBCode::BIT_0_A:
        return BIT_R(reg, 0);

    case CBCode::BIT_0_ADDR_HL:
        return BIT_ADDR_HL(0);


    case CBCode::BIT_1_B:
    case CBCode::BIT_1_C:
    case CBCode::BIT_1_D:
    case CBCode::BIT_1_E:
    case CBCode::BIT_1_H:
    case CBCode::BIT_1_L:
    case CBCode::BIT_1_A:
        return BIT_R(reg, 1);

    case CBCode::BIT_1_ADDR_HL:
        return BIT_ADDR_HL(1);

    case CBCode::BIT_2_B:
    case CBCode::BIT_2_C:
    case CBCode::BIT_2_D:
    case CBCode::BIT_2_E:
    case CBCode::BIT_2_H:
    case CBCode::BIT_2_L:
    case CBCode::BIT_2_A:
        return BIT_R(reg, 2);

    case CBCode::BIT_2_ADDR_HL:
        return BIT_ADDR_HL(2);

    case CBCode::BIT_3_B:
    case CBCode::BIT_3_C:
    case CBCode::BIT_3_D:
    case CBCode::BIT_3_E:
    case CBCode::BIT_3_H:
    case CBCode::BIT_3_L:
    case CBCode::BIT_3_A:
        return BIT_R(reg, 3);

    case CBCode::BIT_3_ADDR_HL:
        return BIT_ADDR_HL(3);

    case CBCode::BIT_4_B:
    case CBCode::BIT_4_C:
    case CBCode::BIT_4_D:
    case CBCode::BIT_4_E:
    case CBCode::BIT_4_H:
    case CBCode::BIT_4_L:
    case CBCode::BIT_4_A:
        return BIT_R(reg, 4);

    case CBCode::BIT_4_ADDR_HL:
        return BIT_ADDR_HL(4);

    case CBCode::BIT_5_B:
    case CBCode::BIT_5_C:
    case CBCode::BIT_5_D:
    case CBCode::BIT_5_E:
    case CBCode::BIT_5_H:
    case CBCode::BIT_5_L:
    case CBCode::BIT_5_A:
        return BIT_R(reg, 5);

    case CBCode::BIT_5_ADDR_HL:
        return BIT_ADDR_HL(5);

    case CBCode::BIT_6_B:
    case CBCode::BIT_6_C:
    case CBCode::BIT_6_D:
    case CBCode::BIT_6_E:
    case CBCode::BIT_6_H:
    case CBCode::BIT_6_L:
    case CBCode::BIT_6_A:
        return BIT_R(reg, 6);

    case CBCode::BIT_6_ADDR_HL:
        return BIT_ADDR_HL(6);

    case CBCode::BIT_7_B:
    case CBCode::BIT_7_C:
    case CBCode::BIT_7_D:
    case CBCode::BIT_7_E:
    case CBCode::BIT_7_H:
    case CBCode::BIT_7_L:
    case CBCode::BIT_7_A:
        return BIT_R(reg, 7);

    case CBCode::BIT_7_ADDR_HL:
        return BIT_ADDR_HL(7);

    case CBCode::RES_0_B:
    case CBCode::RES_0_C:
    case CBCode::RES_0_D:
    case CBCode::RES_0_E:
    case CBCode::RES_0_H:
    case CBCode::RES_0_L:
    case CBCode::RES_0_A:
        return RES_R(reg, 0);

    case CBCode::RES_0_ADDR_HL:
        return RES_ADDR_HL(0);

    case CBCode::RES_1_B:
    case CBCode::RES_1_C:
    case CBCode::RES_1_D:
    case CBCode::RES_1_E:
    case CBCode::RES_1_H:
    case CBCode::RES_1_L:
    case CBCode::RES_1_A:
        return RES_R(reg, 1);

    case CBCode::RES_1_ADDR_HL:
        return RES_ADDR_HL(1);

    case CBCode::RES_2_B:
    case CBCode::RES_2_C:
    case CBCode::RES_2_D:
    case CBCode::RES_2_E:
    case CBCode::RES_2_H:
    case CBCode::RES_2_L:
    case CBCode::RES_2_A:
        return RES_R(reg, 2);

    case CBCode::RES_2_ADDR_HL:
        return RES_ADDR_HL(2);

    case CBCode::RES_3_B:
    case CBCode::RES_3_C:
    case CBCode::RES_3_D:
    case CBCode::RES_3_E:
    case CBCode::RES_3_H:
    case CBCode::RES_3_L:
    case CBCode::RES_3_A:
        return RES_R(reg, 3);

    case CBCode::RES_3_ADDR_HL:
        return RES_ADDR_HL(3);

    case CBCode::RES_4_B:
    case CBCode::RES_4_C:
    case CBCode::RES_4_D:
    case CBCode::RES_4_E:
    case CBCode::RES_4_H:
    case CBCode::RES_4_L:
    case CBCode::RES_4_A:
        return RES_R(reg, 4);

    case CBCode::RES_4_ADDR_HL:
        return RES_ADDR_HL(4);

    case CBCode::RES_5_B:
    case CBCode::RES_5_C:
    case CBCode::RES_5_D:
    case CBCode::RES_5_E:
    case CBCode::RES_5_H:
    case CBCode::RES_5_L:
    case CBCode::RES_5_A:
        return RES_R(reg, 5);

    case CBCode::RES_5_ADDR_HL:
        return RES_ADDR_HL(5);

    case CBCode::RES_6_B:
    case CBCode::RES_6_C:
    case CBCode::RES_6_D:
    case CBCode::RES_6_E:
    case CBCode::RES_6_H:
    case CBCode::RES_6_L:
    case CBCode::RES_6_A:
        return RES_R(reg, 6);

    case CBCode::RES_6_ADDR_HL:
        return RES_ADDR_HL(6);

    case CBCode::RES_7_B:
    case CBCode::RES_7_C:
    case CBCode::RES_7_D:
    case CBCode::RES_7_E:
    case CBCode::RES_7_H:
    case CBCode::RES_7_L:
    case CBCode::RES_7_A:
        return RES_R(reg, 7);

    case CBCode::RES_7_ADDR_HL:
        return RES_ADDR_HL(7);

    case CBCode::SET_0_B:
    case CBCode::SET_0_C:
    case CBCode::SET_0_D:
    case CBCode::SET_0_E:
    case CBCode::SET_0_H:
    case CBCode::SET_0_L:
    case CBCode::SET_0_A:
        return SET_R(reg, 0);

    case CBCode::SET_0_ADDR_HL:
        return SET_ADDR_HL(0);

    case CBCode::SET_1_B:
    case CBCode::SET_1_C:
    case CBCode::SET_1_D:
    case CBCode::SET_1_E:
    case CBCode::SET_1_H:
    case CBCode::SET_1_L:
    case CBCode::SET_1_A:
        return SET_R(reg, 1);

    case CBCode::SET_1_ADDR_HL:
        return SET_ADDR_HL(1);

    case CBCode::SET_2_B:
    case CBCode::SET_2_C:
    case CBCode::SET_2_D:
    case CBCode::SET_2_E:
    case CBCode::SET_2_H:
    case CBCode::SET_2_L:
    case CBCode::SET_2_A:
        return SET_R(reg, 2);

    case CBCode::SET_2_ADDR_HL:
        return SET_ADDR_HL(2);

    case CBCode::SET_3_B:
    case CBCode::SET_3_C:
    case CBCode::SET_3_D:
    case CBCode::SET_3_E:
    case CBCode::SET_3_H:
    case CBCode::SET_3_L:
    case CBCode::SET_3_A:
        return SET_R(reg, 3);

    case CBCode::SET_3_ADDR_HL:
        return SET_ADDR_HL(3);

    case CBCode::SET_4_B:
    case CBCode::SET_4_C:
    case CBCode::SET_4_D:
    case CBCode::SET_4_E:
    case CBCode::SET_4_H:
    case CBCode::SET_4_L:
    case CBCode::SET_4_A:
        return SET_R(reg, 4);

    case CBCode::SET_4_ADDR_HL:
        return SET_ADDR_HL(4);

    case CBCode::SET_5_B:
    case CBCode::SET_5_C:
    case CBCode::SET_5_D:
    case CBCode::SET_5_E:
    case CBCode::SET_5_H:
    case CBCode::SET_5_L:
    case CBCode::SET_5_A:
        return SET_R(reg, 5);

    case CBCode::SET_5_ADDR_HL:
        return SET_ADDR_HL(5);

    case CBCode::SET_6_B:
    case CBCode::SET_6_C:
    case CBCode::SET_6_D:
    case CBCode::SET_6_E:
    case CBCode::SET_6_H:
    case CBCode::SET_6_L:
    case CBCode::SET_6_A:
        return SET_R(reg, 6);

    case CBCode::SET_6_ADDR_HL:
        return SET_ADDR_HL(6);

    case CBCode::SET_7_B:
    case CBCode::SET_7_C:
    case CBCode::SET_7_D:
    case CBCode::SET_7_E:
    case CBCode::SET_7_H:
    case CBCode::SET_7_L:
    case CBCode::SET_7_A:
        return SET_R(reg, 7);

    case CBCode::SET_7_ADDR_HL:
        return SET_ADDR_HL(7);

    default:
        throw UnimplementedOperation("Unimplemented CB Code\n");
        break;
    }
}