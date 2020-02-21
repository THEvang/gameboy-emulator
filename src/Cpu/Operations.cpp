#include <cpu/Operations.h>
#include <BitOperations.h>
#include <string>

UnimplementedOperation::UnimplementedOperation(const std::string& msg)
    : runtime_error(msg) {

}

void NOP(Cpu& cpu) {
    cpu.m_cycles =4;
    cpu.m_program_counter++;
}

void STOP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: STOP");
}

void HALT(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: HALT");
}

void RST(int) {
    throw UnimplementedOperation("Unimplemented operation: RST"); 
}

void DI(Cpu& cpu) {
    
    cpu.m_cycles += 4;
    cpu.m_enabled_interrupts = false;
    cpu.m_program_counter++;
}

void EI(Cpu& cpu) {
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

void RET_NZ(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET NZ");
}

void RET_Z(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET Z");
}

void RET_NC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET NC");
}

void RET_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RET C");
}

void RETI(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration: RETI");
}

void JUMP(Cpu& cpu) {

    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter + 1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter + 2);
    const auto address = combine_bytes(upper, lower);

    cpu.m_program_counter = address;
    cpu.m_cycles += 12;
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

void LD_A_D8(Cpu& cpu) {

    cpu.m_reg_a = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LD_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A A");
}

void LD_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A B");
}

void LD_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A C");
}

void LD_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A D");
}

void LD_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A E");
}

void LD_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A H");
}

void LD_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A L");
}

void LD_A_ADDR_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR BC");
}

void LD_A_ADDR_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR DE");
}

void LD_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented opration LDA A ADDR HL");
}

void LD_A_ADDR_A16(Cpu& cpu) {
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
    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter+2);
    const auto address = combine_bytes(upper, lower);

    cpu.m_reg_a = cpu.m_memory_controller->read(address);
    cpu.m_cycles += 16;
    cpu.m_program_counter += 3;
}

void LD_BC_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD BC D16");
}

void LD_DE_D16(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD DE D16");
}
void LD_HL_D16(Cpu& cpu) {

    cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter+2);

    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
}

void LD_HL_SPR8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD HL SPR8");
}

void LD_SP_D16(Cpu& cpu) {

    const auto lower = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    const auto upper = cpu.m_memory_controller->read(cpu.m_program_counter+2);
    const auto address = combine_bytes(upper, lower);

    cpu.m_stack_ptr = address;
    cpu.m_cycles += 12;
    cpu.m_program_counter += 3;
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

void INC_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: INC SP");
}

void DEC_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC A");
}

void DEC_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC B");
}

void DEC_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC C");
}

void DEC_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC D");
}

void DEC_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC E");
}

void DEC_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC H");
}

void DEC_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC L");
}

void DEC_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC BC");
}

void DEC_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC DE");
}

void DEC_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC HL");
}

void DEC_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC ADDR HL");
}

void DEC_SP(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DEC SP");
}

void SCF(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SCF");
}

void CCF(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: CCF");
}

void RRCA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RRCA");
}

void RRA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RRA");
}

void RLA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RLA");
}

void RLCA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: RLCA");
}

void DDA(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: DDA");
}

void ADD_SP_R8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADD SP R8");
}

void AND_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND D8");
}

void AND_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND A");
}

void AND_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND B");
}

void AND_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND C");
}

void AND_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND D");
}

void AND_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND E");
}

void AND_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND H");
}

void AND_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND L");
}

void AND_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: AND ADDR HL");
}

void XOR_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR D8");
}

void XOR_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR A");
}

void XOR_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR B");
}

void XOR_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR C");
}

void XOR_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR D");
}

void XOR_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR E");
}

void XOR_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR H");
}

void XOR_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR L");
}

void XOR_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: XOR ADDR HL");
}

void OR_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR D8");
}

void OR_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR A");
}

void OR_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR B");
}

void OR_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR C");
}

void OR_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR D");
}

void OR_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR E");
}

void OR_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR H");
}

void OR_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR L");
}

void OR_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: OR ADDR HL");
}

void CP_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP D8");
}

void CP_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP A");
}

void CP_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP B");
}

void CP_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP C");
}

void CP_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP D");
}

void CP_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP E");
}

void CP_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP H");
}

void CP_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP L");
}

void CP_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation. CP ADDR HL");
}

void PUSH_AF(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: PUSH AF");
}

void PUSH_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: PUSH BC");
}

void PUSH_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: PUSH DE");
}

void PUSH_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: PUSH HL");
}

void POP_AF(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: POP AF");
}

void POP_BC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: POP BC");
}

void POP_DE(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: POP DE");
}

void POP_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: POP HL");
}

void ADC_A_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A D8");
}

void ADC_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A A");
}

void ADC_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A B");
}

void ADC_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A C");
}

void ADC_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A D");
}

void ADC_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A E");
}

void ADC_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A H");
}

void ADC_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A L");
}

void ADC_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: ADC A ADDR HL");
}

void LDH_ADDR_A8_A(Cpu& cpu) {

    const uint16_t address = 0xFF00 + cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_memory_controller->write(address, cpu.m_reg_a);
    cpu.m_cycles += 12;
    cpu.m_program_counter += 2;
}

void LDH_A_ADDR_A8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation LDH A ADDR A8");
}

void LD_ADDR_C_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: LD ADDR C A");
}

void SBC_A_D8(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A D8");
}

void SBC_A_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A A");
}

void SBC_A_B(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A B");
}

void SBC_A_C(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A C");
}

void SBC_A_D(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A D");
}

void SBC_A_E(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A E");
}

void SBC_A_H(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A H");
}

void SBC_A_L(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A L");
}

void SBC_A_ADDR_HL(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A ADDR HL");
}

void PREFIX_CB(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: PREFIX CB");
}

void LD_ADDR_HLD_A(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented operation: SBC A ADDR HL");
}