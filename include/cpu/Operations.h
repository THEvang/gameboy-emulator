#pragma once
#include <stdexcept>
#include <string>
#include <cpu/Cpu.h>

class UnimplementedOperation : public std::runtime_error {
public:
    explicit UnimplementedOperation(const std::string& msg);
};

FetchResult NOP(Cpu& cpu);
FetchResult STOP(Cpu& cpu);
FetchResult HALT(Cpu& cpu);
FetchResult RST(Cpu& cpu, uint8_t address); 
FetchResult DI(Cpu& cpu);
FetchResult EI(Cpu& cpu);

FetchResult JR(Cpu& cpu);
FetchResult JR_NZ(Cpu& cpu);
FetchResult JR_Z(Cpu& cpu);
FetchResult JR_NC(Cpu& cpu);
FetchResult JR_C(Cpu& cpu);

FetchResult RET(Cpu& cpu);
FetchResult RET_Z(Cpu& cpu);
FetchResult RET_NZ(Cpu& cpu);
FetchResult RET_C(Cpu& cpu);
FetchResult RET_NC(Cpu& cpu);
FetchResult RETI(Cpu& cpu);

FetchResult JUMP(Cpu& cpu);
FetchResult JUMP_NZ(Cpu& cpu);
FetchResult JUMP_Z(Cpu& cpu);
FetchResult JUMP_NC(Cpu& cpu);
FetchResult JUMP_C(Cpu& cpu);
FetchResult JUMP_ADDR_HL(Cpu& cpu);

FetchResult CALL(Cpu& cpu);
FetchResult CALL_NZ(Cpu& cpu);
FetchResult CALL_Z(Cpu& cpu);
FetchResult CALL_NC(Cpu& cpu);
FetchResult CALL_C(Cpu& cpu);

FetchResult LD_A_D8(Cpu& cpu);
FetchResult LD_A_A(Cpu& cpu);
FetchResult LD_A_B(Cpu& cpu);
FetchResult LD_A_C(Cpu& cpu);
FetchResult LD_A_D(Cpu& cpu);
FetchResult LD_A_E(Cpu& cpu);
FetchResult LD_A_H(Cpu& cpu);
FetchResult LD_A_L(Cpu& cpu);
FetchResult LD_A_ADDR_BC(Cpu& cpu);
FetchResult LD_A_ADDR_DE(Cpu& cpu);
FetchResult LD_A_ADDR_HL(Cpu& cpu);
FetchResult LD_A_ADDR_C(Cpu& cpu);
FetchResult LD_A_ADDR_A16(Cpu& cpu);
FetchResult LD_ADDR_A16_SP(Cpu& cpu);

FetchResult LDI_ADDR_HL_A(Cpu& cpu);
FetchResult LDI_A_ADDR_HL(Cpu& cpu);

FetchResult LD_ADDR_BC_A(Cpu& cpu);
FetchResult LD_ADDR_DE_A(Cpu& cpu);

FetchResult LD_B_D8(Cpu& cpu);
FetchResult LD_B_A(Cpu& cpu);
FetchResult LD_B_B(Cpu& cpu);
FetchResult LD_B_C(Cpu& cpu);
FetchResult LD_B_D(Cpu& cpu);
FetchResult LD_B_E(Cpu& cpu);
FetchResult LD_B_H(Cpu& cpu);
FetchResult LD_B_L(Cpu& cpu);
FetchResult LD_B_ADDR_HL(Cpu& cpu);

FetchResult LD_C_D8(Cpu& cpu);
FetchResult LD_C_A(Cpu& cpu);
FetchResult LD_C_B(Cpu& cpu);
FetchResult LD_C_C(Cpu& cpu);
FetchResult LD_C_D(Cpu& cpu);
FetchResult LD_C_E(Cpu& cpu);
FetchResult LD_C_H(Cpu& cpu);
FetchResult LD_C_L(Cpu& cpu);
FetchResult LD_C_ADDR_HL(Cpu& cpu);

FetchResult LD_D_D8(Cpu& cpu);
FetchResult LD_D_A(Cpu& cpu);
FetchResult LD_D_B(Cpu& cpu);
FetchResult LD_D_C(Cpu& cpu);
FetchResult LD_D_D(Cpu& cpu);
FetchResult LD_D_E(Cpu& cpu);
FetchResult LD_D_H(Cpu& cpu);
FetchResult LD_D_L(Cpu& cpu);
FetchResult LD_D_ADDR_HL(Cpu& cpu);

