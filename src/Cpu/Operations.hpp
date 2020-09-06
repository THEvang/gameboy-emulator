#pragma once

#include <cstdint>

class Instruction;

Instruction NOP();
Instruction STOP();
Instruction HALT();
Instruction RST(uint8_t address); 
Instruction DI();
Instruction EI();

Instruction JR();
Instruction JR_NZ();
Instruction JR_Z();
Instruction JR_NC();
Instruction JR_C();

Instruction RET();
Instruction RET_Z();
Instruction RET_NZ();
Instruction RET_C();
Instruction RET_NC();
Instruction RETI();

Instruction JUMP();
Instruction JUMP_NZ();
Instruction JUMP_Z();
Instruction JUMP_NC();
Instruction JUMP_C();
Instruction JUMP_ADDR_HL();

Instruction CALL();
Instruction CALL_NZ();
Instruction CALL_Z();
Instruction CALL_NC();
Instruction CALL_C();

Instruction LD_A_D8();
Instruction LD_A_A();
Instruction LD_A_B();
Instruction LD_A_C();
Instruction LD_A_D();
Instruction LD_A_E();
Instruction LD_A_H();
Instruction LD_A_L();
Instruction LD_A_ADDR_BC();
Instruction LD_A_ADDR_DE();
Instruction LD_A_ADDR_HL();
Instruction LD_A_ADDR_C();
Instruction LD_A_ADDR_A16();
Instruction LD_ADDR_A16_SP();

Instruction LDI_ADDR_HL_A();
Instruction LDI_A_ADDR_HL();

Instruction LD_ADDR_BC_A();
Instruction LD_ADDR_DE_A();

Instruction LD_B_D8();
Instruction LD_B_A();
Instruction LD_B_B();
Instruction LD_B_C();
Instruction LD_B_D();
Instruction LD_B_E();
Instruction LD_B_H();
Instruction LD_B_L();
Instruction LD_B_ADDR_HL();

Instruction LD_C_D8();
Instruction LD_C_A();
Instruction LD_C_B();
Instruction LD_C_C();
Instruction LD_C_D();
Instruction LD_C_E();
Instruction LD_C_H();
Instruction LD_C_L();
Instruction LD_C_ADDR_HL();

Instruction LD_D_D8();
Instruction LD_D_A();
Instruction LD_D_B();
Instruction LD_D_C();
Instruction LD_D_D();
Instruction LD_D_E();
Instruction LD_D_H();
Instruction LD_D_L();
Instruction LD_D_ADDR_HL();

Instruction LD_E_D8();
Instruction LD_E_A();
Instruction LD_E_B();
Instruction LD_E_C();
Instruction LD_E_D();
Instruction LD_E_E();
Instruction LD_E_H();
Instruction LD_E_L();
Instruction LD_E_ADDR_HL();

Instruction LD_H_D8();
Instruction LD_H_A();
Instruction LD_H_B();
Instruction LD_H_C();
Instruction LD_H_D();
Instruction LD_H_E();
Instruction LD_H_H();
Instruction LD_H_L();
Instruction LD_H_ADDR_HL();

Instruction LD_L_D8();
Instruction LD_L_A();
Instruction LD_L_B();
Instruction LD_L_C();
Instruction LD_L_D();
Instruction LD_L_E();
Instruction LD_L_H();
Instruction LD_L_L();
Instruction LD_L_ADDR_HL();

Instruction LD_ADDR_HL_A();
Instruction LD_ADDR_HL_B();
Instruction LD_ADDR_HL_C();
Instruction LD_ADDR_HL_D();
Instruction LD_ADDR_HL_E();
Instruction LD_ADDR_HL_H();
Instruction LD_ADDR_HL_L();
Instruction LD_ADDR_HL_D8();
Instruction LD_ADDR_HL_ADDR_HL();
Instruction LD_ADDR_A16_A();

