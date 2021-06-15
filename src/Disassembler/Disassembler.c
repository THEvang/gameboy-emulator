#include "Disassembler/Disassembler.h"

#include <stdio.h>

int gb_disassemble(Opcode opcode) {

    switch (opcode) {
    case Opcode_NOP:
        return printf("%s", "NOP");

    case Opcode_LD_BC_D16:
        return printf("%s", "LD BC, d16");

    case Opcode_LD_ADDR_BC_A:
        return printf("%s", "LD (BC), A");

    case Opcode_INC_BC:
        return printf("%s", "INC BC");

    case Opcode_INC_B:
        return printf("%s", "INC B");

    case Opcode_DEC_B:
        return printf("%s", "DEC B");

    case Opcode_LD_B_D8:
        return printf("%s", "LD B, d8");

    case Opcode_RLCA:
        return printf("%s", "RLCA");

    case Opcode_LD_ADDR_A16_SP:
        return printf("%s", "LD (a16), SP");

    case Opcode_ADD_HL_BC:
        return printf("%s", "ADD HL, BC");

    case Opcode_LD_A_ADDR_BC:
        return printf("%s", "LD A, (BC)");

    case Opcode_DEC_BC:
        return printf("%s", "DEC BC");

    case Opcode_INC_C:
        return printf("%s", "INC C");

    case Opcode_DEC_C:
        return printf("%s", "DEC C");

    case Opcode_LD_C_D8:
        return printf("%s", "LD C d8");

    case Opcode_RRCA:
        return printf("%s", "RRCA");

    case Opcode_STOP:
        return printf("%s", "STOP");

    case Opcode_LD_DE_D16:
        return printf("%s", "LD DE, d16");

    case Opcode_LD_ADDR_DE_A:
        return printf("%s", "LD (DE), A");

    case Opcode_INC_DE:
        return printf("%s", "INC DE");

    case Opcode_INC_D:
        return printf("%s", "INC D");

    case Opcode_DEC_D:
        return printf("%s", "DEC D");

    case Opcode_LD_D_D8:
        return printf("%s", "LD D, d8");

    case Opcode_RLA:
        return printf("%s", "RLA");

    case Opcode_JR_R8:
        return printf("%s", "JR r8");

    case Opcode_ADD_HL_DE:
        return printf("%s", "ADD HL DE");

    case Opcode_LD_A_ADDR_DE:
        return printf("%s", "LD A, (DE)");

    case Opcode_DEC_DE:
        return printf("%s", "DEC DE");

    case Opcode_INC_E:
        return printf("%s", "INC E");

    case Opcode_DEC_E:
        return printf("%s", "DEC E");

    case Opcode_LD_E_D8:
        return printf("%s", "LD E, d8");

    case Opcode_RRA:
        return printf("%s", "RRA");

    case Opcode_JR_NZ_R8:
        return printf("%s", "JR NZ, r8");

    case Opcode_LD_HL_D16:
        return printf("%s", "LD HL, d16");

    case Opcode_LD_ADDR_HLI_A:
        return printf("%s", "LD (HL+), A");

    case Opcode_INC_HL:
        return printf("%s", "INC HL");

    case Opcode_INC_H:
        return printf("%s", "INC H");

    case Opcode_DEC_H:
        return printf("%s", "DEC H");

    case Opcode_LD_H_D8:
        return printf("%s", "LD H, d8");

    case Opcode_DAA:
        return printf("%s", "DAA");

    case Opcode_JR_Z_R8:
        return printf("%s", "JR Z, r8");

    case Opcode_ADD_HL_HL:
        return printf("%s", "ADD HL, HL");

    case Opcode_LD_A_ADDR_HLI:
        return printf("%s", "LD A, (HL+)");

    case Opcode_DEC_HL:
        return printf("%s", "DEC HL");

    case Opcode_INC_L:
        return printf("%s", "INC L");

    case Opcode_DEC_L:
        return printf("%s", "DEC L");

    case Opcode_LD_L_D8:
        return printf("%s", "LD L, d8");

    case Opcode_CPL:
        return printf("%s", "CPL");

    case Opcode_JR_NC_R8:
        return printf("%s", "JR NC, r8");

    case Opcode_LD_SP_D16:
        return printf("%s", "LD SP d16");

    case Opcode_LD_ADDR_HLD_A:
        return printf("%s", "LD (HL-), A");

    case Opcode_INC_SP:
        return printf("%s", "INC SP");

    case Opcode_INC_ADDR_HL:
        return printf("%s", "INC (HL)");

    case Opcode_DEC_ADDR_HL:
        return printf("%s", "DEC (HL)");

    case Opcode_LD_ADDR_HL_D8:
        return printf("%s", "LD (HL), d8");

    case Opcode_SCF:
        return printf("%s", "SCF");

    case Opcode_JR_C_R8:
        return printf("%s", "JR C, r8");

    case Opcode_ADD_HL_SP:
        return printf("%s", "ADD HL, SP");

    case Opcode_LD_A_ADDR_HLD:
        return printf("%s", "LD A, (HL-)");

    case Opcode_DEC_SP:
        return printf("%s", "DEC SP");

    case Opcode_INC_A:
        return printf("%s", "INC A");

    case Opcode_DEC_A:
        return printf("%s", "DEC A");

    case Opcode_LD_A_D8:
        return printf("%s", "LD A, d8");

    case Opcode_CCF:
        return printf("%s", "CCF");

    case Opcode_LD_B_B:
        return printf("%s", "LD B, B");

    case Opcode_LD_B_C:
        return printf("%s", "LD B, C");

    case Opcode_LD_B_D:
        return printf("%s", "LD B, D");

    case Opcode_LD_B_E:
        return printf("%s", "LD B, E");

    case Opcode_LD_B_H:
        return printf("%s", "LD B, H");

    case Opcode_LD_B_L:
        return printf("%s", "LD B, L");

    case Opcode_LD_B_ADDR_HL:
        return printf("%s", "LD B, (HL)");

    case Opcode_LD_B_A:
        return printf("%s", "LD B, A");

    case Opcode_LD_C_B:
        return printf("%s", "LD C, B");

    case Opcode_LD_C_C:
        return printf("%s", "LD C, C");

    case Opcode_LD_C_D:
        return printf("%s", "LD C, D");

    case Opcode_LD_C_E:
        return printf("%s", "LD C, E");

    case Opcode_LD_C_H:
        return printf("%s", "LD C, H");

    case Opcode_LD_C_L:
        return printf("%s", "LD C, L");

    case Opcode_LD_C_ADDR_HL:
        return printf("%s", "LD C, (HL)");

    case Opcode_LD_C_A:
        return printf("%s", "LD C, A");

    case Opcode_LD_D_B:
        return printf("%s", "LD D, B");

    case Opcode_LD_D_C:
        return printf("%s", "LD D, C");

    case Opcode_LD_D_D:
        return printf("%s", "LD D, D");

    case Opcode_LD_D_E:
        return printf("%s", "LD D, E");

    case Opcode_LD_D_H:
        return printf("%s", "LD D, H");

    case Opcode_LD_D_L:
        return printf("%s", "LD D, L");

    case Opcode_LD_D_ADDR_HL:
        return printf("%s", "LD D, (HL)");

    case Opcode_LD_D_A:
        return printf("%s", "LD D, A");

    case Opcode_LD_E_B:
        return printf("%s", "LD E, B");

    case Opcode_LD_E_C:
        return printf("%s", "LD E, C");

    case Opcode_LD_E_D:
        return printf("%s", "LD E, D");

    case Opcode_LD_E_E:
        return printf("%s", "LD E, E");

    case Opcode_LD_E_H:
        return printf("%s", "LD E, H");

    case Opcode_LD_E_L:
        return printf("%s", "LD E, L");

    case Opcode_LD_E_ADDR_HL:
        return printf("%s", "LD E, (HL)");

    case Opcode_LD_E_A:
        return printf("%s", "LD E, A");

    case Opcode_LD_H_B:
        return printf("%s", "LD H, B");

    case Opcode_LD_H_C:
        return printf("%s", "LD H, C");

    case Opcode_LD_H_D:
        return printf("%s", "LD H, D");

    case Opcode_LD_H_E:
        return printf("%s", "LD H, E");

    case Opcode_LD_H_H:
        return printf("%s", "LD H, E");

    case Opcode_LD_H_L:
        return printf("%s", "LD H, L");

    case Opcode_LD_H_ADDR_HL:
        return printf("%s", "LD H, (HL)");

    case Opcode_LD_H_A:
        return printf("%s", "LD H, A");

    case Opcode_LD_L_B:
        return printf("%s", "LD L, B");

    case Opcode_LD_L_C:
        return printf("%s", "LD L, C");

    case Opcode_LD_L_D:
        return printf("%s", "LD L, D");

    case Opcode_LD_L_E:
        return printf("%s", "LD L, E");

    case Opcode_LD_L_H:
        return printf("%s", "LD L, H");

    case Opcode_LD_L_L:
        return printf("%s", "LD L, L");

    case Opcode_LD_L_ADDR_HL:
        return printf("%s", "LD L, (HL)");

    case Opcode_LD_L_A:
        return printf("%s", "LD L, A");

    case Opcode_LD_ADDR_HL_B:
        return printf("%s", "LD (HL), B");

    case Opcode_LD_ADDR_HL_C:
        return printf("%s", "LD (HL), C");

    case Opcode_LD_ADDR_HL_D:
        return printf("%s", "LD (HL), D");

    case Opcode_LD_ADDR_HL_E:
        return printf("%s", "LD (HL), E");

    case Opcode_LD_ADDR_HL_H:
        return printf("%s", "LD (HL), H");

    case Opcode_LD_ADDR_HL_L:
        return printf("%s", "LD (HL), L");

    case Opcode_HALT:
        return printf("%s", "HALT");

    case Opcode_LD_ADDR_HL_A:
        return printf("%s", "LD (HL), A");

    case Opcode_LD_A_B:
        return printf("%s", "LD A, B");

    case Opcode_LD_A_C:
        return printf("%s", "LD A, C");

    case Opcode_LD_A_D:
        return printf("%s", "LD A, D");

    case Opcode_LD_A_E:
        return printf("%s", "LD A, E");

    case Opcode_LD_A_H:
        return printf("%s", "LD A, H");

    case Opcode_LD_A_L:
        return printf("%s", "LD A, L");

    case Opcode_LD_A_ADDR_HL:
        return printf("%s", "LD A, (HL)");

    case Opcode_LD_A_A:
        return printf("%s", "LD A, A");

    case Opcode_ADD_A_B:
        return printf("%s", "ADD A, B");

    case Opcode_ADD_A_C:
        return printf("%s", "ADD A, C");

    case Opcode_ADD_A_D:
        return printf("%s", "ADD A, D");

    case Opcode_ADD_A_E:
        return printf("%s", "ADD A, E");

    case Opcode_ADD_A_H:
        return printf("%s", "ADD A, H");

    case Opcode_ADD_A_L:
        return printf("%s", "ADD A, L");

    case Opcode_ADD_A_ADDR_HL:
        return printf("%s", "ADD A, (HL)");

    case Opcode_ADD_A_A:
        return printf("%s", "ADD A, A");

    case Opcode_ADC_A_B:
        return printf("%s", "ADC A, B");

    case Opcode_ADC_A_C:
        return printf("%s", "ADC A, C");

    case Opcode_ADC_A_D:
        return printf("%s", "ADC A, D");

    case Opcode_ADC_A_E:
        return printf("%s", "ADC A, E");

    case Opcode_ADC_A_H:
        return printf("%s", "ADC A, H");

    case Opcode_ADC_A_L:
        return printf("%s", "ADC A, L");

    case Opcode_ADC_A_ADDR_HL:
        return printf("%s", "ADC A, (HL)");

    case Opcode_ADC_A_A:
        return printf("%s", "ADC A, A");

    case Opcode_SUB_B:
        return printf("%s", "SUB B");

    case Opcode_SUB_C:
        return printf("%s", "SUB C");

    case Opcode_SUB_D:
        return printf("%s", "SUB D");

    case Opcode_SUB_E:
        return printf("%s", "SUB E");

    case Opcode_SUB_H:
        return printf("%s", "SUB H");

    case Opcode_SUB_L:
        return printf("%s", "SUB L");

    case Opcode_SUB_ADDR_HL:
        return printf("%s", "SUB (HL)");

    case Opcode_SUB_A:
        return printf("%s", "SUB A");

    case Opcode_SBC_A_B:
        return printf("%s", "SBC A, B");

    case Opcode_SBC_A_C:
        return printf("%s", "SBC A, C");

    case Opcode_SBC_A_D:
        return printf("%s", "SBC A, D");

    case Opcode_SBC_A_E:
        return printf("%s", "SBC A, E");

    case Opcode_SBC_A_H:
        return printf("%s", "SBC A, H");

    case Opcode_SBC_A_L:
        return printf("%s", "SBC A, L");

    case Opcode_SBC_A_ADDR_HL:
        return printf("%s", "SBC A, (HL)");

    case Opcode_SBC_A_A:
        return printf("%s", "SBC A, A");

    case Opcode_AND_B:
        return printf("%s", "AND B");

    case Opcode_AND_C:
        return printf("%s", "AND C");

    case Opcode_AND_D:
        return printf("%s", "AND D");

    case Opcode_AND_E:
        return printf("%s", "AND E");

    case Opcode_AND_H:
        return printf("%s", "AND H");

    case Opcode_AND_L:
        return printf("%s", "AND L");

    case Opcode_AND_ADDR_HL:
        return printf("%s", "AND (HL)");

    case Opcode_AND_A:
        return printf("%s", "AND A");

    case Opcode_XOR_B:
        return printf("%s", "XOR B");

    case Opcode_XOR_C:
        return printf("%s", "XOR C");

    case Opcode_XOR_D:
        return printf("%s", "XOR D");

    case Opcode_XOR_E:
        return printf("%s", "XOR E");

    case Opcode_XOR_H:
        return printf("%s", "XOR H");

    case Opcode_XOR_L:
        return printf("%s", "XOR L");

    case Opcode_XOR_ADDR_HL:
        return printf("%s", "XOR (HL)");

    case Opcode_XOR_A:
        return printf("%s", "XOR A");

    case Opcode_OR_B:
        return printf("%s", "OR B");

    case Opcode_OR_C:
        return printf("%s", "OR C");

    case Opcode_OR_D:
        return printf("%s", "OR D");

    case Opcode_OR_E:
        return printf("%s", "OR E");

    case Opcode_OR_H:
        return printf("%s", "OR H");

    case Opcode_OR_L:
        return printf("%s", "OR L");

    case Opcode_OR_ADDR_HL:
        return printf("%s", "OR (HL)");

    case Opcode_OR_A:
        return printf("%s", "OR A");

    case Opcode_CP_B:
        return printf("%s", "CP B");

    case Opcode_CP_C:
        return printf("%s", "CP C");

    case Opcode_CP_D:
        return printf("%s", "CP D");

    case Opcode_CP_E:
        return printf("%s", "CP E");

    case Opcode_CP_H:
        return printf("%s", "CP H");

    case Opcode_CP_L:
        return printf("%s", "CP L");

    case Opcode_CP_ADDR_HL:
        return printf("%s", "CP (HL)");

    case Opcode_CP_A:
        return printf("%s", "CP A");

    case Opcode_RET_NZ:
        return printf("%s", "RET NZ");

    case Opcode_POP_BC:
        return printf("%s", "POP BC");

    case Opcode_JP_NZ_A16:
        return printf("%s", "JP NZ, a16");

    case Opcode_JP_A16:
        return printf("%s", "JP a16");

    case Opcode_CALL_NZ_A16:
        return printf("%s", "CALL NZ, a16");

    case Opcode_PUSH_BC:
        return printf("%s", "PUSH BC");

    case Opcode_ADD_A_D8:
        return printf("%s", "ADD A, d8");

    case Opcode_RST_00H:
        return printf("%s", "RST 00h");

    case Opcode_RET_Z:
        return printf("%s", "RET Z");

    case Opcode_RET:
        return printf("%s", "RET");

    case Opcode_JP_Z_A16:
        return printf("%s", "JP Z, a16");

    case Opcode_PREFIX_CB:
        return printf("%s", "PREFIX CB");

    case Opcode_CALL_Z_A16:
        return printf("%s", "CALL Z");

    case Opcode_CALL_A16:
        return printf("%s", "CALL");

    case Opcode_ADC_A_D8:
        return printf("%s", "ADC A, d8");

    case Opcode_RST_08H:
        return printf("%s", "RST 08h");

    case Opcode_RET_NC:
        return printf("%s", "RET NC");

    case Opcode_POP_DE:
        return printf("%s", "POP DE");

    case Opcode_JP_NC_A16:
        return printf("%s", "JP NC, a16");

    case Opcode_CALL_NC_A16:
        return printf("%s", "CALL NC, a16");

    case Opcode_PUSH_DE:
        return printf("%s", "PUSH DE");

    case Opcode_SUB_D8:
        return printf("%s", "SUB d8");

    case Opcode_RST_10H:
        return printf("%s", "RST 10h");

    case Opcode_RET_C:
        return printf("%s", "RET C");

    case Opcode_RETI:
        return printf("%s", "RETI");

    case Opcode_JP_C_A16:
        return printf("%s", "JP C, a16");

    case Opcode_CALL_C_A16:
        return printf("%s", "CALL C, a16");

    case Opcode_SBC_A_D8:
        return printf("%s", "SBC A, d8");

    case Opcode_RST_18H:
        return printf("%s", "RST 18h");

    case Opcode_LDH_ADDR_A8_A:
        return printf("%s", "LD (a8), A");

    case Opcode_POP_HL:
        return printf("%s", "POP HL");

    case Opcode_LD_ADDR_C_A:
        return printf("%s", "LD (C), A");

    case Opcode_PUSH_HL:
        return printf("%s", "PUSH HL");

    case Opcode_AND_D8:
        return printf("%s", "AND d8");

    case Opcode_RST_20H:
        return printf("%s", "RST 20h");

    case Opcode_ADD_SP_R8:
        return printf("%s", "ADD SP, r8");

    case Opcode_JP_ADDR_HL:
        return printf("%s", "JP (HL)");

    case Opcode_LD_ADDR_A16_A:
        return printf("%s", "LD (a16), A");

    case Opcode_XOR_D8:
        return printf("%s", "XOR d8");

    case Opcode_RST_28H:
        return printf("%s", "RST 20h");

    case Opcode_LDH_A_ADDR_A8:
        return printf("%s", "LDH A, (a8)");

    case Opcode_POP_AF:
        return printf("%s", "PP AF");

    case Opcode_LD_A_ADDR_C:
        return printf("%s", "LD A, (C)");

    case Opcode_DI:
        return printf("%s", "DI");

    case Opcode_PUSH_AF:
        return printf("%s", "PUSH AF");

    case Opcode_OR_D8:
        return printf("%s", "OR d8");

    case Opcode_RST_30H:
        return printf("%s", "RST 30h");

    case Opcode_LD_HL_SPR8:
        return printf("%s", "LD HL, SP+r8");

    case Opcode_LD_SP_HL:
        return printf("%s", "LD SP, HL");

    case Opcode_LD_A_ADDR_A16:
        return printf("%s", "LD A, (a16)");

    case Opcode_EI:
        return printf("%s", "EI");

    case Opcode_CP_D8:
        return printf("%s", "CP d8");

    case Opcode_RST_38H:
        return printf("%s", "RST 38h");

    default:
        return printf("%s", "Unknown opcode");
    }
}