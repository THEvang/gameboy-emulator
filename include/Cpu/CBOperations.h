#pragma once 

#include <Cpu/Cpu.h>

FetchResult RLC_B(Cpu& cpu);
FetchResult RLC_C(Cpu& cpu);
FetchResult RLC_D(Cpu& cpu);
FetchResult RLC_E(Cpu& cpu);
FetchResult RLC_H(Cpu& cpu);
FetchResult RLC_L(Cpu& cpu);
FetchResult RLC_ADDR_HL(Cpu& cpu);
FetchResult RLC_A(Cpu& cpu);

FetchResult RRC_B(Cpu& cpu);
FetchResult RRC_C(Cpu& cpu);
FetchResult RRC_D(Cpu& cpu);
FetchResult RRC_E(Cpu& cpu);
FetchResult RRC_H(Cpu& cpu);
FetchResult RRC_L(Cpu& cpu);
FetchResult RRC_ADDR_HL(Cpu& cpu);
FetchResult RRC_A(Cpu& cpu);

FetchResult SRL_A(Cpu& cpu);
FetchResult SRL_B(Cpu& cpu);
FetchResult SRL_C(Cpu& cpu);
FetchResult SRL_D(Cpu& cpu);
FetchResult SRL_E(Cpu& cpu);
FetchResult SRL_H(Cpu& cpu);
FetchResult SRL_L(Cpu& cpu);
FetchResult SRL_ADDR_HL(Cpu& cpu);

FetchResult RL_B(Cpu& cpu);
FetchResult RL_C(Cpu& cpu);
FetchResult RL_D(Cpu& cpu);
FetchResult RL_E(Cpu& cpu);
FetchResult RL_H(Cpu& cpu);
FetchResult RL_L(Cpu& cpu);
FetchResult RL_ADDR_HL(Cpu& cpu);
FetchResult RL_A(Cpu& cpu);

FetchResult RR_B(Cpu& cpu);
FetchResult RR_C(Cpu& cpu);
FetchResult RR_D(Cpu& cpu);
FetchResult RR_E(Cpu& cpu);
FetchResult RR_H(Cpu& cpu);
FetchResult RR_L(Cpu& cpu);
FetchResult RR_ADDR_HL(Cpu& cpu);
FetchResult RR_A(Cpu& cpu);

FetchResult SLA_B(Cpu& cpu);
FetchResult SLA_C(Cpu& cpu);
FetchResult SLA_D(Cpu& cpu);
FetchResult SLA_E(Cpu& cpu);
FetchResult SLA_H(Cpu& cpu);
FetchResult SLA_L(Cpu& cpu);
FetchResult SLA_ADDR_HL(Cpu& cpu);
FetchResult SLA_A(Cpu& cpu);

FetchResult SLA_B(Cpu& cpu);
FetchResult SLA_C(Cpu& cpu);
FetchResult SLA_D(Cpu& cpu);
FetchResult SLA_E(Cpu& cpu);
FetchResult SLA_H(Cpu& cpu);
FetchResult SLA_L(Cpu& cpu);
FetchResult SLA_ADDR_HL(Cpu& cpu);
FetchResult SLA_A(Cpu& cpu);

FetchResult SRA_B(Cpu& cpu);
FetchResult SRA_C(Cpu& cpu);
FetchResult SRA_D(Cpu& cpu);
FetchResult SRA_E(Cpu& cpu);
FetchResult SRA_H(Cpu& cpu);
FetchResult SRA_L(Cpu& cpu);
FetchResult SRA_ADDR_HL(Cpu& cpu);
FetchResult SRA_A(Cpu& cpu);

FetchResult SWAP_B(Cpu& cpu);
FetchResult SWAP_C(Cpu& cpu);
FetchResult SWAP_D(Cpu& cpu);
FetchResult SWAP_E(Cpu& cpu);
FetchResult SWAP_H(Cpu& cpu);
FetchResult SWAP_L(Cpu& cpu);
FetchResult SWAP_ADDR_HL(Cpu& cpu);
FetchResult SWAP_A(Cpu& cpu);

FetchResult BIT_0_B(Cpu& cpu);
FetchResult BIT_0_C(Cpu& cpu);
FetchResult BIT_0_D(Cpu& cpu);
FetchResult BIT_0_E(Cpu& cpu);
FetchResult BIT_0_H(Cpu& cpu);
FetchResult BIT_0_L(Cpu& cpu);
FetchResult BIT_0_ADDR_HL(Cpu& cpu);
FetchResult BIT_0_A(Cpu& cpu);

FetchResult BIT_1_B(Cpu& cpu);
FetchResult BIT_1_C(Cpu& cpu);
FetchResult BIT_1_D(Cpu& cpu);
FetchResult BIT_1_E(Cpu& cpu);
FetchResult BIT_1_H(Cpu& cpu);
FetchResult BIT_1_L(Cpu& cpu);
FetchResult BIT_1_ADDR_HL(Cpu& cpu);
FetchResult BIT_1_A(Cpu& cpu);

