#pragma once

#include <cstdint>
#include "Cpu/Cpu.hpp"

struct Instruction;

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

Instruction LD_R_D8(Cpu::Register);
Instruction LD_R_R(Cpu::Register, Cpu::Register);
Instruction LD_R_ADDR_HL(Cpu::Register);
Instruction LD_ADDR_HL_R(Cpu::Register);

Instruction LD_A_ADDR_RR(std::pair<Cpu::Register, Cpu::Register>);
Instruction LD_A_ADDR_C();
Instruction LD_A_ADDR_A16();
Instruction LD_ADDR_A16_SP();

Instruction LDI_ADDR_HL_A();
Instruction LDI_A_ADDR_HL();

Instruction LD_ADDR_RR_A(std::pair<Cpu::Register, Cpu::Register>);

Instruction LD_ADDR_HL_D8();
Instruction LD_ADDR_HL_ADDR_HL();
Instruction LD_ADDR_A16_A();

Instruction LD_RR_D16(std::pair<Cpu::Register, Cpu::Register>);
Instruction LD_HL_SPR8();

Instruction LD_SP_D16();
Instruction LD_SP_HL();

Instruction ADD_D8();
Instruction ADD_R(Cpu::Register);
Instruction ADD_ADDR_HL();
Instruction ADD_HL_RR(std::pair<Cpu::Register, Cpu::Register>);
Instruction ADD_HL_SP();

Instruction SUB_D8();
Instruction SUB_R(Cpu::Register);
Instruction SUB_ADDR_HL();

Instruction INC_R(Cpu::Register);
Instruction INC_RR(std::pair<Cpu::Register, Cpu::Register>);
Instruction INC_ADDR_HL();
Instruction INC_SP();

Instruction DEC_R(Cpu::Register);
Instruction DEC_RR(std::pair<Cpu::Register, Cpu::Register>);
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
Instruction AND_R(Cpu::Register);
Instruction AND_ADDR_HL();

Instruction XOR_D8();
Instruction XOR_R(Cpu::Register);
Instruction XOR_ADDR_HL();

Instruction OR_D8();
Instruction OR_R(Cpu::Register);
Instruction OR_ADDR_HL();

Instruction CP_D8();
Instruction CP_R(Cpu::Register);
Instruction CP_ADDR_HL();

Instruction PUSH_RR(std::pair<Cpu::Register, Cpu::Register>);

Instruction POP_AF();
Instruction POP_RR(std::pair<Cpu::Register, Cpu::Register>);

Instruction ADC_D8();
Instruction ADC_R(Cpu::Register);
Instruction ADC_ADDR_HL();

Instruction LDH_ADDR_A8_A();
Instruction LDH_A_ADDR_A8();
Instruction LD_ADDR_C_A();
Instruction SBC_D8();
Instruction SBC_R(Cpu::Register);
Instruction SBC_A_ADDR_HL();

Instruction PREFIX_CB();

Instruction LD_ADDR_HLD_A();
Instruction LD_A_ADDR_HLD();

Instruction CPL();