Instruction LD_BC_D16();
Instruction LD_DE_D16();
Instruction LD_HL_D16();
Instruction LD_HL_SPR8();

Instruction LD_SP_D16();
Instruction LD_SP_HL();

Instruction ADD_A_D8();
Instruction ADD_A_A();
Instruction ADD_A_B();
Instruction ADD_A_C();
Instruction ADD_A_D();
Instruction ADD_A_E();
Instruction ADD_A_H();
Instruction ADD_A_L();
Instruction ADD_A_ADDR_HL();

Instruction ADD_HL_BC();
Instruction ADD_HL_HL();
Instruction ADD_HL_DE();
Instruction ADD_HL_SP();

Instruction SUB_D8();
Instruction SUB_A();
Instruction SUB_B();
Instruction SUB_C();
Instruction SUB_D();
Instruction SUB_E();
Instruction SUB_H();
Instruction SUB_L();
Instruction SUB_ADDR_HL();

Instruction INC_A();
Instruction INC_B();
Instruction INC_C();
Instruction INC_D();
Instruction INC_E();
Instruction INC_H();
Instruction INC_L();
Instruction INC_BC();
Instruction INC_DE();
Instruction INC_HL();
Instruction INC_ADDR_HL();
Instruction INC_SP();


Instruction DEC_A();
Instruction DEC_B();
Instruction DEC_C();
Instruction DEC_D();
Instruction DEC_E();
Instruction DEC_H();
Instruction DEC_L();
Instruction DEC_BC();
Instruction DEC_DE();
Instruction DEC_HL();
Instruction DEC_ADDR_HL();
Instruction DEC_SP();

Instruction SCF();
Instruction CCF();

Instruction RRCA();
Instruction RRA();

Instruction RLA();
Instruction RLCA();

Instruction DAA();

Instruction ADD_SP_R8();

Instruction AND_D8();
Instruction AND_A();
Instruction AND_B();
Instruction AND_C();
Instruction AND_D();
Instruction AND_E();
Instruction AND_H();
Instruction AND_L();
Instruction AND_ADDR_HL();

Instruction XOR_D8();
Instruction XOR_A();
Instruction XOR_B();
Instruction XOR_C();
Instruction XOR_D();
Instruction XOR_E();
Instruction XOR_H();
Instruction XOR_L();
Instruction XOR_ADDR_HL();

Instruction OR_D8();
Instruction OR_A();
Instruction OR_B();
Instruction OR_C();
Instruction OR_D();
Instruction OR_E();
Instruction OR_H();
Instruction OR_L();
Instruction OR_ADDR_HL();

Instruction CP_D8();
Instruction CP_A();
Instruction CP_B();
Instruction CP_C();
Instruction CP_D();
Instruction CP_E();
Instruction CP_H();
Instruction CP_L();
Instruction CP_ADDR_HL();

Instruction PUSH_AF();
Instruction PUSH_BC();
Instruction PUSH_DE();
Instruction PUSH_HL();

Instruction POP_AF();
Instruction POP_BC();
Instruction POP_DE();
Instruction POP_HL();

Instruction ADC_A_D8();
Instruction ADC_A_A();
Instruction ADC_A_B();
Instruction ADC_A_C();
Instruction ADC_A_D();
Instruction ADC_A_E();
Instruction ADC_A_H();
Instruction ADC_A_L();
Instruction ADC_A_ADDR_HL();

Instruction LDH_ADDR_A8_A();
Instruction LDH_A_ADDR_A8();
Instruction LD_ADDR_C_A();

Instruction SBC_A_D8();
Instruction SBC_A_A();
Instruction SBC_A_B();
Instruction SBC_A_C();
Instruction SBC_A_D();
Instruction SBC_A_E();
Instruction SBC_A_H();
Instruction SBC_A_L();
Instruction SBC_A_ADDR_HL();

Instruction PREFIX_CB();

Instruction LD_ADDR_HLD_A();
Instruction LD_A_ADDR_HLD();

Instruction CPL();