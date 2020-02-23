#pragma once
#include <stdexcept>
#include <string>
#include <cpu/Cpu.h>

class UnimplementedOperation : public std::runtime_error {
public:

    UnimplementedOperation(const std::string& msg);
};

void NOP(Cpu& cpu);
void STOP(Cpu& cpu);
void HALT(Cpu& cpu);
void RST(Cpu& cpu, uint8_t address); 
void DI(Cpu& cpu);
void EI(Cpu& cpu);

void JR(Cpu& cpu);
void JR_NZ(Cpu& cpu);
void JR_Z(Cpu& cpu);
void JR_NC(Cpu& cpu);
void JR_C(Cpu& cpu);

void RET(Cpu& cpu);
void RET_Z(Cpu& cpu);
void RET_NZ(Cpu& cpu);
void RET_C(Cpu& cpu);
void RET_NC(Cpu& cpu);
void RETI(Cpu& cpu);

void JUMP(Cpu& cpu);
void JUMP_NZ(Cpu& cpu);
void JUMP_Z(Cpu& cpu);
void JUMP_NC(Cpu& cpu);
void JUMP_C(Cpu& cpu);
void JUMP_ADDR_HL(Cpu& cpu);

void CALL(Cpu& cpu);
void CALL_NZ(Cpu& cpu);
void CALL_Z(Cpu& cpu);
void CALL_NC(Cpu& cpu);
void CALL_C(Cpu& cpu);

void LD_A_D8(Cpu& cpu);
void LD_A_A(Cpu& cpu);
void LD_A_B(Cpu& cpu);
void LD_A_C(Cpu& cpu);
void LD_A_D(Cpu& cpu);
void LD_A_E(Cpu& cpu);
void LD_A_H(Cpu& cpu);
void LD_A_L(Cpu& cpu);
void LD_A_ADDR_BC(Cpu& cpu);
void LD_A_ADDR_DE(Cpu& cpu);
void LD_A_ADDR_HL(Cpu& cpu);
void LD_A_ADDR_C(Cpu& cpu);
void LD_A_ADDR_A16(Cpu& cpu);
void LD_ADDR_SP(Cpu& cpu);

void LDI_ADDR_HL_A(Cpu& cpu);
void LDI_A_ADDR_HL(Cpu& cpu);

void LD_ADDR_BC_A(Cpu& cpu);
void LD_ADDR_DE_A(Cpu& cpu);

void LD_B_D8(Cpu& cpu);
void LD_B_A(Cpu& cpu);
void LD_B_B(Cpu& cpu);
void LD_B_C(Cpu& cpu);
void LD_B_D(Cpu& cpu);
void LD_B_E(Cpu& cpu);
void LD_B_H(Cpu& cpu);
void LD_B_L(Cpu& cpu);
void LD_B_ADDR_HL(Cpu& cpu);

void LD_C_D8(Cpu& cpu);
void LD_C_A(Cpu& cpu);
void LD_C_B(Cpu& cpu);
void LD_C_C(Cpu& cpu);
void LD_C_D(Cpu& cpu);
void LD_C_E(Cpu& cpu);
void LD_C_H(Cpu& cpu);
void LD_C_L(Cpu& cpu);
void LD_C_ADDR_HL(Cpu& cpu);

void LD_D_D8(Cpu& cpu);
void LD_D_A(Cpu& cpu);
void LD_D_B(Cpu& cpu);
void LD_D_C(Cpu& cpu);
void LD_D_D(Cpu& cpu);
void LD_D_E(Cpu& cpu);
void LD_D_H(Cpu& cpu);
void LD_D_L(Cpu& cpu);
void LD_D_ADDR_HL(Cpu& cpu);

void LD_E_D8(Cpu& cpu);
void LD_E_A(Cpu& cpu);
void LD_E_B(Cpu& cpu);
void LD_E_C(Cpu& cpu);
void LD_E_D(Cpu& cpu);
void LD_E_E(Cpu& cpu);
void LD_E_H(Cpu& cpu);
void LD_E_L(Cpu& cpu);
void LD_E_ADDR_HL(Cpu& cpu);

void LD_H_D8(Cpu& cpu);
void LD_H_A(Cpu& cpu);
void LD_H_B(Cpu& cpu);
void LD_H_C(Cpu& cpu);
void LD_H_D(Cpu& cpu);
void LD_H_E(Cpu& cpu);
void LD_H_H(Cpu& cpu);
void LD_H_L(Cpu& cpu);
void LD_H_ADDR_HL(Cpu& cpu);

void LD_L_D8(Cpu& cpu);
void LD_L_A(Cpu& cpu);
void LD_L_B(Cpu& cpu);
void LD_L_C(Cpu& cpu);
void LD_L_D(Cpu& cpu);
void LD_L_E(Cpu& cpu);
void LD_L_H(Cpu& cpu);
void LD_L_L(Cpu& cpu);
void LD_L_ADDR_HL(Cpu& cpu);

void LD_ADDR_HL_A(Cpu& cpu);
void LD_ADDR_HL_B(Cpu& cpu);
void LD_ADDR_HL_C(Cpu& cpu);
void LD_ADDR_HL_D(Cpu& cpu);
void LD_ADDR_HL_E(Cpu& cpu);
void LD_ADDR_HL_H(Cpu& cpu);
void LD_ADDR_HL_L(Cpu& cpu);
void LD_ADDR_HL_ADDR_HL(Cpu& cpu);
void LD_ADDR_A16_A(Cpu& cpu);

void LD_BC_D16(Cpu& cpu);
void LD_DE_D16(Cpu& cpu);
void LD_HL_D16(Cpu& cpu);
void LD_HL_SPR8(Cpu& cpu);

