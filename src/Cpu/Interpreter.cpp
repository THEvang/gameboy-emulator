#include "Cpu/Interpreter.hpp"
#include "Cpu/Operations.hpp"
#include "Cpu/CBOperations.hpp"

#include <stdio.h>

Instruction fetch(Opcode opcode) {
    
    switch (opcode) {
    case Opcode_NOP:
        return NOP();

    case Opcode_LD_BC_D16:
        return LD_RR_D16(Register_B, Register_C);

    case Opcode_LD_ADDR_BC_A:
        return LD_ADDR_RR_A(Register_B, Register_C);

    case Opcode_INC_BC:
        return INC_RR(Register_B, Register_C);

    case Opcode_INC_B:
        return INC_R(Register_B);

    case Opcode_DEC_B:
        return DEC_R(Register_B);

    case Opcode_LD_B_D8:
        return LD_R_D8(Register_B);

    case Opcode_RLCA:
        return RLCA();

    case Opcode_LD_ADDR_A16_SP:
        return LD_ADDR_A16_SP();

    case Opcode_ADD_HL_BC:
        return ADD_HL_RR(Register_B, Register_C);

    case Opcode_LD_A_ADDR_BC:
        return LD_A_ADDR_RR(Register_B, Register_C);

    case Opcode_DEC_BC:
        return DEC_RR(Register_B, Register_C);

    case Opcode_INC_C:
        return INC_R(Register_C);

    case Opcode_DEC_C:
        return DEC_R(Register_C);

    case Opcode_LD_C_D8:
        return LD_R_D8(Register_C);

    case Opcode_RRCA:
        return RRCA();

    case Opcode_STOP:
        return STOP();

    case Opcode_LD_DE_D16:
        return LD_RR_D16(Register_D, Register_E);

    case Opcode_LD_ADDR_DE_A:
        return LD_ADDR_RR_A(Register_D, Register_E);

    case Opcode_INC_DE:
        return INC_RR(Register_D, Register_E);

    case Opcode_INC_D:
        return INC_R(Register_D);

    case Opcode_DEC_D:
        return DEC_R(Register_D);

    case Opcode_LD_D_D8:
        return LD_R_D8(Register_D);

    case Opcode_RLA:
        return RLA();

    case Opcode_JR_R8:
        return JR();

    case Opcode_ADD_HL_DE:
        return ADD_HL_RR(Register_D, Register_E);

    case Opcode_LD_A_ADDR_DE:
        return LD_A_ADDR_RR(Register_D, Register_E);

    case Opcode_DEC_DE:
        return DEC_RR(Register_D, Register_E);

    case Opcode_INC_E:
        return INC_R(Register_E);

    case Opcode_DEC_E:
        return DEC_R(Register_E);

    case Opcode_LD_E_D8:
        return LD_R_D8(Register_E);

    case Opcode_RRA:
        return RRA();

    case Opcode_JR_NZ_R8:
        return JR_NZ();

    case Opcode_LD_HL_D16:
        return LD_RR_D16(Register_H, Register_L);

    case Opcode_LD_ADDR_HLI_A:
        return LDI_ADDR_HL_A();

    case Opcode_INC_HL:
        return INC_RR(Register_H, Register_L);

    case Opcode_INC_H:
        return INC_R(Register_H);

    case Opcode_DEC_H:
        return DEC_R(Register_H);

    case Opcode_LD_H_D8:
        return LD_R_D8(Register_H);

    case Opcode_DAA:
        return DAA();

    case Opcode_JR_Z_R8:
        return JR_Z();

    case Opcode_ADD_HL_HL:
        return ADD_HL_RR(Register_H, Register_L);

    case Opcode_LD_A_ADDR_HLI:
        return LDI_A_ADDR_HL();

    case Opcode_DEC_HL:
        return DEC_RR(Register_H, Register_L);

    case Opcode_INC_L:
        return INC_R(Register_L);

    case Opcode_DEC_L:
        return DEC_R(Register_L);

    case Opcode_LD_L_D8:
        return LD_R_D8(Register_L);

    case Opcode_CPL:
        return CPL();

    case Opcode_JR_NC_R8:
        return JR_NC();

    case Opcode_LD_SP_D16:
        return LD_SP_D16();

    case Opcode_LD_ADDR_HLD_A:
        return LD_ADDR_HLD_A();

    case Opcode_INC_SP:
        return INC_SP();

    case Opcode_INC_ADDR_HL:
        return INC_ADDR_HL();

    case Opcode_DEC_ADDR_HL:
        return DEC_ADDR_HL();

    case Opcode_LD_ADDR_HL_D8:
        return LD_ADDR_HL_D8();

    case Opcode_SCF:
        return SCF();

    case Opcode_JR_C_R8:
        return JR_C();

    case Opcode_ADD_HL_SP:
        return ADD_HL_SP();

    case Opcode_LD_A_ADDR_HLD:
        return LD_A_ADDR_HLD();

    case Opcode_DEC_SP:
        return DEC_SP();

    case Opcode_INC_A:
        return INC_R(Register_A);

    case Opcode_DEC_A:
        return DEC_R(Register_A);

    case Opcode_LD_A_D8:
        return LD_R_D8(Register_A);

    case Opcode_CCF:
        return CCF();

    case Opcode_LD_B_B:
        return LD_R_R(Register_B, Register_B);

    case Opcode_LD_B_C:
        return LD_R_R(Register_B, Register_C);

    case Opcode_LD_B_D:
        return LD_R_R(Register_B, Register_D);

    case Opcode_LD_B_E:
        return LD_R_R(Register_B, Register_E);

    case Opcode_LD_B_H:
        return LD_R_R(Register_B, Register_H);

    case Opcode_LD_B_L:
        return LD_R_R(Register_B, Register_L);

    case Opcode_LD_B_ADDR_HL:
        return LD_R_ADDR_HL(Register_B);

    case Opcode_LD_B_A:
        return LD_R_R(Register_B, Register_A);

    case Opcode_LD_C_B:
        return LD_R_R(Register_C, Register_B);

    case Opcode_LD_C_C:
        return LD_R_R(Register_C, Register_C);

    case Opcode_LD_C_D:
        return LD_R_R(Register_C, Register_D);

    case Opcode_LD_C_E:
        return LD_R_R(Register_C, Register_E);

    case Opcode_LD_C_H:
        return LD_R_R(Register_C, Register_H);

    case Opcode_LD_C_L:
        return LD_R_R(Register_C, Register_L);

    case Opcode_LD_C_ADDR_HL:
        return LD_R_ADDR_HL(Register_C);

    case Opcode_LD_C_A:
        return LD_R_R(Register_C, Register_A);

    case Opcode_LD_D_B:
        return LD_R_R(Register_D, Register_B);

    case Opcode_LD_D_C:
        return LD_R_R(Register_D, Register_C);

    case Opcode_LD_D_D:
        return LD_R_R(Register_D, Register_D);

    case Opcode_LD_D_E:
        return LD_R_R(Register_D, Register_E);

    case Opcode_LD_D_H:
        return LD_R_R(Register_D, Register_H);

    case Opcode_LD_D_L:
        return LD_R_R(Register_D, Register_L);

    case Opcode_LD_D_ADDR_HL:
        return LD_R_ADDR_HL(Register_D);

    case Opcode_LD_D_A:
        return LD_R_R(Register_D, Register_A);

    case Opcode_LD_E_B:
        return LD_R_R(Register_E, Register_B);

    case Opcode_LD_E_C:
        return LD_R_R(Register_E, Register_C);

    case Opcode_LD_E_D:
        return LD_R_R(Register_E, Register_D);

    case Opcode_LD_E_E:
        return LD_R_R(Register_E, Register_E);

    case Opcode_LD_E_H:
        return LD_R_R(Register_E, Register_H);

    case Opcode_LD_E_L:
        return LD_R_R(Register_E, Register_L);

    case Opcode_LD_E_ADDR_HL:
        return LD_R_ADDR_HL(Register_E);

    case Opcode_LD_E_A:
        return LD_R_R(Register_E, Register_A);

    case Opcode_LD_H_B:
        return LD_R_R(Register_H, Register_B);

    case Opcode_LD_H_C:
        return LD_R_R(Register_H, Register_C);

    case Opcode_LD_H_D:
        return LD_R_R(Register_H, Register_D);

    case Opcode_LD_H_E:
        return LD_R_R(Register_H, Register_E);

    case Opcode_LD_H_H:
        return LD_R_R(Register_H, Register_H);

    case Opcode_LD_H_L:
        return LD_R_R(Register_H, Register_L);

    case Opcode_LD_H_ADDR_HL:
        return LD_R_ADDR_HL(Register_H);

    case Opcode_LD_H_A:
        return LD_R_R(Register_H, Register_A);

    case Opcode_LD_L_B:
        return LD_R_R(Register_L, Register_B);

    case Opcode_LD_L_C:
        return LD_R_R(Register_L, Register_C);

    case Opcode_LD_L_D:
        return LD_R_R(Register_L, Register_D);

    case Opcode_LD_L_E:
        return LD_R_R(Register_L, Register_E);

    case Opcode_LD_L_H:
        return LD_R_R(Register_L, Register_H);

    case Opcode_LD_L_L:
        return LD_R_R(Register_L, Register_L);

    case Opcode_LD_L_ADDR_HL:
        return LD_R_ADDR_HL(Register_L);

    case Opcode_LD_L_A:
        return LD_R_R(Register_L, Register_A);

    case Opcode_LD_ADDR_HL_B:
        return LD_ADDR_HL_R(Register_B);

    case Opcode_LD_ADDR_HL_C:
        return LD_ADDR_HL_R(Register_C);

    case Opcode_LD_ADDR_HL_D:
        return LD_ADDR_HL_R(Register_D);

    case Opcode_LD_ADDR_HL_E:
        return LD_ADDR_HL_R(Register_E);

    case Opcode_LD_ADDR_HL_H:
        return LD_ADDR_HL_R(Register_H);

    case Opcode_LD_ADDR_HL_L:
        return LD_ADDR_HL_R(Register_L);

    case Opcode_HALT:
        return HALT();

    case Opcode_LD_ADDR_HL_A:
        return LD_ADDR_HL_R(Register_A);

    case Opcode_LD_A_B:
        return LD_R_R(Register_A, Register_B);

    case Opcode_LD_A_C:
        return LD_R_R(Register_A, Register_C);

    case Opcode_LD_A_D:
        return LD_R_R(Register_A, Register_D);

    case Opcode_LD_A_E:
        return LD_R_R(Register_A, Register_E);

    case Opcode_LD_A_H:
        return LD_R_R(Register_A, Register_H);

    case Opcode_LD_A_L:
        return LD_R_R(Register_A, Register_L);

    case Opcode_LD_A_ADDR_HL:
        return LD_R_ADDR_HL(Register_A);

    case Opcode_LD_A_A:
        return LD_R_R(Register_A, Register_A);

    case Opcode_ADD_A_B:
        return ADD_R(Register_B);

    case Opcode_ADD_A_C:
        return ADD_R(Register_C);

    case Opcode_ADD_A_D:
        return ADD_R(Register_D);

    case Opcode_ADD_A_E:
        return ADD_R(Register_E);

    case Opcode_ADD_A_H:
        return ADD_R(Register_H);

    case Opcode_ADD_A_L:
        return ADD_R(Register_L);

    case Opcode_ADD_A_ADDR_HL:
        return ADD_ADDR_HL();

    case Opcode_ADD_A_A:
        return ADD_R(Register_A);

    case Opcode_ADC_A_B:
        return ADC_R(Register_B);

    case Opcode_ADC_A_C:
        return ADC_R(Register_C);

    case Opcode_ADC_A_D:
        return ADC_R(Register_D);

    case Opcode_ADC_A_E:
        return ADC_R(Register_E);

    case Opcode_ADC_A_H:
        return ADC_R(Register_H);

    case Opcode_ADC_A_L:
        return ADC_R(Register_L);

    case Opcode_ADC_A_ADDR_HL:
        return ADC_ADDR_HL();

    case Opcode_ADC_A_A:
        return ADC_R(Register_A);

    case Opcode_SUB_B:
        return SUB_R(Register_B);

    case Opcode_SUB_C:
        return SUB_R(Register_C);

    case Opcode_SUB_D:
        return SUB_R(Register_D);

    case Opcode_SUB_E:
        return SUB_R(Register_E);

    case Opcode_SUB_H:
        return SUB_R(Register_H);

    case Opcode_SUB_L:
        return SUB_R(Register_L);

    case Opcode_SUB_ADDR_HL:
        return SUB_ADDR_HL();

    case Opcode_SUB_A:
        return SUB_R(Register_A);

    case Opcode_SBC_A_B:
        return SBC_R(Register_B);

    case Opcode_SBC_A_C:
        return SBC_R(Register_C);

    case Opcode_SBC_A_D:
        return SBC_R(Register_D);

    case Opcode_SBC_A_E:
        return SBC_R(Register_E);

    case Opcode_SBC_A_H:
        return SBC_R(Register_H);

    case Opcode_SBC_A_L:
        return SBC_R(Register_L);

    case Opcode_SBC_A_ADDR_HL:
        return SBC_A_ADDR_HL();

    case Opcode_SBC_A_A:
        return SBC_R(Register_A);

    case Opcode_AND_B:
        return AND_R(Register_B);

    case Opcode_AND_C:
        return AND_R(Register_C);

    case Opcode_AND_D:
        return AND_R(Register_D);

    case Opcode_AND_E:
        return AND_R(Register_E);

    case Opcode_AND_H:
        return AND_R(Register_H);

    case Opcode_AND_L:
        return AND_R(Register_L);

    case Opcode_AND_ADDR_HL:
        return AND_ADDR_HL();

    case Opcode_AND_A:
        return AND_R(Register_A);

    case Opcode_XOR_B:
        return XOR_R(Register_B);

    case Opcode_XOR_C:
        return XOR_R(Register_C);

    case Opcode_XOR_D:
        return XOR_R(Register_D);

    case Opcode_XOR_E:
        return XOR_R(Register_E);

    case Opcode_XOR_H:
        return XOR_R(Register_H);

    case Opcode_XOR_L:
        return XOR_R(Register_L);

    case Opcode_XOR_ADDR_HL:
        return XOR_ADDR_HL();

    case Opcode_XOR_A:
        return XOR_R(Register_A);

    case Opcode_OR_B:
        return OR_R(Register_B);

    case Opcode_OR_C:
        return OR_R(Register_C);

    case Opcode_OR_D:
        return OR_R(Register_D);

    case Opcode_OR_E:
        return OR_R(Register_E);

    case Opcode_OR_H:
        return OR_R(Register_H);

    case Opcode_OR_L:
        return OR_R(Register_L);

    case Opcode_OR_ADDR_HL:
        return OR_ADDR_HL();

    case Opcode_OR_A:
        return OR_R(Register_A);

    case Opcode_CP_B:
        return CP_R(Register_B);

    case Opcode_CP_C:
        return CP_R(Register_C);

    case Opcode_CP_D:
        return CP_R(Register_D);

    case Opcode_CP_E:
        return CP_R(Register_E);

    case Opcode_CP_H:
        return CP_R(Register_H);

    case Opcode_CP_L:
        return CP_R(Register_L);

    case Opcode_CP_ADDR_HL:
        return CP_ADDR_HL();

    case Opcode_CP_A:
        return CP_R(Register_A);

    case Opcode_RET_NZ:
        return RET_NZ();

    case Opcode_POP_BC:
        return POP_RR(Register_B, Register_C);

    case Opcode_JP_NZ_A16:
        return JUMP_NZ();

    case Opcode_JP_A16:
        return JUMP();

    case Opcode_CALL_NZ_A16:
        return CALL_NZ();

    case Opcode_PUSH_BC:
        return PUSH_RR(Register_B, Register_C);

    case Opcode_ADD_A_D8:
        return ADD_D8();

    case Opcode_RST_00H:
        return RST(0x00);

    case Opcode_RET_Z:
        return RET_Z();

    case Opcode_RET:
        return RET();

    case Opcode_JP_Z_A16:
        return JUMP_Z();

    case Opcode_PREFIX_CB:
        return PREFIX_CB();

    case Opcode_CALL_Z_A16:
        return CALL_Z();

    case Opcode_CALL_A16:
        return CALL();

    case Opcode_ADC_A_D8:
        return ADC_D8();

    case Opcode_RST_08H:
        return RST(0x08);

    case Opcode_RET_NC:
        return RET_NC();

    case Opcode_POP_DE:
        return POP_RR(Register_D, Register_E);

    case Opcode_JP_NC_A16:
        return JUMP_NC();

    case Opcode_CALL_NC_A16:
        return CALL_NC();

    case Opcode_PUSH_DE:
        return PUSH_RR(Register_D, Register_E);

    case Opcode_SUB_D8:
        return SUB_D8();

    case Opcode_RST_10H:
        return RST(0x10);

    case Opcode_RET_C:
        return RET_C();

    case Opcode_RETI:
        return RETI();

    case Opcode_JP_C_A16:
        return JUMP_C();

    case Opcode_CALL_C_A16:
        return CALL_C();

    case Opcode_SBC_A_D8:
        return SBC_D8();

    case Opcode_RST_18H:
        return RST(0x18);

    case Opcode_LDH_ADDR_A8_A:
        return LDH_ADDR_A8_A();

    case Opcode_POP_HL:
        return POP_RR(Register_H, Register_L);

    case Opcode_LD_ADDR_C_A:
        return LD_ADDR_C_A();

    case Opcode_PUSH_HL:
        return PUSH_RR(Register_H, Register_L);

    case Opcode_AND_D8:
        return AND_D8();

    case Opcode_RST_20H:
        return RST(0x20);

    case Opcode_ADD_SP_R8:
        return ADD_SP_R8();

    case Opcode_JP_ADDR_HL:
        return JUMP_ADDR_HL();

    case Opcode_LD_ADDR_A16_A:
        return LD_ADDR_A16_A();

    case Opcode_XOR_D8:
        return XOR_D8();

    case Opcode_RST_28H:
        return RST(0x28);

    case Opcode_LDH_A_ADDR_A8:
        return LDH_A_ADDR_A8();

    case Opcode_POP_AF:
        return POP_AF();

    case Opcode_LD_A_ADDR_C:
        return LD_A_ADDR_C();

    case Opcode_DI:
        return DI();

    case Opcode_PUSH_AF:
        return PUSH_RR(Register_A, Register_F);

    case Opcode_OR_D8:
        return OR_D8();

    case Opcode_RST_30H:
        return RST(0x30);

    case Opcode_LD_HL_SPR8:
        return LD_HL_SPR8();

    case Opcode_LD_SP_HL:
        return LD_SP_HL();

    case Opcode_LD_A_ADDR_A16:
        return LD_A_ADDR_A16();

    case Opcode_EI:
        return EI();

    case Opcode_CP_D8:
        return CP_D8();

    case Opcode_RST_38H:
        return RST(0x38);

    default:
        printf("Invalid Opcode: %d\n", opcode);
        exit(1);
    }
}