FetchResult BIT_2_B(Cpu& cpu);
FetchResult BIT_2_C(Cpu& cpu);
FetchResult BIT_2_D(Cpu& cpu);
FetchResult BIT_2_E(Cpu& cpu);
FetchResult BIT_2_H(Cpu& cpu);
FetchResult BIT_2_L(Cpu& cpu);
FetchResult BIT_2_ADDR_HL(Cpu& cpu);
FetchResult BIT_2_A(Cpu& cpu);

FetchResult BIT_3_B(Cpu& cpu);
FetchResult BIT_3_C(Cpu& cpu);
FetchResult BIT_3_D(Cpu& cpu);
FetchResult BIT_3_E(Cpu& cpu);
FetchResult BIT_3_H(Cpu& cpu);
FetchResult BIT_3_L(Cpu& cpu);
FetchResult BIT_3_ADDR_HL(Cpu& cpu);
FetchResult BIT_3_A(Cpu& cpu);

FetchResult BIT_4_B(Cpu& cpu);
FetchResult BIT_4_C(Cpu& cpu);
FetchResult BIT_4_D(Cpu& cpu);
FetchResult BIT_4_E(Cpu& cpu);
FetchResult BIT_4_H(Cpu& cpu);
FetchResult BIT_4_L(Cpu& cpu);
FetchResult BIT_4_ADDR_HL(Cpu& cpu);
FetchResult BIT_4_A(Cpu& cpu);

FetchResult BIT_5_B(Cpu& cpu);
FetchResult BIT_5_C(Cpu& cpu);
FetchResult BIT_5_D(Cpu& cpu);
FetchResult BIT_5_E(Cpu& cpu);
FetchResult BIT_5_H(Cpu& cpu);
FetchResult BIT_5_L(Cpu& cpu);
FetchResult BIT_5_ADDR_HL(Cpu& cpu);
FetchResult BIT_5_A(Cpu& cpu);

FetchResult BIT_6_B(Cpu& cpu);
FetchResult BIT_6_C(Cpu& cpu);
FetchResult BIT_6_D(Cpu& cpu);
FetchResult BIT_6_E(Cpu& cpu);
FetchResult BIT_6_H(Cpu& cpu);
FetchResult BIT_6_L(Cpu& cpu);
FetchResult BIT_6_ADDR_HL(Cpu& cpu);
FetchResult BIT_6_A(Cpu& cpu);

FetchResult BIT_7_B(Cpu& cpu);
FetchResult BIT_7_C(Cpu& cpu);
FetchResult BIT_7_D(Cpu& cpu);
FetchResult BIT_7_E(Cpu& cpu);
FetchResult BIT_7_H(Cpu& cpu);
FetchResult BIT_7_L(Cpu& cpu);
FetchResult BIT_7_ADDR_HL(Cpu& cpu);
FetchResult BIT_7_A(Cpu& cpu);

FetchResult RES_0_B(Cpu& cpu);
FetchResult RES_0_C(Cpu& cpu);
FetchResult RES_0_D(Cpu& cpu);
FetchResult RES_0_E(Cpu& cpu);
FetchResult RES_0_H(Cpu& cpu);
FetchResult RES_0_L(Cpu& cpu);
FetchResult RES_0_ADDR_HL(Cpu& cpu);
FetchResult RES_0_A(Cpu& cpu);

FetchResult RES_1_B(Cpu& cpu);
FetchResult RES_1_C(Cpu& cpu);
FetchResult RES_1_D(Cpu& cpu);
FetchResult RES_1_E(Cpu& cpu);
FetchResult RES_1_H(Cpu& cpu);
FetchResult RES_1_L(Cpu& cpu);
FetchResult RES_1_ADDR_HL(Cpu& cpu);
FetchResult RES_1_A(Cpu& cpu);

FetchResult RES_2_B(Cpu& cpu);
FetchResult RES_2_C(Cpu& cpu);
FetchResult RES_2_D(Cpu& cpu);
FetchResult RES_2_E(Cpu& cpu);
FetchResult RES_2_H(Cpu& cpu);
FetchResult RES_2_L(Cpu& cpu);
FetchResult RES_2_ADDR_HL(Cpu& cpu);
FetchResult RES_2_A(Cpu& cpu);

FetchResult RES_3_B(Cpu& cpu);
FetchResult RES_3_C(Cpu& cpu);
FetchResult RES_3_D(Cpu& cpu);
FetchResult RES_3_E(Cpu& cpu);
FetchResult RES_3_H(Cpu& cpu);
FetchResult RES_3_L(Cpu& cpu);
FetchResult RES_3_ADDR_HL(Cpu& cpu);
FetchResult RES_3_A(Cpu& cpu);

FetchResult RES_4_B(Cpu& cpu);
FetchResult RES_4_C(Cpu& cpu);
FetchResult RES_4_D(Cpu& cpu);
FetchResult RES_4_E(Cpu& cpu);
FetchResult RES_4_H(Cpu& cpu);
FetchResult RES_4_L(Cpu& cpu);
FetchResult RES_4_ADDR_HL(Cpu& cpu);
FetchResult RES_4_A(Cpu& cpu);

