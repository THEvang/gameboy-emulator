#pragma once

typedef enum Opcode {
    Opcode_NOP = 0x00,
    Opcode_LD_BC_D16,
    Opcode_LD_ADDR_BC_A,
    Opcode_INC_BC,
    Opcode_INC_B,
    Opcode_DEC_B,
    Opcode_LD_B_D8,
    Opcode_RLCA,
    Opcode_LD_ADDR_A16_SP,
    Opcode_ADD_HL_BC,
    Opcode_LD_A_ADDR_BC,
    Opcode_DEC_BC,
    Opcode_INC_C,
    Opcode_DEC_C,
    Opcode_LD_C_D8,
    Opcode_RRCA,

    Opcode_STOP = 0X10,
    Opcode_LD_DE_D16,
    Opcode_LD_ADDR_DE_A,
    Opcode_INC_DE,
    Opcode_INC_D,
    Opcode_DEC_D,
    Opcode_LD_D_D8,
    Opcode_RLA,
    Opcode_JR_R8,
    Opcode_ADD_HL_DE,
    Opcode_LD_A_ADDR_DE,
    Opcode_DEC_DE,
    Opcode_INC_E,
    Opcode_DEC_E,
    Opcode_LD_E_D8,
    Opcode_RRA,

    Opcode_JR_NZ_R8 = 0X20,
    Opcode_LD_HL_D16,
    Opcode_LD_ADDR_HLI_A,
    Opcode_INC_HL,
    Opcode_INC_H,
    Opcode_DEC_H,
    Opcode_LD_H_D8,
    Opcode_DAA,
    Opcode_JR_Z_R8,
    Opcode_ADD_HL_HL,
    Opcode_LD_A_ADDR_HLI,
    Opcode_DEC_HL,
    Opcode_INC_L,
    Opcode_DEC_L,
    Opcode_LD_L_D8,
    Opcode_CPL,

    Opcode_JR_NC_R8 = 0X30,
    Opcode_LD_SP_D16,
    Opcode_LD_ADDR_HLD_A,
    Opcode_INC_SP,
    Opcode_INC_ADDR_HL,
    Opcode_DEC_ADDR_HL,
    Opcode_LD_ADDR_HL_D8,
    Opcode_SCF,
    Opcode_JR_C_R8,
    Opcode_ADD_HL_SP,
    Opcode_LD_A_ADDR_HLD,
    Opcode_DEC_SP,
    Opcode_INC_A,
    Opcode_DEC_A, 
    Opcode_LD_A_D8,
    Opcode_CCF,

    Opcode_LD_B_B = 0X40,
    Opcode_LD_B_C,
    Opcode_LD_B_D,
    Opcode_LD_B_E,
    Opcode_LD_B_H,
    Opcode_LD_B_L,
    Opcode_LD_B_ADDR_HL,
    Opcode_LD_B_A,
    Opcode_LD_C_B,
    Opcode_LD_C_C,
    Opcode_LD_C_D,
    Opcode_LD_C_E,
    Opcode_LD_C_H,
    Opcode_LD_C_L,
    Opcode_LD_C_ADDR_HL,
    Opcode_LD_C_A,

    Opcode_LD_D_B = 0X50,
    Opcode_LD_D_C,
    Opcode_LD_D_D,
    Opcode_LD_D_E,
    Opcode_LD_D_H,
    Opcode_LD_D_L,
    Opcode_LD_D_ADDR_HL,
    Opcode_LD_D_A,

    Opcode_LD_E_B,
    Opcode_LD_E_C,
    Opcode_LD_E_D,
    Opcode_LD_E_E,
    Opcode_LD_E_H,
    Opcode_LD_E_L,
    Opcode_LD_E_ADDR_HL,
    Opcode_LD_E_A,

    Opcode_LD_H_B = 0X60,
    Opcode_LD_H_C,
    Opcode_LD_H_D,
    Opcode_LD_H_E,
    Opcode_LD_H_H,
    Opcode_LD_H_L,
    Opcode_LD_H_ADDR_HL,
    Opcode_LD_H_A,
    Opcode_LD_L_B,
    Opcode_LD_L_C,
    Opcode_LD_L_D,
    Opcode_LD_L_E,
    Opcode_LD_L_H,
    Opcode_LD_L_L,
    Opcode_LD_L_ADDR_HL,
    Opcode_LD_L_A,

    Opcode_LD_ADDR_HL_B = 0X70,
    Opcode_LD_ADDR_HL_C,
    Opcode_LD_ADDR_HL_D,
    Opcode_LD_ADDR_HL_E,
    Opcode_LD_ADDR_HL_H,
    Opcode_LD_ADDR_HL_L,
    Opcode_HALT,
    Opcode_LD_ADDR_HL_A,
    Opcode_LD_A_B,
    Opcode_LD_A_C,
    Opcode_LD_A_D,
    Opcode_LD_A_E,
    Opcode_LD_A_H,
    Opcode_LD_A_L,
    Opcode_LD_A_ADDR_HL,
    Opcode_LD_A_A,

    Opcode_ADD_A_B = 0X80,
    Opcode_ADD_A_C,
    Opcode_ADD_A_D,
    Opcode_ADD_A_E,
    Opcode_ADD_A_H,
    Opcode_ADD_A_L,
    Opcode_ADD_A_ADDR_HL,
    Opcode_ADD_A_A,

    Opcode_ADC_A_B,
    Opcode_ADC_A_C,
    Opcode_ADC_A_D,
    Opcode_ADC_A_E,
    Opcode_ADC_A_H,
    Opcode_ADC_A_L, 
    Opcode_ADC_A_ADDR_HL,
    Opcode_ADC_A_A,

    Opcode_SUB_B = 0X90,
    Opcode_SUB_C,
    Opcode_SUB_D,
    Opcode_SUB_E,
    Opcode_SUB_H,
    Opcode_SUB_L,
    Opcode_SUB_ADDR_HL,
    Opcode_SUB_A,
    
    Opcode_SBC_A_B,
    Opcode_SBC_A_C,
    Opcode_SBC_A_D,
    Opcode_SBC_A_E,
    Opcode_SBC_A_H,
    Opcode_SBC_A_L,
    Opcode_SBC_A_ADDR_HL,
    Opcode_SBC_A_A,

    Opcode_AND_B = 0XA0,
    Opcode_AND_C,
    Opcode_AND_D,
    Opcode_AND_E,
    Opcode_AND_H,
    Opcode_AND_L,
    Opcode_AND_ADDR_HL,
    Opcode_AND_A,
    
    Opcode_XOR_B,
    Opcode_XOR_C,
    Opcode_XOR_D,
    Opcode_XOR_E,
    Opcode_XOR_H,
    Opcode_XOR_L,
    Opcode_XOR_ADDR_HL,
    Opcode_XOR_A,

    Opcode_OR_B = 0XB0,
    Opcode_OR_C,
    Opcode_OR_D,
    Opcode_OR_E,
    Opcode_OR_H,
    Opcode_OR_L,
    Opcode_OR_ADDR_HL,
    Opcode_OR_A,

    Opcode_CP_B,
    Opcode_CP_C,
    Opcode_CP_D,
    Opcode_CP_E,
    Opcode_CP_H,
    Opcode_CP_L,
    Opcode_CP_ADDR_HL,
    Opcode_CP_A,

    Opcode_RET_NZ = 0XC0,
    Opcode_POP_BC,
    Opcode_JP_NZ_A16,
    Opcode_JP_A16,
    Opcode_CALL_NZ_A16,
    Opcode_PUSH_BC,
    Opcode_ADD_A_D8,
    Opcode_RST_00H,
    Opcode_RET_Z,
    Opcode_RET,
    Opcode_JP_Z_A16,
    Opcode_PREFIX_CB,
    Opcode_CALL_Z_A16,
    Opcode_CALL_A16,
    
    Opcode_ADC_A_D8,
    Opcode_RST_08H,

    Opcode_RET_NC = 0XD0,
    Opcode_POP_DE,
    Opcode_JP_NC_A16,

    Opcode_CALL_NC_A16 = 0XD4,
    Opcode_PUSH_DE,
    Opcode_SUB_D8,
    Opcode_RST_10H,
    Opcode_RET_C,
    Opcode_RETI,
    Opcode_JP_C_A16,

    Opcode_CALL_C_A16 = 0XDC,

    Opcode_SBC_A_D8 = 0XDE,
    Opcode_RST_18H,

    Opcode_LDH_ADDR_A8_A = 0XE0,
    Opcode_POP_HL,
    Opcode_LD_ADDR_C_A,

    Opcode_PUSH_HL = 0XE5,
    Opcode_AND_D8,
    Opcode_RST_20H,
    Opcode_ADD_SP_R8,
    Opcode_JP_ADDR_HL,
    Opcode_LD_ADDR_A16_A,

    Opcode_XOR_D8 = 0XEE,
    Opcode_RST_28H,

    Opcode_LDH_A_ADDR_A8 = 0XF0,
    Opcode_POP_AF,
    Opcode_LD_A_ADDR_C,
    Opcode_DI,

    Opcode_PUSH_AF = 0XF5,
    Opcode_OR_D8,
    Opcode_RST_30H,
    Opcode_LD_HL_SPR8,
    Opcode_LD_SP_HL,
    Opcode_LD_A_ADDR_A16,
    Opcode_EI,

    Opcode_CP_D8 = 0XFE,
    Opcode_RST_38H    
} Opcode;