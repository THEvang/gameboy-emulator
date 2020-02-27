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

void BIT_1_B(Cpu& cpu);
void BIT_1_C(Cpu& cpu);
void BIT_1_D(Cpu& cpu);
void BIT_1_E(Cpu& cpu);
void BIT_1_H(Cpu& cpu);
void BIT_1_L(Cpu& cpu);
void BIT_1_ADDR_HL(Cpu& cpu);
void BIT_1_A(Cpu& cpu);

void BIT_2_B(Cpu& cpu);
void BIT_2_C(Cpu& cpu);
void BIT_2_D(Cpu& cpu);
void BIT_2_E(Cpu& cpu);
void BIT_2_H(Cpu& cpu);
void BIT_2_L(Cpu& cpu);
void BIT_2_ADDR_HL(Cpu& cpu);
void BIT_2_A(Cpu& cpu);

void BIT_3_B(Cpu& cpu);
void BIT_3_C(Cpu& cpu);
void BIT_3_D(Cpu& cpu);
void BIT_3_E(Cpu& cpu);
void BIT_3_H(Cpu& cpu);
void BIT_3_L(Cpu& cpu);
void BIT_3_ADDR_HL(Cpu& cpu);
void BIT_3_A(Cpu& cpu);

void BIT_4_B(Cpu& cpu);
void BIT_4_C(Cpu& cpu);
void BIT_4_D(Cpu& cpu);
void BIT_4_E(Cpu& cpu);
void BIT_4_H(Cpu& cpu);
void BIT_4_L(Cpu& cpu);
void BIT_4_ADDR_HL(Cpu& cpu);
void BIT_4_A(Cpu& cpu);

void BIT_5_B(Cpu& cpu);
void BIT_5_C(Cpu& cpu);
void BIT_5_D(Cpu& cpu);
void BIT_5_E(Cpu& cpu);
void BIT_5_H(Cpu& cpu);
void BIT_5_L(Cpu& cpu);
void BIT_5_ADDR_HL(Cpu& cpu);
void BIT_5_A(Cpu& cpu);

void BIT_6_B(Cpu& cpu);
void BIT_6_C(Cpu& cpu);
void BIT_6_D(Cpu& cpu);
void BIT_6_E(Cpu& cpu);
void BIT_6_H(Cpu& cpu);
void BIT_6_L(Cpu& cpu);
void BIT_6_ADDR_HL(Cpu& cpu);
void BIT_6_A(Cpu& cpu);

void BIT_7_B(Cpu& cpu);
void BIT_7_C(Cpu& cpu);
void BIT_7_D(Cpu& cpu);
void BIT_7_E(Cpu& cpu);
void BIT_7_H(Cpu& cpu);
void BIT_7_L(Cpu& cpu);
void BIT_7_ADDR_HL(Cpu& cpu);
void BIT_7_A(Cpu& cpu);