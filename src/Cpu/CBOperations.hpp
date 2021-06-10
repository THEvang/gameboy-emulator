#pragma once

#include "Cpu/Cpu.h"

struct Instruction;

Instruction RLC_R(Cpu_Register);
Instruction RLC_ADDR_HL();

Instruction RRC_R(Cpu_Register);
Instruction RRC_ADDR_HL();

Instruction SRL_R(Cpu_Register);
Instruction SRL_ADDR_HL();

Instruction RL_R(Cpu_Register);
Instruction RL_ADDR_HL();

Instruction RR_R(Cpu_Register);
Instruction RR_ADDR_HL();

Instruction SLA_R(Cpu_Register);
Instruction SLA_ADDR_HL();

Instruction SLA_R(Cpu_Register);
Instruction SLA_ADDR_HL();

Instruction SRA_R(Cpu_Register);
Instruction SRA_ADDR_HL();

Instruction SWAP_R(Cpu_Register);
Instruction SWAP_ADDR_HL();

Instruction BIT_R(Cpu_Register, int);
Instruction BIT_ADDR_HL(int);

Instruction SET_R(Cpu_Register, int);
Instruction SET_ADDR_HL(int);

Instruction RES_R(Cpu_Register, int);
Instruction RES_ADDR_HL(int);