Cpu_Register get_cb_register(CB_Code opcode) {
    auto lower = static_cast<uint8_t>(opcode) & 0x0F;

    switch(lower) {
        case 0x00:
        case 0x08:
            return Register_B;
        case 0x01:
        case 0x09:
            return Register_C;
        case 0x02:
        case 0x0A:
            return Register_D;
        case 0x03:
        case 0x0B:
            return Register_E;
        case 0x04:
        case 0x0C:
            return Register_H;
        case 0x05:
        case 0x0D:
            return Register_L;
        case 0x07:
        case 0x0E:
        default:
            return Register_A;
    }
}

int get_bit_index(CBCode opcode) {
    
    auto get_column_index = [](CBCode opcode) -> int {
        auto lower = static_cast<uint8_t>(opcode) & 0x0F;
        return lower <= 0x07 ? 0 : 1;
    };

    auto get_row_index = [](CBCode opcode) -> int {
        auto upper = static_cast<uint8_t>(opcode) & 0xF0;
        if(upper == 0x40 || upper == 0x80 || upper == 0xC0) {
            return 0;
        } else if(upper == 0x50 || upper == 0x90 || upper == 0xD0) {
            return 2;
        } else if(upper == 0x60 || upper == 0xA0 || upper == 0xE0) {
            return 4;
        }  
        return 6;
    };

    return get_column_index(opcode) + get_row_index(opcode);
}