FetchResult LD_E_D8(Cpu& cpu);
FetchResult LD_E_A(Cpu& cpu);
FetchResult LD_E_B(Cpu& cpu);
FetchResult LD_E_C(Cpu& cpu);
FetchResult LD_E_D(Cpu& cpu);
FetchResult LD_E_E(Cpu& cpu);
FetchResult LD_E_H(Cpu& cpu);
FetchResult LD_E_L(Cpu& cpu);
FetchResult LD_E_ADDR_HL(Cpu& cpu);

FetchResult LD_H_D8(Cpu& cpu);
FetchResult LD_H_A(Cpu& cpu);
FetchResult LD_H_B(Cpu& cpu);
FetchResult LD_H_C(Cpu& cpu);
FetchResult LD_H_D(Cpu& cpu);
FetchResult LD_H_E(Cpu& cpu);
FetchResult LD_H_H(Cpu& cpu);
FetchResult LD_H_L(Cpu& cpu);
FetchResult LD_H_ADDR_HL(Cpu& cpu);

FetchResult LD_L_D8(Cpu& cpu);
FetchResult LD_L_A(Cpu& cpu);
FetchResult LD_L_B(Cpu& cpu);
FetchResult LD_L_C(Cpu& cpu);
FetchResult LD_L_D(Cpu& cpu);
FetchResult LD_L_E(Cpu& cpu);
FetchResult LD_L_H(Cpu& cpu);
FetchResult LD_L_L(Cpu& cpu);
FetchResult LD_L_ADDR_HL(Cpu& cpu);

FetchResult LD_ADDR_HL_A(Cpu& cpu);
FetchResult LD_ADDR_HL_B(Cpu& cpu);
FetchResult LD_ADDR_HL_C(Cpu& cpu);
FetchResult LD_ADDR_HL_D(Cpu& cpu);
FetchResult LD_ADDR_HL_E(Cpu& cpu);
FetchResult LD_ADDR_HL_H(Cpu& cpu);
FetchResult LD_ADDR_HL_L(Cpu& cpu);
FetchResult LD_ADDR_HL_D8(Cpu& cpu);
FetchResult LD_ADDR_HL_ADDR_HL(Cpu& cpu);
FetchResult LD_ADDR_A16_A(Cpu& cpu);

FetchResult LD_BC_D16(Cpu& cpu);
FetchResult LD_DE_D16(Cpu& cpu);
FetchResult LD_HL_D16(Cpu& cpu);
FetchResult LD_HL_SPR8(Cpu& cpu);

FetchResult LD_SP_D16(Cpu& cpu);
FetchResult LD_SP_HL(Cpu& cpu);

FetchResult ADD_A_D8(Cpu& cpu);
FetchResult ADD_A_A(Cpu& cpu);
FetchResult ADD_A_B(Cpu& cpu);
FetchResult ADD_A_C(Cpu& cpu);
FetchResult ADD_A_D(Cpu& cpu);
FetchResult ADD_A_E(Cpu& cpu);
FetchResult ADD_A_H(Cpu& cpu);
FetchResult ADD_A_L(Cpu& cpu);
FetchResult ADD_A_ADDR_HL(Cpu& cpu);

FetchResult ADD_HL_BC(Cpu& cpu);
FetchResult ADD_HL_HL(Cpu& cpu);
FetchResult ADD_HL_DE(Cpu& cpu);
FetchResult ADD_HL_SP(Cpu& cpu);

FetchResult SUB_D8(Cpu& cpu);
FetchResult SUB_A(Cpu& cpu);
FetchResult SUB_B(Cpu& cpu);
FetchResult SUB_C(Cpu& cpu);
FetchResult SUB_D(Cpu& cpu);
FetchResult SUB_E(Cpu& cpu);
FetchResult SUB_H(Cpu& cpu);
FetchResult SUB_L(Cpu& cpu);
FetchResult SUB_ADDR_HL(Cpu& cpu);

FetchResult INC_A(Cpu& cpu);
FetchResult INC_B(Cpu& cpu);
FetchResult INC_C(Cpu& cpu);
FetchResult INC_D(Cpu& cpu);
FetchResult INC_E(Cpu& cpu);
FetchResult INC_H(Cpu& cpu);
FetchResult INC_L(Cpu& cpu);
FetchResult INC_BC(Cpu& cpu);
FetchResult INC_DE(Cpu& cpu);
FetchResult INC_HL(Cpu& cpu);
FetchResult INC_ADDR_HL(Cpu& cpu);
FetchResult INC_SP(Cpu& cpu);


