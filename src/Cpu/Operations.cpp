#include <cpu/Operations.h>

void NOP(Cpu& cpu) {
    return;
}

void STOP() {
    throw UnimplementedOperation("Unimplemented operation: STOP");
}

void HALT() {
    throw UnimplementedOperation("Unimplemented operation: HALT");
}

void RST() {
    throw UnimplementedOperation("Unimplemented operation: RST"); 
}

void DI() {
    throw UnimplementedOperation("Unimplemented operation: DI");
}

void EI() {
    throw UnimplementedOperation("Unimplemented operation: EI");
}

void JR(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: JR");
}

void JR_NZ(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: JR NZ");
}

void JR_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: JR Z");
}

void JR_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: JR NC");
}

void JR_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: JR C");
}

void RET(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET");
}

void RET_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET_Z");
}

void RET_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET NC");
}

void RETI(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: RETI");
}

void JUMP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP");
}

void JUMP_NZ(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP NZ");
}

void JUMP_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP Z");
}

void JUMP_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP NC");
}

void JUMP_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP C");
}

void JUMP_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: JUMP ADDR HL");
}

void CALL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL");
}

void CALL_NZ(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL NZ");
}

void CALL_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL Z");
}

void CALL_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL NC");
}

void CALL_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: CALL C");
}

void LDA_A_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A D8");
}

void LDA_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A A");
}

void LDA_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A B");
}

void LDA_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A C");
}

void LDA_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A D");
}

void LDA_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A E");
}

void LDA_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A H");
}

void LDA_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A L");
}

void LDA_A_ADDR_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR BC");
}

void LDA_A_ADDR_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR DE");
}

void LDA_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR HL");
}

void LDA_A_ADDR_A16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR");
}

void LD_A_ADDR_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR C");
}

void LD_ADDR_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation LD ADDR SP");
}

void LDI_ADDR_HL_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation LDI_ADDR_HL_A");
}

void LDI_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDI A ADDR HL");
}

void LD_ADDR_BC_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LD ADDR BC A");
}

void LD_ADDR_DE_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LD ADDR DE A");
}
void LD_ADDR_HL_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LD ADDR HL A");
}

void LD_B_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B D8");
}

void LD_B_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B A");
}

void LD_B_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B B");
}

void LD_B_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B C");
}

void LD_B_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B D");
}

void LD_B_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B E");
}

void LD_B_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B H");
}

void LD_B_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B L");
}

void LD_B_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD B ADDR HL");
}

void LD_C_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C D8");
}

void LD_C_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C D8");
}

void LD_C_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C A");
}

void LD_C_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C B");
}

void LD_C_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C C");
}

void LD_C_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C D");
}

void LD_C_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C E");
}

void LD_C_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C H");
}

void LD_C_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C L");
}

void LD_C_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD C ADDR HL");
}

void LD_D_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D D8");
}

void LD_D_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D A");
}

void LD_D_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D B");
}

void LD_D_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D C");
}

void LD_D_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D D");
}

void LD_D_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D E");
}

void LD_D_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D H");
}

void LD_D_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D L");
}

void LD_D_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD D ADDR HL");
}

void LD_E_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E D8");
}

void LD_E_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E A");
}

void LD_E_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E B");
}

void LD_E_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E C");
}

void LD_E_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E D");
}

void LD_E_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E E");
}

void LD_E_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E H");
}

void LD_E_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E L");
}

void LD_E_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD E ADDR HL");
}

void LD_H_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H D8");
}

void LD_H_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H A");
}

void LD_H_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H B");
}

void LD_H_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H C");
}

void LD_H_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H D");
}

void LD_H_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H E");
}

void LD_H_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H H");
}

void LD_H_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H L");
}

void LD_H_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD H ADDR HL");
}

void LD_L_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L D8");
}

void LD_L_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L A");
}

void LD_L_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L B");
}

void LD_L_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L C");
}

void LD_L_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L D");
}

void LD_L_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L E");
}

void LD_L_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L H");
}

void LD_L_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L L");
}

void LD_L_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD L ADDR HL");
}

void LD_ADDR_HL_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL A");
}

void LD_ADDR_HL_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL B");
}

void LD_ADDR_HL_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL C");
}

void LD_ADDR_HL_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL D");
}

void LD_ADDR_HL_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL E");
}

void LD_ADDR_HL_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL H");
}

void LD_ADDR_HL_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL L");
}

void LD_ADDR_HL_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR HL ADDR HL");
}

void LD_ADDR_A16_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR A16 A");
}

void LD_BC_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD BC D16");
}

void LD_DE_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD DE D16");
}
void LD_HL_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD HL D16");
}

void LD_HL_SPR8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD HL SPR8");
}

void LD_SP_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD SP D16");
}

void LD_SP_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD SP HL");
}

void ADD_A_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A D8");
}

void ADD_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A A");
}

void ADD_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A B");
}

void ADD_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A C");
}

void ADD_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A D");
}

void ADD_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A E");
}

void ADD_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A H");
}

void ADD_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A L");
}

void ADD_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD A ADDR HL");
}

void ADD_HL_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD HL BC");
}

void ADD_HL_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD HL DE");
}

void ADD_HL_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD HL HL");
}

void SUB_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB D8");
}

void SUB_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB A");
}

void SUB_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB B");
}

void SUB_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB C");
}

void SUB_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB D");
}

void SUB_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB E");
}

void SUB_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB H");
}

void SUB_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB L");
}

void SUB_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SUB ADDR HL");
}

void INC_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC A");
}

void INC_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC B");
}

void INC_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC C");
}

void INC_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC D");
}

void INC_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC E");
}

void INC_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC H");
}

void INC_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC L");
}

void INC_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC BC");
}

void INC_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC DE");
}

void INC_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC HL");
}

void INC_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC ADDR HL");
}