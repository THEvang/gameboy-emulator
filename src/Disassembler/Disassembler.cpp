#include "Disassembler/Disassembler.hpp"

Instruction disassemble(Opcode const& opcode) {

    Instruction instruction;

    switch (opcode) {
    case Opcode::NOP:
        return {opcode, "NOP", 4};

    case Opcode::LD_BC_D16:
        return {opcode, "LD BC, d16", 12};

    case Opcode::LD_ADDR_BC_A:
        return {opcode, "LD (BC), A", 8};

    case Opcode::INC_BC:
        return {opcode, "INC BC", 4};

    case Opcode::INC_B:
        return {opcode, "INC B", 4};

    case Opcode::DEC_B:
        return {opcode, "DEC B", 4};

    case Opcode::LD_B_D8:
        return {opcode, "LD B, d8", 9};

    case Opcode::RLCA:
        return {opcode, "RLCA", 4};

    case Opcode::LD_ADDR_A16_SP:
        return {opcode, "LD (a16), SP", 20};

    case Opcode::ADD_HL_BC:
        return {opcode, "ADD HL, BC", 8};

    case Opcode::LD_A_ADDR_BC:
        return {opcode, "LD A, (BC)", 8};

    case Opcode::DEC_BC:
        return {opcode, "DEC BC", 8};

    case Opcode::INC_C:
        return {opcode, "INC C", 4};

    case Opcode::DEC_C:
        return {opcode, "DEC C", 4};

    case Opcode::LD_C_D8:
        return {opcode, "LD C d8", 8};

    case Opcode::RRCA:
        return {opcode, "RRCA", 4};

    case Opcode::STOP:
        return {opcode, "STOP", 4};

    case Opcode::LD_DE_D16:
        return {opcode, "LD DE, d16", 12};

    case Opcode::LD_ADDR_DE_A:
        return {opcode, "LD (DE), A", 8};

    case Opcode::INC_DE:
        return {opcode, "INC DE", 8};

    case Opcode::INC_D:
        return {opcode, "INC D", 4};

    case Opcode::DEC_D:
        return {opcode, "DEC D", 4};

    case Opcode::LD_D_D8:
        return {opcode, "LD D, d8", 8};

    case Opcode::RLA:
        return {opcode, "RLA", 4};

    case Opcode::JR_R8:
        return {opcode, "JR r8", 12};

    case Opcode::ADD_HL_DE:
        return {opcode, "ADD HL DE", 8};

    case Opcode::LD_A_ADDR_DE:
        return {opcode, "LD A, (DE)", 8};

    case Opcode::DEC_DE:
        return {opcode, "DEC DE", 8};

    case Opcode::INC_E:
        return {opcode, "INC E", 4};

    case Opcode::DEC_E:
        return {opcode, "DEC E", 4};

    case Opcode::LD_E_D8:
        return {opcode, "LD E, d8", 8};

    case Opcode::RRA:
        return {opcode, "RRA", 4};

    case Opcode::JR_NZ_R8:
        return {opcode, "JR NZ, r8", 12};

    case Opcode::LD_HL_D16:
        return {opcode, "LD HL, d16", 12};

    case Opcode::LD_ADDR_HLI_A:
        return {opcode, "LD (HL+), A", 8};

    case Opcode::INC_HL:
        return {opcode, "INC HL", 8};

    case Opcode::INC_H:
        return {opcode, "INC H", 4};

    case Opcode::DEC_H:
        return {opcode, "DEC H", 4};

    case Opcode::LD_H_D8:
        return {opcode, "LD H, d8", 8};

    case Opcode::DAA:
        return {opcode, "DAA", 4};

    case Opcode::JR_Z_R8:
        return {opcode, "JR Z, r8", 12};

    case Opcode::ADD_HL_HL:
        return {opcode, "ADD HL, HL", 8};

    case Opcode::LD_A_ADDR_HLI:
        return {opcode, "LD A, (HL+)", 8};

    case Opcode::DEC_HL:
        return {opcode, "DEC HL", 8};

    case Opcode::INC_L:
        return {opcode, "INC L", 4};

    case Opcode::DEC_L:
        return {opcode, "DEC L", 1};

    case Opcode::LD_L_D8:
        return {opcode, "LD L, d8", 8};

    case Opcode::CPL:
        return {opcode, "CPL", 4};

    case Opcode::JR_NC_R8:
        return {opcode, "JR NC, r8", 12};

    case Opcode::LD_SP_D16:
        return {opcode, "LD SP d16", 12};

    case Opcode::LD_ADDR_HLD_A:
        return {opcode, "LD (HL-), A", 8};

    case Opcode::INC_SP:
        return {opcode, "INC SP", 8};

    case Opcode::INC_ADDR_HL:
        return {opcode, "INC (HL)", 12};

    case Opcode::DEC_ADDR_HL:
        return {opcode, "DEC (HL)", 12};

    case Opcode::LD_ADDR_HL_D8:
        return {opcode, "LD (HL), d8", 12};

    case Opcode::SCF:
        return {opcode, "SCF", 4};

    case Opcode::JR_C_R8:
        return {opcode, "JR C, r8", 12};

    case Opcode::ADD_HL_SP:
        return {opcode, "ADD HL, SP", 8};

    case Opcode::LD_A_ADDR_HLD:
        return {opcode, "LD A, (HL-)", 8};

    case Opcode::DEC_SP:
        return {opcode, "DEC SP", 8};

    case Opcode::INC_A:
        return {opcode, "INC A", 4};

    case Opcode::DEC_A:
        return {opcode, "DEC A", 4};;

    case Opcode::LD_A_D8:
        return {opcode, "LD A, d8", 8};

    case Opcode::CCF:
        return {opcode, "CCF", 4};

    case Opcode::LD_B_B:
        return {opcode, "LD B, B", 4};

    case Opcode::LD_B_C:
        return {opcode, "LD B, C", 4};

    case Opcode::LD_B_D:
        return {opcode, "LD B, D", 4};

    case Opcode::LD_B_E:
        return {opcode, "LD B, E", 4};

    case Opcode::LD_B_H:
        return {opcode, "LD B, H", 4};

    case Opcode::LD_B_L:
        return {opcode, "LD B, L", 4};

    case Opcode::LD_B_ADDR_HL:
        return {opcode, "LD B, (HL)", 8};

    case Opcode::LD_B_A:
        return {opcode, "LD B, A", 4};

    case Opcode::LD_C_B:
        return {opcode, "LD C, B", 4};

    case Opcode::LD_C_C:
        return {opcode, "LD C, C", 4};

    case Opcode::LD_C_D:
        return {opcode, "LD C, D", 4};

    case Opcode::LD_C_E:
        return {opcode, "LD C, E", 4};

    case Opcode::LD_C_H:
        return {opcode, "LD C, H", 4};

    case Opcode::LD_C_L:
        return {opcode, "LD C, L", 4};

    case Opcode::LD_C_ADDR_HL:
        return {opcode, "LD C, (HL)", 8};

    case Opcode::LD_C_A:
        return {opcode, "LD C, A", 4};

    case Opcode::LD_D_B:
        return {opcode, "LD D, B", 4};

    case Opcode::LD_D_C:
        return {opcode, "LD D, C", 4};

    case Opcode::LD_D_D:
        return {opcode, "LD D, D", 4};

    case Opcode::LD_D_E:
        return {opcode, "LD D, E", 4};

    case Opcode::LD_D_H:
        return {opcode, "LD D, H", 4};

    case Opcode::LD_D_L:
        return {opcode, "LD D, L", 4};

    case Opcode::LD_D_ADDR_HL:
        return {opcode, "LD D, (HL)", 8};

    case Opcode::LD_D_A:
        return {opcode, "LD D, A", 4};

    case Opcode::LD_E_B:
        return {opcode, "LD E, B", 4};

    case Opcode::LD_E_C:
        return {opcode, "LD E, C", 4};

    case Opcode::LD_E_D:
        return {opcode, "LD E, D", 4};

    case Opcode::LD_E_E:
        return {opcode, "LD E, E", 4};

    case Opcode::LD_E_H:
        return {opcode, "LD E, H", 4};

    case Opcode::LD_E_L:
        return {opcode, "LD E, L", 4};

    case Opcode::LD_E_ADDR_HL:
        return {opcode, "LD E, (HL)", 8};

    case Opcode::LD_E_A:
        return {opcode, "LD E, A", 4};

    case Opcode::LD_H_B:
        return {opcode, "LD H, B", 4};

    case Opcode::LD_H_C:
        return {opcode, "LD H, C", 4};

    case Opcode::LD_H_D:
        return {opcode, "LD H, D", 4};

    case Opcode::LD_H_E:
        return {opcode, "LD H, E", 4};

    case Opcode::LD_H_H:
        return {opcode, "LD H, E", 4};

    case Opcode::LD_H_L:
        return {opcode, "LD H, L", 4};

    case Opcode::LD_H_ADDR_HL:
        return {opcode, "LD H, (HL)", 8};

    case Opcode::LD_H_A:
        return {opcode, "LD H, A", 4};

    case Opcode::LD_L_B:
        return {opcode, "LD L, B", 4};

    case Opcode::LD_L_C:
        return {opcode, "LD L, C", 4};

    case Opcode::LD_L_D:
        return {opcode, "LD L, D", 4};

    case Opcode::LD_L_E:
        return {opcode, "LD L, E", 4};

    case Opcode::LD_L_H:
        return {opcode, "LD L, H", 4};

    case Opcode::LD_L_L:
        return {opcode, "LD L, L", 4};

    case Opcode::LD_L_ADDR_HL:
        return {opcode, "LD L, (HL)", 8};

    case Opcode::LD_L_A:
        return {opcode, "LD L, A", 4};

    case Opcode::LD_ADDR_HL_B:
        return {opcode, "LD (HL), B", 8};

    case Opcode::LD_ADDR_HL_C:
        return {opcode, "LD (HL), C", 8};

    case Opcode::LD_ADDR_HL_D:
        return {opcode, "LD (HL), D", 8};

    case Opcode::LD_ADDR_HL_E:
        return {opcode, "LD (HL), E", 8};

    case Opcode::LD_ADDR_HL_H:
        return {opcode, "LD (HL), H", 8};

    case Opcode::LD_ADDR_HL_L:
        return {opcode, "LD (HL), L", 8};

    case Opcode::HALT:
        return {opcode, "HALT", 4};

    case Opcode::LD_ADDR_HL_A:
        return {opcode, "LD (HL), A", 8};

    case Opcode::LD_A_B:
        return {opcode, "LD A, B", 4};

    case Opcode::LD_A_C:
        return {opcode, "LD A, C", 4};

    case Opcode::LD_A_D:
        return {opcode, "LD A, D", 4};

    case Opcode::LD_A_E:
        return {opcode, "LD A, E", 4};

    case Opcode::LD_A_H:
        return {opcode, "LD A, H", 4};

    case Opcode::LD_A_L:
        return {opcode, "LD A, L", 4};

    case Opcode::LD_A_ADDR_HL:
        return {opcode, "LD A, (HL)", 8};

    case Opcode::LD_A_A:
        return {opcode, "LD A, A", 4};

    case Opcode::ADD_A_B:
        return {opcode, "ADD A, B", 4};

    case Opcode::ADD_A_C:
        return {opcode, "ADD A, C", 4};

    case Opcode::ADD_A_D:
        return {opcode, "ADD A, D", 4};

    case Opcode::ADD_A_E:
        return {opcode, "ADD A, E", 4};

    case Opcode::ADD_A_H:
        return {opcode, "ADD A, H", 4};

    case Opcode::ADD_A_L:
        return {opcode, "ADD A, L", 4};

    case Opcode::ADD_A_ADDR_HL:
        return {opcode, "ADD A, (HL)", 4};

    case Opcode::ADD_A_A:
        return {opcode, "ADD A, A", 4};

    case Opcode::ADC_A_B:
        return {opcode, "ADC A, B", 4};

    case Opcode::ADC_A_C:
        return {opcode, "ADC A, C", 4};

    case Opcode::ADC_A_D:
        return {opcode, "ADC A, D", 4};

    case Opcode::ADC_A_E:
        return {opcode, "ADC A, E", 4};

    case Opcode::ADC_A_H:
        return {opcode, "ADC A, H", 4};

    case Opcode::ADC_A_L:
        return {opcode, "ADC A, L", 4};

    case Opcode::ADC_A_ADDR_HL:
        return {opcode, "ADC A, (HL)", 8};

    case Opcode::ADC_A_A:
        return {opcode, "ADC A, A", 4};

    case Opcode::SUB_B:
        return {opcode, "SUB B", 4};

    case Opcode::SUB_C:
        return {opcode, "SUB C", 4};

    case Opcode::SUB_D:
        return {opcode, "SUB D", 4};

    case Opcode::SUB_E:
        return {opcode, "SUB E", 4};

    case Opcode::SUB_H:
        return {opcode, "SUB H", 4};

    case Opcode::SUB_L:
        return {opcode, "SUB L", 4};

    case Opcode::SUB_ADDR_HL:
        return {opcode, "SUB (HL)", 8};

    case Opcode::SUB_A:
        return {opcode, "SUB A", 4};

    case Opcode::SBC_A_B:
        return {opcode, "SBC A, B", 4};

    case Opcode::SBC_A_C:
        return {opcode, "SBC A, C", 4};

    case Opcode::SBC_A_D:
        return {opcode, "SBC A, D", 4};

    case Opcode::SBC_A_E:
        return {opcode, "SBC A, E", 4};

    case Opcode::SBC_A_H:
        return {opcode, "SBC A, H", 4};

    case Opcode::SBC_A_L:
        return {opcode, "SBC A, L", 4};

    case Opcode::SBC_A_ADDR_HL:
        return {opcode, "SBC A, (HL)", 8};

    case Opcode::SBC_A_A:
        return {opcode, "SBC A, A", 4};

    case Opcode::AND_B:
        return {opcode, "AND B", 4};

    case Opcode::AND_C:
        return {opcode, "AND C", 4};

    case Opcode::AND_D:
        return {opcode, "AND D", 4};

    case Opcode::AND_E:
        return {opcode, "AND E", 4};

    case Opcode::AND_H:
        return {opcode, "AND H", 4};

    case Opcode::AND_L:
        return {opcode, "AND L", 4};

    case Opcode::AND_ADDR_HL:
        return {opcode, "AND (HL)", 8};

    case Opcode::AND_A:
        return {opcode, "AND A", 4};

    case Opcode::XOR_B:
        return {opcode, "XOR B", 4};

    case Opcode::XOR_C:
        return {opcode, "XOR C", 4};

    case Opcode::XOR_D:
        return {opcode, "XOR D", 4};

    case Opcode::XOR_E:
        return {opcode, "XOR E", 4};

    case Opcode::XOR_H:
        return {opcode, "XOR H", 4};

    case Opcode::XOR_L:
        return {opcode, "XOR L", 4};

    case Opcode::XOR_ADDR_HL:
        return {opcode, "XOR (HL)", 8};

    case Opcode::XOR_A:
        return {opcode, "XOR A", 4};

    case Opcode::OR_B:
        return {opcode, "OR B", 4};

    case Opcode::OR_C:
        return {opcode, "OR C", 4};

    case Opcode::OR_D:
        return {opcode, "OR D", 4};

    case Opcode::OR_E:
        return {opcode, "OR E", 4};

    case Opcode::OR_H:
        return {opcode, "OR H", 4};

    case Opcode::OR_L:
        return {opcode, "OR L", 4};

    case Opcode::OR_ADDR_HL:
        return {opcode, "OR (HL)", 8};

    case Opcode::OR_A:
        return {opcode, "OR A", 4};

    case Opcode::CP_B:
        return {opcode, "CP B", 4};

    case Opcode::CP_C:
        return {opcode, "CP C", 4};

    case Opcode::CP_D:
        return {opcode, "CP D", 4};

    case Opcode::CP_E:
        return {opcode, "CP E", 4};

    case Opcode::CP_H:
        return {opcode, "CP H", 4};

    case Opcode::CP_L:
        return {opcode, "CP L", 4};

    case Opcode::CP_ADDR_HL:
        return {opcode, "CP (HL)", 8};

    case Opcode::CP_A:
        return {opcode, "CP A", 4};

    case Opcode::RET_NZ:
        return {opcode, "RET NZ", 20};

    case Opcode::POP_BC:
        return {opcode, "POP BC", 12};

    case Opcode::JP_NZ_A16:
        return {opcode, "JP NZ, a16", 16};

    case Opcode::JP_A16:
        return {opcode, "JP a16", 16};

    case Opcode::CALL_NZ_A16:
        return {opcode, "CALL NZ, a16", 24};

    case Opcode::PUSH_BC:
        return {opcode, "PUSH BC", 16};

    case Opcode::ADD_A_D8:
        return {opcode, "ADD A, d8", 8};

    case Opcode::RST_00H:
        return {opcode, "RST 00h", 16};

    case Opcode::RET_Z:
        return {opcode, "RET Z", 20};

    case Opcode::RET:
        return {opcode, "RET", 16};

    case Opcode::JP_Z_A16:
        return {opcode, "JP Z, a16", 24};

    case Opcode::PREFIX_CB:
        return {opcode, "PREFIX CB", 4};

    case Opcode::CALL_Z_A16:
        return {opcode, "CALL Z", 24};

    case Opcode::CALL_A16:
        return {opcode, "CALL", 16};;

    case Opcode::ADC_A_D8:
        return {opcode, "ADC A, d8", 8};

    case Opcode::RST_08H:
        return {opcode, "RST 08h", 16};

    case Opcode::RET_NC:
        return {opcode, "RET NC", 20};

    case Opcode::POP_DE:
        return {opcode, "POP DE", 12};

    case Opcode::JP_NC_A16:
        return {opcode, "JP NC, a16", 16};

    case Opcode::CALL_NC_A16:
        return {opcode, "CALL NC, a16", 24};

    case Opcode::PUSH_DE:
        return {opcode, "PUSH DE", 16};

    case Opcode::SUB_D8:
        return {opcode, "SUB d8", 8};

    case Opcode::RST_10H:
        return {opcode, "RST 10h", 16};

    case Opcode::RET_C:
        return {opcode, "RET C", 20};

    case Opcode::RETI:
        return {opcode, "RETI", 16};

    case Opcode::JP_C_A16:
        return {opcode, "JP C, a16", 16};

    case Opcode::CALL_C_A16:
        return {opcode, "CALL C, a16", 24};

    case Opcode::SBC_A_D8:
        return {opcode, "SBC A, d8", 8};

    case Opcode::RST_18H:
        return {opcode, "RST 18h", 16};

    case Opcode::LDH_ADDR_A8_A:
        return {opcode, "LD (a8), A", 12};

    case Opcode::POP_HL:
        return {opcode, "POP HL", 12};

    case Opcode::LD_ADDR_C_A:
        return {opcode, "LD (C), A", 8};

    case Opcode::PUSH_HL:
        return {opcode, "PUSH HL", 16};

    case Opcode::AND_D8:
        return {opcode, "AND d8", 8};

    case Opcode::RST_20H:
        return {opcode, "RST 20h", 16};

    case Opcode::ADD_SP_R8:
        return {opcode, "ADD SP, r8", 16};

    case Opcode::JP_ADDR_HL:
        return {opcode, "JP (HL)", 4};

    case Opcode::LD_ADDR_A16_A:
        return {opcode, "LD (a16), A", 16};

    case Opcode::XOR_D8:
        return {opcode, "XOR d8", 8};

    case Opcode::RST_28H:
        return {opcode, "RST 20h", 16};

    case Opcode::LDH_A_ADDR_A8:
        return {opcode, "LDH A, (a8)", 12};

    case Opcode::POP_AF:
        return {opcode, "PP AF", 12};;

    case Opcode::LD_A_ADDR_C:
        return {opcode, "LD A, (C)", 8};

    case Opcode::DI:
        return {opcode, "DI", 4};

    case Opcode::PUSH_AF:
        return {opcode, "PUSH AF", 16};

    case Opcode::OR_D8:
        return {opcode, "OR d8", 8};

    case Opcode::RST_30H:
        return {opcode, "RST 30h", 16};

    case Opcode::LD_HL_SPR8:
        return {opcode, "LD HL, SP+r8", 12};

    case Opcode::LD_SP_HL:
        return {opcode, "LD SP, HL", 8};

    case Opcode::LD_A_ADDR_A16:
        return {opcode, "LD A, (a16)", 16};

    case Opcode::EI:
        return {opcode, "EI", 4};

    case Opcode::CP_D8:
        return {opcode, "CP d8", 8};

    case Opcode::RST_38H:
        return {opcode, "RST 38h", 16};

    default:
        return {opcode, "Unknown opcode", 4};
    }
}