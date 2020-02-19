#include <cpu/Operations.h>

void NOP(Cpu& cpu) {
    return;
}



void LDB(Cpu& cpu) {
    cpu.m_reg_b = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LDC(Cpu& cpu) {
    cpu.m_reg_c = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LDD(Cpu& cpu) {
    cpu.m_reg_d = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LDE(Cpu& cpu) {
    cpu.m_reg_e = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LDH(Cpu& cpu) {
    cpu.m_reg_h = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void LDL(Cpu& cpu) {
    cpu.m_reg_l = cpu.m_memory_controller->read(cpu.m_program_counter+1);
    cpu.m_cycles += 8;
    cpu.m_program_counter += 2;
}

void INCBC(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented Operation: INC BC");
}

void INCB(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented Operation: INC B");
}

void DECB(Cpu& cpu) {
    throw UnimplementedOperation("Unimplemented Operation: DEC B");
}