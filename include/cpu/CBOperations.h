#pragma once 
#include <cpu/Cpu.h>
#include <cpu/CBOpcodes.h>

void RLC_B();
void RLC_C();
void RLC_D();
void RLC_E();
void RLC_H();
void RLC_L();

void SRL_A(Cpu& cpu);
void SRL_B(Cpu& cpu);
void SRL_C(Cpu& cpu);
void SRL_D(Cpu& cpu);
void SRL_E(Cpu& cpu);
void SRL_H(Cpu& cpu);
void SRL_L(Cpu& cpu);
void SRL_ADDR_HL(Cpu& cpu);

void RR_A(Cpu& cpu);
void RR_B(Cpu& cpu);
void RR_C(Cpu& cpu);
void RR_D(Cpu& cpu);
void RR_E(Cpu& cpu);
void RR_H(Cpu& cpu);
void RR_L(Cpu& cpu);
void RR_ADDR_HL(Cpu& cpu);

void SWAP_B(Cpu& cpu);
void SWAP_C(Cpu& cpu);
void SWAP_D(Cpu& cpu);
void SWAP_E(Cpu& cpu);
void SWAP_H(Cpu& cpu);
void SWAP_L(Cpu& cpu);
void SWAP_ADDR_HL(Cpu& cpu);
void SWAP_A(Cpu& cpu);

void BIT_0_B(Cpu& cpu);
void BIT_0_C(Cpu& cpu);
void BIT_0_D(Cpu& cpu);
void BIT_0_E(Cpu& cpu);
void BIT_0_H(Cpu& cpu);
void BIT_0_L(Cpu& cpu);
void BIT_0_ADDR_HL(Cpu& cpu);
void BIT_0_A(Cpu& cpu);