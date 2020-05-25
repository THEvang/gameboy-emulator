#pragma once

#include <stdexcept>
#include <string>

#include "Cpu/Cpu.h"

class UnimplementedOperation : public std::runtime_error {
public:
    explicit UnimplementedOperation(const std::string& msg);
};

FetchResult NOP();
FetchResult STOP();
FetchResult HALT();
FetchResult RST(uint8_t address); 
FetchResult DI();
FetchResult EI();

FetchResult JR();
FetchResult JR_NZ();
FetchResult JR_Z();
FetchResult JR_NC();
FetchResult JR_C();

FetchResult RET();
FetchResult RET_Z();
FetchResult RET_NZ();
FetchResult RET_C();
FetchResult RET_NC();
FetchResult RETI();

FetchResult JUMP();
FetchResult JUMP_NZ();
FetchResult JUMP_Z();
FetchResult JUMP_NC();
FetchResult JUMP_C();
FetchResult JUMP_ADDR_HL();

FetchResult CALL();
FetchResult CALL_NZ();
FetchResult CALL_Z();
FetchResult CALL_NC();
FetchResult CALL_C();

FetchResult LD_A_D8();
FetchResult LD_A_A();
FetchResult LD_A_B();
FetchResult LD_A_C();
FetchResult LD_A_D();
FetchResult LD_A_E();
FetchResult LD_A_H();
FetchResult LD_A_L();
FetchResult LD_A_ADDR_BC();
FetchResult LD_A_ADDR_DE();
FetchResult LD_A_ADDR_HL();
FetchResult LD_A_ADDR_C();
FetchResult LD_A_ADDR_A16();
FetchResult LD_ADDR_A16_SP();

FetchResult LDI_ADDR_HL_A();
FetchResult LDI_A_ADDR_HL();

FetchResult LD_ADDR_BC_A();
FetchResult LD_ADDR_DE_A();

FetchResult LD_B_D8();
FetchResult LD_B_A();
FetchResult LD_B_B();
FetchResult LD_B_C();
FetchResult LD_B_D();
FetchResult LD_B_E();
FetchResult LD_B_H();
FetchResult LD_B_L();
FetchResult LD_B_ADDR_HL();

FetchResult LD_C_D8();
FetchResult LD_C_A();
FetchResult LD_C_B();
FetchResult LD_C_C();
FetchResult LD_C_D();
FetchResult LD_C_E();
FetchResult LD_C_H();
FetchResult LD_C_L();
FetchResult LD_C_ADDR_HL();

FetchResult LD_D_D8();
FetchResult LD_D_A();
FetchResult LD_D_B();
FetchResult LD_D_C();
FetchResult LD_D_D();
FetchResult LD_D_E();
FetchResult LD_D_H();
FetchResult LD_D_L();
FetchResult LD_D_ADDR_HL();

FetchResult LD_E_D8();
FetchResult LD_E_A();
FetchResult LD_E_B();
FetchResult LD_E_C();
FetchResult LD_E_D();
FetchResult LD_E_E();
FetchResult LD_E_H();
FetchResult LD_E_L();
FetchResult LD_E_ADDR_HL();

FetchResult LD_H_D8();
FetchResult LD_H_A();
FetchResult LD_H_B();
FetchResult LD_H_C();
FetchResult LD_H_D();
FetchResult LD_H_E();
FetchResult LD_H_H();
FetchResult LD_H_L();
FetchResult LD_H_ADDR_HL();

FetchResult LD_L_D8();
FetchResult LD_L_A();
FetchResult LD_L_B();
FetchResult LD_L_C();
FetchResult LD_L_D();
FetchResult LD_L_E();
FetchResult LD_L_H();
FetchResult LD_L_L();
FetchResult LD_L_ADDR_HL();

FetchResult LD_ADDR_HL_A();
FetchResult LD_ADDR_HL_B();
FetchResult LD_ADDR_HL_C();
FetchResult LD_ADDR_HL_D();
FetchResult LD_ADDR_HL_E();
FetchResult LD_ADDR_HL_H();
FetchResult LD_ADDR_HL_L();
FetchResult LD_ADDR_HL_D8();
FetchResult LD_ADDR_HL_ADDR_HL();
FetchResult LD_ADDR_A16_A();

