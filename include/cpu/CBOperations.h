#pragma once 
#include <cpu/Cpu.h>
#include <cpu/CBOpcodes.h>

void RLC_B(Cpu& cpu);
void RLC_C(Cpu& cpu);
void RLC_D(Cpu& cpu);
void RLC_E(Cpu& cpu);
void RLC_H(Cpu& cpu);
void RLC_L(Cpu& cpu);
void RLC_ADDR_HL(Cpu& cpu);
void RLC_A(Cpu& cpu);

void RRC_B(Cpu& cpu);
void RRC_C(Cpu& cpu);
void RRC_D(Cpu& cpu);
void RRC_E(Cpu& cpu);
void RRC_H(Cpu& cpu);
void RRC_L(Cpu& cpu);
void RRC_ADDR_HL(Cpu& cpu);
void RRC_A(Cpu& cpu);

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

void RES_0_B(Cpu& cpu);
void RES_0_C(Cpu& cpu);
void RES_0_D(Cpu& cpu);
void RES_0_E(Cpu& cpu);
void RES_0_H(Cpu& cpu);
void RES_0_L(Cpu& cpu);
void RES_0_ADDR_HL(Cpu& cpu);
void RES_0_A(Cpu& cpu);

void RES_1_B(Cpu& cpu);
void RES_1_C(Cpu& cpu);
void RES_1_D(Cpu& cpu);
void RES_1_E(Cpu& cpu);
void RES_1_H(Cpu& cpu);
void RES_1_L(Cpu& cpu);
void RES_1_ADDR_HL(Cpu& cpu);
void RES_1_A(Cpu& cpu);

void RES_2_B(Cpu& cpu);
void RES_2_C(Cpu& cpu);
void RES_2_D(Cpu& cpu);
void RES_2_E(Cpu& cpu);
void RES_2_H(Cpu& cpu);
void RES_2_L(Cpu& cpu);
void RES_2_ADDR_HL(Cpu& cpu);
void RES_2_A(Cpu& cpu);

void RES_3_B(Cpu& cpu);
void RES_3_C(Cpu& cpu);
void RES_3_D(Cpu& cpu);
void RES_3_E(Cpu& cpu);
void RES_3_H(Cpu& cpu);
void RES_3_L(Cpu& cpu);
void RES_3_ADDR_HL(Cpu& cpu);
void RES_3_A(Cpu& cpu);

void RES_4_B(Cpu& cpu);
void RES_4_C(Cpu& cpu);
void RES_4_D(Cpu& cpu);
void RES_4_E(Cpu& cpu);
void RES_4_H(Cpu& cpu);
void RES_4_L(Cpu& cpu);
void RES_4_ADDR_HL(Cpu& cpu);
void RES_4_A(Cpu& cpu);

void RES_5_B(Cpu& cpu);
void RES_5_C(Cpu& cpu);
void RES_5_D(Cpu& cpu);
void RES_5_E(Cpu& cpu);
void RES_5_H(Cpu& cpu);
void RES_5_L(Cpu& cpu);
void RES_5_ADDR_HL(Cpu& cpu);
void RES_5_A(Cpu& cpu);

void RES_6_B(Cpu& cpu);
void RES_6_C(Cpu& cpu);
void RES_6_D(Cpu& cpu);
void RES_6_E(Cpu& cpu);
void RES_6_H(Cpu& cpu);
void RES_6_L(Cpu& cpu);
void RES_6_ADDR_HL(Cpu& cpu);
void RES_6_A(Cpu& cpu);

void RES_7_B(Cpu& cpu);
void RES_7_C(Cpu& cpu);
void RES_7_D(Cpu& cpu);
void RES_7_E(Cpu& cpu);
void RES_7_H(Cpu& cpu);
void RES_7_L(Cpu& cpu);
void RES_7_ADDR_HL(Cpu& cpu);
void RES_7_A(Cpu& cpu);

void SET_0_B(Cpu& cpu);
void SET_0_C(Cpu& cpu);
void SET_0_D(Cpu& cpu);
void SET_0_E(Cpu& cpu);
void SET_0_H(Cpu& cpu);
void SET_0_L(Cpu& cpu);
void SET_0_ADDR_HL(Cpu& cpu);
void SET_0_A(Cpu& cpu);

void SET_1_B(Cpu& cpu);
void SET_1_C(Cpu& cpu);
void SET_1_D(Cpu& cpu);
void SET_1_E(Cpu& cpu);
void SET_1_H(Cpu& cpu);
void SET_1_L(Cpu& cpu);
void SET_1_ADDR_HL(Cpu& cpu);
void SET_1_A(Cpu& cpu);

void SET_2_B(Cpu& cpu);
void SET_2_C(Cpu& cpu);
void SET_2_D(Cpu& cpu);
void SET_2_E(Cpu& cpu);
void SET_2_H(Cpu& cpu);
void SET_2_L(Cpu& cpu);
void SET_2_ADDR_HL(Cpu& cpu);
void SET_2_A(Cpu& cpu);

void SET_3_B(Cpu& cpu);
void SET_3_C(Cpu& cpu);
void SET_3_D(Cpu& cpu);
void SET_3_E(Cpu& cpu);
void SET_3_H(Cpu& cpu);
void SET_3_L(Cpu& cpu);
void SET_3_ADDR_HL(Cpu& cpu);
void SET_3_A(Cpu& cpu);

void SET_4_B(Cpu& cpu);
void SET_4_C(Cpu& cpu);
void SET_4_D(Cpu& cpu);
void SET_4_E(Cpu& cpu);
void SET_4_H(Cpu& cpu);
void SET_4_L(Cpu& cpu);
void SET_4_ADDR_HL(Cpu& cpu);
void SET_4_A(Cpu& cpu);

void SET_5_B(Cpu& cpu);
void SET_5_C(Cpu& cpu);
void SET_5_D(Cpu& cpu);
void SET_5_E(Cpu& cpu);
void SET_5_H(Cpu& cpu);
void SET_5_L(Cpu& cpu);
void SET_5_ADDR_HL(Cpu& cpu);
void SET_5_A(Cpu& cpu);

void SET_6_B(Cpu& cpu);
void SET_6_C(Cpu& cpu);
void SET_6_D(Cpu& cpu);
void SET_6_E(Cpu& cpu);
void SET_6_H(Cpu& cpu);
void SET_6_L(Cpu& cpu);
void SET_6_ADDR_HL(Cpu& cpu);
void SET_6_A(Cpu& cpu);

void SET_7_B(Cpu& cpu);
void SET_7_C(Cpu& cpu);
void SET_7_D(Cpu& cpu);
void SET_7_E(Cpu& cpu);
void SET_7_H(Cpu& cpu);
void SET_7_L(Cpu& cpu);
void SET_7_ADDR_HL(Cpu& cpu);
void SET_7_A(Cpu& cpu);