void LD_SP_D16(Cpu& cpu);
void LD_SP_HL(Cpu& cpu);

void ADD_A_D8(Cpu& cpu);
void ADD_A_A(Cpu& cpu);
void ADD_A_B(Cpu& cpu);
void ADD_A_C(Cpu& cpu);
void ADD_A_D(Cpu& cpu);
void ADD_A_E(Cpu& cpu);
void ADD_A_H(Cpu& cpu);
void ADD_A_L(Cpu& cpu);
void ADD_A_ADDR_HL(Cpu& cpu);

void ADD_HL_BC(Cpu& cpu);
void ADD_HL_HL(Cpu& cpu);
void ADD_HL_DE(Cpu& cpu);

void SUB_D8(Cpu& cpu);
void SUB_A(Cpu& cpu);
void SUB_B(Cpu& cpu);
void SUB_C(Cpu& cpu);
void SUB_D(Cpu& cpu);
void SUB_E(Cpu& cpu);
void SUB_H(Cpu& cpu);
void SUB_L(Cpu& cpu);
void SUB_ADDR_HL(Cpu& cpu);

void INC_A(Cpu& cpu);
void INC_B(Cpu& cpu);
void INC_C(Cpu& cpu);
void INC_D(Cpu& cpu);
void INC_E(Cpu& cpu);
void INC_H(Cpu& cpu);
void INC_L(Cpu& cpu);
void INC_BC(Cpu& cpu);
void INC_DE(Cpu& cpu);
void INC_HL(Cpu& cpu);
void INC_ADDR_HL(Cpu& cpu);
void INC_SP(Cpu& cpu);


void DEC_A(Cpu& cpu);
void DEC_B(Cpu& cpu);
void DEC_C(Cpu& cpu);
void DEC_D(Cpu& cpu);
void DEC_E(Cpu& cpu);
void DEC_H(Cpu& cpu);
void DEC_L(Cpu& cpu);
void DEC_BC(Cpu& cpu);
void DEC_DE(Cpu& cpu);
void DEC_HL(Cpu& cpu);
void DEC_ADDR_HL(Cpu& cpu);
void DEC_SP(Cpu& cpu);

void SCF(Cpu& cpu);
void CCF(Cpu& cpu);

void RRCA(Cpu& cpu);
void RRA(Cpu& cpu);

void RLA(Cpu& cpu);
void RLCA(Cpu& cpu);

void DDA(Cpu& cpu);

void ADD_SP_R8(Cpu& cpu);

void AND_D8(Cpu& cpu);
void AND_A(Cpu& cpu);
void AND_B(Cpu& cpu);
void AND_C(Cpu& cpu);
void AND_D(Cpu& cpu);
void AND_E(Cpu& cpu);
void AND_H(Cpu& cpu);
void AND_L(Cpu& cpu);
void AND_ADDR_HL(Cpu& cpu);

void XOR_D8(Cpu& cpu);
void XOR_A(Cpu& cpu);
void XOR_B(Cpu& cpu);
void XOR_C(Cpu& cpu);
void XOR_D(Cpu& cpu);
void XOR_E(Cpu& cpu);
void XOR_H(Cpu& cpu);
void XOR_L(Cpu& cpu);
void XOR_ADDR_HL(Cpu& cpu);

void OR_D8(Cpu& cpu);
void OR_A(Cpu& cpu);
void OR_B(Cpu& cpu);
void OR_C(Cpu& cpu);
void OR_D(Cpu& cpu);
void OR_E(Cpu& cpu);
void OR_H(Cpu& cpu);
void OR_L(Cpu& cpu);
void OR_ADDR_HL(Cpu& cpu);

void CP_D8(Cpu& cpu);
void CP_A(Cpu& cpu);
void CP_B(Cpu& cpu);
void CP_C(Cpu& cpu);
void CP_D(Cpu& cpu);
void CP_E(Cpu& cpu);
void CP_H(Cpu& cpu);
void CP_L(Cpu& cpu);
void CP_ADDR_HL(Cpu& cpu);

void PUSH_AF(Cpu& cpu);
void PUSH_BC(Cpu& cpu);
void PUSH_DE(Cpu& cpu);
void PUSH_HL(Cpu& cpu);

void POP_AF(Cpu& cpu);
void POP_BC(Cpu& cpu);
void POP_DE(Cpu& cpu);
void POP_HL(Cpu& cpu);

void ADC_A_D8(Cpu& cpu);
void ADC_A_A(Cpu& cpu);
void ADC_A_B(Cpu& cpu);
void ADC_A_C(Cpu& cpu);
void ADC_A_D(Cpu& cpu);
void ADC_A_E(Cpu& cpu);
void ADC_A_H(Cpu& cpu);
void ADC_A_L(Cpu& cpu);
void ADC_A_ADDR_HL(Cpu& cpu);

void LDH_ADDR_A8_A(Cpu& cpu);
void LDH_A_ADDR_A8(Cpu& cpu);
void LD_ADDR_C_A(Cpu& cpu);

void SBC_A_D8(Cpu& cpu);
void SBC_A_A(Cpu& cpu);
void SBC_A_B(Cpu& cpu);
void SBC_A_C(Cpu& cpu);
void SBC_A_D(Cpu& cpu);
void SBC_A_E(Cpu& cpu);
void SBC_A_H(Cpu& cpu);
void SBC_A_L(Cpu& cpu);
void SBC_A_ADDR_HL(Cpu& cpu);

void PREFIX_CB(Cpu& cpu);

void LD_ADDR_HLD_A(Cpu& cpu);