FetchResult RES_5_B(Cpu& cpu);
FetchResult RES_5_C(Cpu& cpu);
FetchResult RES_5_D(Cpu& cpu);
FetchResult RES_5_E(Cpu& cpu);
FetchResult RES_5_H(Cpu& cpu);
FetchResult RES_5_L(Cpu& cpu);
FetchResult RES_5_ADDR_HL(Cpu& cpu);
FetchResult RES_5_A(Cpu& cpu);

FetchResult RES_6_B(Cpu& cpu);
FetchResult RES_6_C(Cpu& cpu);
FetchResult RES_6_D(Cpu& cpu);
FetchResult RES_6_E(Cpu& cpu);
FetchResult RES_6_H(Cpu& cpu);
FetchResult RES_6_L(Cpu& cpu);
FetchResult RES_6_ADDR_HL(Cpu& cpu);
FetchResult RES_6_A(Cpu& cpu);

FetchResult RES_7_B(Cpu& cpu);
FetchResult RES_7_C(Cpu& cpu);
FetchResult RES_7_D(Cpu& cpu);
FetchResult RES_7_E(Cpu& cpu);
FetchResult RES_7_H(Cpu& cpu);
FetchResult RES_7_L(Cpu& cpu);
FetchResult RES_7_ADDR_HL(Cpu& cpu);
FetchResult RES_7_A(Cpu& cpu);

FetchResult SET_0_B(Cpu& cpu);
FetchResult SET_0_C(Cpu& cpu);
FetchResult SET_0_D(Cpu& cpu);
FetchResult SET_0_E(Cpu& cpu);
FetchResult SET_0_H(Cpu& cpu);
FetchResult SET_0_L(Cpu& cpu);
FetchResult SET_0_ADDR_HL(Cpu& cpu);
FetchResult SET_0_A(Cpu& cpu);

FetchResult SET_1_B(Cpu& cpu);
FetchResult SET_1_C(Cpu& cpu);
FetchResult SET_1_D(Cpu& cpu);
FetchResult SET_1_E(Cpu& cpu);
FetchResult SET_1_H(Cpu& cpu);
FetchResult SET_1_L(Cpu& cpu);
FetchResult SET_1_ADDR_HL(Cpu& cpu);
FetchResult SET_1_A(Cpu& cpu);

FetchResult SET_2_B(Cpu& cpu);
FetchResult SET_2_C(Cpu& cpu);
FetchResult SET_2_D(Cpu& cpu);
FetchResult SET_2_E(Cpu& cpu);
FetchResult SET_2_H(Cpu& cpu);
FetchResult SET_2_L(Cpu& cpu);
FetchResult SET_2_ADDR_HL(Cpu& cpu);
FetchResult SET_2_A(Cpu& cpu);

FetchResult SET_3_B(Cpu& cpu);
FetchResult SET_3_C(Cpu& cpu);
FetchResult SET_3_D(Cpu& cpu);
FetchResult SET_3_E(Cpu& cpu);
FetchResult SET_3_H(Cpu& cpu);
FetchResult SET_3_L(Cpu& cpu);
FetchResult SET_3_ADDR_HL(Cpu& cpu);
FetchResult SET_3_A(Cpu& cpu);

FetchResult SET_4_B(Cpu& cpu);
FetchResult SET_4_C(Cpu& cpu);
FetchResult SET_4_D(Cpu& cpu);
FetchResult SET_4_E(Cpu& cpu);
FetchResult SET_4_H(Cpu& cpu);
FetchResult SET_4_L(Cpu& cpu);
FetchResult SET_4_ADDR_HL(Cpu& cpu);
FetchResult SET_4_A(Cpu& cpu);

FetchResult SET_5_B(Cpu& cpu);
FetchResult SET_5_C(Cpu& cpu);
FetchResult SET_5_D(Cpu& cpu);
FetchResult SET_5_E(Cpu& cpu);
FetchResult SET_5_H(Cpu& cpu);
FetchResult SET_5_L(Cpu& cpu);
FetchResult SET_5_ADDR_HL(Cpu& cpu);
FetchResult SET_5_A(Cpu& cpu);

FetchResult SET_6_B(Cpu& cpu);
FetchResult SET_6_C(Cpu& cpu);
FetchResult SET_6_D(Cpu& cpu);
FetchResult SET_6_E(Cpu& cpu);
FetchResult SET_6_H(Cpu& cpu);
FetchResult SET_6_L(Cpu& cpu);
FetchResult SET_6_ADDR_HL(Cpu& cpu);
FetchResult SET_6_A(Cpu& cpu);

FetchResult SET_7_B(Cpu& cpu);
FetchResult SET_7_C(Cpu& cpu);
FetchResult SET_7_D(Cpu& cpu);
FetchResult SET_7_E(Cpu& cpu);
FetchResult SET_7_H(Cpu& cpu);
FetchResult SET_7_L(Cpu& cpu);
FetchResult SET_7_ADDR_HL(Cpu& cpu);
FetchResult SET_7_A(Cpu& cpu);