FetchResult DEC_A(Cpu& cpu);
FetchResult DEC_B(Cpu& cpu);
FetchResult DEC_C(Cpu& cpu);
FetchResult DEC_D(Cpu& cpu);
FetchResult DEC_E(Cpu& cpu);
FetchResult DEC_H(Cpu& cpu);
FetchResult DEC_L(Cpu& cpu);
FetchResult DEC_BC(Cpu& cpu);
FetchResult DEC_DE(Cpu& cpu);
FetchResult DEC_HL(Cpu& cpu);
FetchResult DEC_ADDR_HL(Cpu& cpu);
FetchResult DEC_SP(Cpu& cpu);

FetchResult SCF(Cpu& cpu);
FetchResult CCF(Cpu& cpu);

FetchResult RRCA(Cpu& cpu);
FetchResult RRA(Cpu& cpu);

FetchResult RLA(Cpu& cpu);
FetchResult RLCA(Cpu& cpu);

FetchResult DAA(Cpu& cpu);

FetchResult ADD_SP_R8(Cpu& cpu);

FetchResult AND_D8(Cpu& cpu);
FetchResult AND_A(Cpu& cpu);
FetchResult AND_B(Cpu& cpu);
FetchResult AND_C(Cpu& cpu);
FetchResult AND_D(Cpu& cpu);
FetchResult AND_E(Cpu& cpu);
FetchResult AND_H(Cpu& cpu);
FetchResult AND_L(Cpu& cpu);
FetchResult AND_ADDR_HL(Cpu& cpu);

FetchResult XOR_D8(Cpu& cpu);
FetchResult XOR_A(Cpu& cpu);
FetchResult XOR_B(Cpu& cpu);
FetchResult XOR_C(Cpu& cpu);
FetchResult XOR_D(Cpu& cpu);
FetchResult XOR_E(Cpu& cpu);
FetchResult XOR_H(Cpu& cpu);
FetchResult XOR_L(Cpu& cpu);
FetchResult XOR_ADDR_HL(Cpu& cpu);

FetchResult OR_D8(Cpu& cpu);
FetchResult OR_A(Cpu& cpu);
FetchResult OR_B(Cpu& cpu);
FetchResult OR_C(Cpu& cpu);
FetchResult OR_D(Cpu& cpu);
FetchResult OR_E(Cpu& cpu);
FetchResult OR_H(Cpu& cpu);
FetchResult OR_L(Cpu& cpu);
FetchResult OR_ADDR_HL(Cpu& cpu);

FetchResult CP_D8(Cpu& cpu);
FetchResult CP_A(Cpu& cpu);
FetchResult CP_B(Cpu& cpu);
FetchResult CP_C(Cpu& cpu);
FetchResult CP_D(Cpu& cpu);
FetchResult CP_E(Cpu& cpu);
FetchResult CP_H(Cpu& cpu);
FetchResult CP_L(Cpu& cpu);
FetchResult CP_ADDR_HL(Cpu& cpu);

FetchResult PUSH_AF(Cpu& cpu);
FetchResult PUSH_BC(Cpu& cpu);
FetchResult PUSH_DE(Cpu& cpu);
FetchResult PUSH_HL(Cpu& cpu);

FetchResult POP_AF(Cpu& cpu);
FetchResult POP_BC(Cpu& cpu);
FetchResult POP_DE(Cpu& cpu);
FetchResult POP_HL(Cpu& cpu);

FetchResult ADC_A_D8(Cpu& cpu);
FetchResult ADC_A_A(Cpu& cpu);
FetchResult ADC_A_B(Cpu& cpu);
FetchResult ADC_A_C(Cpu& cpu);
FetchResult ADC_A_D(Cpu& cpu);
FetchResult ADC_A_E(Cpu& cpu);
FetchResult ADC_A_H(Cpu& cpu);
FetchResult ADC_A_L(Cpu& cpu);
FetchResult ADC_A_ADDR_HL(Cpu& cpu);

FetchResult LDH_ADDR_A8_A(Cpu& cpu);
FetchResult LDH_A_ADDR_A8(Cpu& cpu);
FetchResult LD_ADDR_C_A(Cpu& cpu);

FetchResult SBC_A_D8(Cpu& cpu);
FetchResult SBC_A_A(Cpu& cpu);
FetchResult SBC_A_B(Cpu& cpu);
FetchResult SBC_A_C(Cpu& cpu);
FetchResult SBC_A_D(Cpu& cpu);
FetchResult SBC_A_E(Cpu& cpu);
FetchResult SBC_A_H(Cpu& cpu);
FetchResult SBC_A_L(Cpu& cpu);
FetchResult SBC_A_ADDR_HL(Cpu& cpu);

FetchResult PREFIX_CB(Cpu& cpu);

FetchResult LD_ADDR_HLD_A(Cpu& cpu);
FetchResult LD_A_ADDR_HLD(Cpu& cpu);

FetchResult CPL(Cpu& cpu);