FetchResult LD_BC_D16();
FetchResult LD_DE_D16();
FetchResult LD_HL_D16();
FetchResult LD_HL_SPR8();

FetchResult LD_SP_D16();
FetchResult LD_SP_HL();

FetchResult ADD_A_D8();
FetchResult ADD_A_A();
FetchResult ADD_A_B();
FetchResult ADD_A_C();
FetchResult ADD_A_D();
FetchResult ADD_A_E();
FetchResult ADD_A_H();
FetchResult ADD_A_L();
FetchResult ADD_A_ADDR_HL();

FetchResult ADD_HL_BC();
FetchResult ADD_HL_HL();
FetchResult ADD_HL_DE();
FetchResult ADD_HL_SP();

FetchResult SUB_D8();
FetchResult SUB_A();
FetchResult SUB_B();
FetchResult SUB_C();
FetchResult SUB_D();
FetchResult SUB_E();
FetchResult SUB_H();
FetchResult SUB_L();
FetchResult SUB_ADDR_HL();

FetchResult INC_A();
FetchResult INC_B();
FetchResult INC_C();
FetchResult INC_D();
FetchResult INC_E();
FetchResult INC_H();
FetchResult INC_L();
FetchResult INC_BC();
FetchResult INC_DE();
FetchResult INC_HL();
FetchResult INC_ADDR_HL();
FetchResult INC_SP();


FetchResult DEC_A();
FetchResult DEC_B();
FetchResult DEC_C();
FetchResult DEC_D();
FetchResult DEC_E();
FetchResult DEC_H();
FetchResult DEC_L();
FetchResult DEC_BC();
FetchResult DEC_DE();
FetchResult DEC_HL();
FetchResult DEC_ADDR_HL();
FetchResult DEC_SP();

FetchResult SCF();
FetchResult CCF();

FetchResult RRCA();
FetchResult RRA();

FetchResult RLA();
FetchResult RLCA();

FetchResult DAA();

FetchResult ADD_SP_R8();

FetchResult AND_D8();
FetchResult AND_A();
FetchResult AND_B();
FetchResult AND_C();
FetchResult AND_D();
FetchResult AND_E();
FetchResult AND_H();
FetchResult AND_L();
FetchResult AND_ADDR_HL();

FetchResult XOR_D8();
FetchResult XOR_A();
FetchResult XOR_B();
FetchResult XOR_C();
FetchResult XOR_D();
FetchResult XOR_E();
FetchResult XOR_H();
FetchResult XOR_L();
FetchResult XOR_ADDR_HL();

FetchResult OR_D8();
FetchResult OR_A();
FetchResult OR_B();
FetchResult OR_C();
FetchResult OR_D();
FetchResult OR_E();
FetchResult OR_H();
FetchResult OR_L();
FetchResult OR_ADDR_HL();

FetchResult CP_D8();
FetchResult CP_A();
FetchResult CP_B();
FetchResult CP_C();
FetchResult CP_D();
FetchResult CP_E();
FetchResult CP_H();
FetchResult CP_L();
FetchResult CP_ADDR_HL();

FetchResult PUSH_AF();
FetchResult PUSH_BC();
FetchResult PUSH_DE();
FetchResult PUSH_HL();

FetchResult POP_AF();
FetchResult POP_BC();
FetchResult POP_DE();
FetchResult POP_HL();

FetchResult ADC_A_D8();
FetchResult ADC_A_A();
FetchResult ADC_A_B();
FetchResult ADC_A_C();
FetchResult ADC_A_D();
FetchResult ADC_A_E();
FetchResult ADC_A_H();
FetchResult ADC_A_L();
FetchResult ADC_A_ADDR_HL();

FetchResult LDH_ADDR_A8_A();
FetchResult LDH_A_ADDR_A8();
FetchResult LD_ADDR_C_A();

FetchResult SBC_A_D8();
FetchResult SBC_A_A();
FetchResult SBC_A_B();
FetchResult SBC_A_C();
FetchResult SBC_A_D();
FetchResult SBC_A_E();
FetchResult SBC_A_H();
FetchResult SBC_A_L();
FetchResult SBC_A_ADDR_HL();

FetchResult PREFIX_CB();

FetchResult LD_ADDR_HLD_A();
FetchResult LD_A_ADDR_HLD();

FetchResult CPL();
