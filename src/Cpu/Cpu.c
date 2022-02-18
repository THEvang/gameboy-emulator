#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"

uint16_t read_register_pair(Cpu cpu, Cpu_Register r1, Cpu_Register r2) {
    return combine_bytes(cpu.registers[r1], cpu.registers[r2]);
}

void gb_cpu_set_initial_state(Cpu* cpu) {

    cpu->stack_ptr = 0xFFFE;
    cpu->program_counter = 0x0100;

    cpu->interrupts_enabled = false;
    cpu->should_enable_interrupts = false;
    cpu->should_disable_interrupts = false;
    cpu->should_stop = false;
    cpu->is_halted = false;
    cpu->halt_bug_triggered = false;
    
    cpu->registers[Register_A] = 0x01;
    cpu->registers[Register_B] = 0x00;
    cpu->registers[Register_C] = 0x13;
    cpu->registers[Register_D] = 0x00;
    cpu->registers[Register_E] = 0xD8;
    cpu->registers[Register_F] = 0xB0;
    cpu->registers[Register_H] = 0x01;
    cpu->registers[Register_L] = 0x4D;
}

bool test_flag(uint8_t flags, Cpu_Flag flag) {
    return flags & flag;
}

void set_flag(uint8_t* flags, Cpu_Flag flag) {
    *flags |= flag;
}

void clear_flag(uint8_t* flags, Cpu_Flag flag) {
    *flags &= ~flag;
}