Instruction fetch_cb(CBCode opcode)
{
    const auto reg = get_cb_register(opcode);
    switch (opcode) {
    case CB_Code_RLC_B:
    case CB_Code_RLC_C:
    case CB_Code_RLC_D:
    case CB_Code_RLC_E:
    case CB_Code_RLC_H:
    case CB_Code_RLC_L:
    case CB_Code_RLC_A:
        return RLC_R(reg);

    case CB_Code_RLC_ADDR_HL:
        return RLC_ADDR_HL();

    case CB_Code_RRC_B:
    case CB_Code_RRC_C:
    case CB_Code_RRC_D:
    case CB_Code_RRC_E:
    case CB_Code_RRC_H:
    case CB_Code_RRC_L:
    case CB_Code_RRC_A:
        return RRC_R(reg);

    case CB_Code_RRC_ADDR_HL:
        return RRC_ADDR_HL();

    case CB_Code_RL_B:
    case CB_Code_RL_C:
    case CB_Code_RL_D:
    case CB_Code_RL_E:
    case CB_Code_RL_H:
    case CB_Code_RL_L:
    case CB_Code_RL_A:
        return RL_R(reg);

    case CB_Code_RL_ADDR_HL:
        return RL_ADDR_HL();

    case CB_Code_RR_B:
    case CB_Code_RR_C:
    case CB_Code_RR_D:
    case CB_Code_RR_E:
    case CB_Code_RR_H:
    case CB_Code_RR_L:
    case CB_Code_RR_A:
        return RR_R(reg);

    case CB_Code_RR_ADDR_HL:
        return RR_ADDR_HL();

    case CB_Code_SLA_B:
    case CB_Code_SLA_C:
    case CB_Code_SLA_D:
    case CB_Code_SLA_E:
    case CB_Code_SLA_H:
    case CB_Code_SLA_L:
    case CB_Code_SLA_A:
        return SLA_R(reg);

    case CB_Code_SLA_ADDR_HL:
        return SLA_ADDR_HL();

    case CB_Code_SRA_B:
    case CB_Code_SRA_C:
    case CB_Code_SRA_D:
    case CB_Code_SRA_E:
    case CB_Code_SRA_H:
    case CB_Code_SRA_L:
    case CB_Code_SRA_A:
        return SRA_R(reg);

    case CB_Code_SRA_ADDR_HL:
        return SRA_ADDR_HL();

    case CB_Code_SWAP_B:
    case CB_Code_SWAP_C:
    case CB_Code_SWAP_D:
    case CB_Code_SWAP_E:
    case CB_Code_SWAP_H:
    case CB_Code_SWAP_L:
    case CB_Code_SWAP_A:
        return SWAP_R(reg);

    case CB_Code_SWAP_ADDR_HL:
        return SWAP_ADDR_HL();

    case CB_Code_SRL_B:
    case CB_Code_SRL_C:
    case CB_Code_SRL_D:
    case CB_Code_SRL_E:
    case CB_Code_SRL_H:
    case CB_Code_SRL_L:
    case CB_Code_SRL_A:
        return SRL_R(reg);

    case CB_Code_SRL_ADDR_HL:
        return SRL_ADDR_HL();

    case CB_Code_BIT_0_B:
    case CB_Code_BIT_0_C:
    case CB_Code_BIT_0_D:
    case CB_Code_BIT_0_E:
    case CB_Code_BIT_0_H:
    case CB_Code_BIT_0_L:
    case CB_Code_BIT_0_A:
    case CB_Code_BIT_1_B:
    case CB_Code_BIT_1_C:
    case CB_Code_BIT_1_D:
    case CB_Code_BIT_1_E:
    case CB_Code_BIT_1_H:
    case CB_Code_BIT_1_L:
    case CB_Code_BIT_1_A:
    case CB_Code_BIT_2_B:
    case CB_Code_BIT_2_C:
    case CB_Code_BIT_2_D:
    case CB_Code_BIT_2_E:
    case CB_Code_BIT_2_H:
    case CB_Code_BIT_2_L:
    case CB_Code_BIT_2_A:
    case CB_Code_BIT_3_B:
    case CB_Code_BIT_3_C:
    case CB_Code_BIT_3_D:
    case CB_Code_BIT_3_E:
    case CB_Code_BIT_3_H:
    case CB_Code_BIT_3_L:
    case CB_Code_BIT_3_A:
    case CB_Code_BIT_4_B:
    case CB_Code_BIT_4_C:
    case CB_Code_BIT_4_D:
    case CB_Code_BIT_4_E:
    case CB_Code_BIT_4_H:
    case CB_Code_BIT_4_L:
    case CB_Code_BIT_4_A:
    case CB_Code_BIT_5_B:
    case CB_Code_BIT_5_C:
    case CB_Code_BIT_5_D:
    case CB_Code_BIT_5_E:
    case CB_Code_BIT_5_H:
    case CB_Code_BIT_5_L:
    case CB_Code_BIT_5_A:
    case CB_Code_BIT_6_B:
    case CB_Code_BIT_6_C:
    case CB_Code_BIT_6_D:
    case CB_Code_BIT_6_E:
    case CB_Code_BIT_6_H:
    case CB_Code_BIT_6_L:
    case CB_Code_BIT_6_A:
    case CB_Code_BIT_7_B:
    case CB_Code_BIT_7_C:
    case CB_Code_BIT_7_D:
    case CB_Code_BIT_7_E:
    case CB_Code_BIT_7_H:
    case CB_Code_BIT_7_L:
    case CB_Code_BIT_7_A:
        return BIT_R(reg, get_bit_index(opcode));

    case CB_Code_BIT_0_ADDR_HL:
    case CB_Code_BIT_1_ADDR_HL:
    case CB_Code_BIT_2_ADDR_HL:
    case CB_Code_BIT_3_ADDR_HL:
    case CB_Code_BIT_4_ADDR_HL:
    case CB_Code_BIT_5_ADDR_HL:
    case CB_Code_BIT_6_ADDR_HL:
    case CB_Code_BIT_7_ADDR_HL:
        return BIT_ADDR_HL(get_bit_index(opcode));

    case CB_Code_RES_0_B:
    case CB_Code_RES_0_C:
    case CB_Code_RES_0_D:
    case CB_Code_RES_0_E:
    case CB_Code_RES_0_H:
    case CB_Code_RES_0_L:
    case CB_Code_RES_0_A:
    case CB_Code_RES_1_B:
    case CB_Code_RES_1_C:
    case CB_Code_RES_1_D:
    case CB_Code_RES_1_E:
    case CB_Code_RES_1_H:
    case CB_Code_RES_1_L:
    case CB_Code_RES_1_A:
    case CB_Code_RES_2_B:
    case CB_Code_RES_2_C:
    case CB_Code_RES_2_D:
    case CB_Code_RES_2_E:
    case CB_Code_RES_2_H:
    case CB_Code_RES_2_L:
    case CB_Code_RES_2_A:
    case CB_Code_RES_3_B:
    case CB_Code_RES_3_C:
    case CB_Code_RES_3_D:
    case CB_Code_RES_3_E:
    case CB_Code_RES_3_H:
    case CB_Code_RES_3_L:
    case CB_Code_RES_3_A:
    case CB_Code_RES_4_B:
    case CB_Code_RES_4_C:
    case CB_Code_RES_4_D:
    case CB_Code_RES_4_E:
    case CB_Code_RES_4_H:
    case CB_Code_RES_4_L:
    case CB_Code_RES_4_A:
    case CB_Code_RES_5_B:
    case CB_Code_RES_5_C:
    case CB_Code_RES_5_D:
    case CB_Code_RES_5_E:
    case CB_Code_RES_5_H:
    case CB_Code_RES_5_L:
    case CB_Code_RES_5_A:
    case CB_Code_RES_6_B:
    case CB_Code_RES_6_C:
    case CB_Code_RES_6_D:
    case CB_Code_RES_6_E:
    case CB_Code_RES_6_H:
    case CB_Code_RES_6_L:
    case CB_Code_RES_6_A:
    case CB_Code_RES_7_B:
    case CB_Code_RES_7_C:
    case CB_Code_RES_7_D:
    case CB_Code_RES_7_E:
    case CB_Code_RES_7_H:
    case CB_Code_RES_7_L:
    case CB_Code_RES_7_A:
        return RES_R(reg, get_bit_index(opcode));

    case CB_Code_RES_0_ADDR_HL:
    case CB_Code_RES_1_ADDR_HL:
    case CB_Code_RES_2_ADDR_HL:
    case CB_Code_RES_3_ADDR_HL:
    case CB_Code_RES_4_ADDR_HL:
    case CB_Code_RES_5_ADDR_HL:
    case CB_Code_RES_6_ADDR_HL:
    case CB_Code_RES_7_ADDR_HL:
        return RES_ADDR_HL(get_bit_index(opcode));

    case CB_Code_SET_0_B:
    case CB_Code_SET_0_C:
    case CB_Code_SET_0_D:
    case CB_Code_SET_0_E:
    case CB_Code_SET_0_H:
    case CB_Code_SET_0_L:
    case CB_Code_SET_0_A:
    case CB_Code_SET_1_B:
    case CB_Code_SET_1_C:
    case CB_Code_SET_1_D:
    case CB_Code_SET_1_E:
    case CB_Code_SET_1_H:
    case CB_Code_SET_1_L:
    case CB_Code_SET_1_A:
    case CB_Code_SET_2_B:
    case CB_Code_SET_2_C:
    case CB_Code_SET_2_D:
    case CB_Code_SET_2_E:
    case CB_Code_SET_2_H:
    case CB_Code_SET_2_L:
    case CB_Code_SET_2_A:
    case CB_Code_SET_3_B:
    case CB_Code_SET_3_C:
    case CB_Code_SET_3_D:
    case CB_Code_SET_3_E:
    case CB_Code_SET_3_H:
    case CB_Code_SET_3_L:
    case CB_Code_SET_3_A:
    case CB_Code_SET_4_B:
    case CB_Code_SET_4_C:
    case CB_Code_SET_4_D:
    case CB_Code_SET_4_E:
    case CB_Code_SET_4_H:
    case CB_Code_SET_4_L:
    case CB_Code_SET_4_A:
    case CB_Code_SET_5_B:
    case CB_Code_SET_5_C:
    case CB_Code_SET_5_D:
    case CB_Code_SET_5_E:
    case CB_Code_SET_5_H:
    case CB_Code_SET_5_L:
    case CB_Code_SET_5_A:
    case CB_Code_SET_6_B:
    case CB_Code_SET_6_C:
    case CB_Code_SET_6_D:
    case CB_Code_SET_6_E:
    case CB_Code_SET_6_H:
    case CB_Code_SET_6_L:
    case CB_Code_SET_6_A:
    case CB_Code_SET_7_B:
    case CB_Code_SET_7_C:
    case CB_Code_SET_7_D:
    case CB_Code_SET_7_E:
    case CB_Code_SET_7_H:
    case CB_Code_SET_7_L:
    case CB_Code_SET_7_A:
        return SET_R(reg, get_bit_index(opcode));

    case CB_Code_SET_0_ADDR_HL:
    case CB_Code_SET_1_ADDR_HL:
    case CB_Code_SET_2_ADDR_HL:
    case CB_Code_SET_3_ADDR_HL:
    case CB_Code_SET_4_ADDR_HL:
    case CB_Code_SET_5_ADDR_HL:
    case CB_Code_SET_6_ADDR_HL:
    case CB_Code_SET_7_ADDR_HL:
        return SET_ADDR_HL(get_bit_index(opcode));

    default:
        printf("Unimplemented CB Code: %d\n", opcode);
        exit(1);
    }
}