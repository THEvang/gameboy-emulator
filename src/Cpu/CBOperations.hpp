#pragma once

#include "Cpu/Cpu.hpp"

struct Instruction;

Instruction RLC_R(Cpu::Register);
Instruction RLC_ADDR_HL();

Instruction RRC_R(Cpu::Register);
Instruction RRC_ADDR_HL();

Instruction SRL_R(Cpu::Register);
Instruction SRL_ADDR_HL();

Instruction RL_R(Cpu::Register);
Instruction RL_ADDR_HL();

Instruction RR_R(Cpu::Register);
Instruction RR_ADDR_HL();

Instruction SLA_R(Cpu::Register);
Instruction SLA_ADDR_HL();

Instruction SLA_R(Cpu::Register);
Instruction SLA_ADDR_HL();

Instruction SRA_R(Cpu::Register);
Instruction SRA_ADDR_HL();

Instruction SWAP_R(Cpu::Register);
Instruction SWAP_ADDR_HL();

Instruction BIT_R(Cpu::Register, int);
Instruction SET_R(Cpu::Register, int);
Instruction RES_R(Cpu::Register, int);