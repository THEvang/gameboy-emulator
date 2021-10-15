#include "Cpu/Cpu.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

uint16_t read_register_pair(Cpu cpu, Cpu_Register r1, Cpu_Register r2) {
    return combine_bytes(cpu.registers[r1], cpu.registers[r2]);
}

void set_initial_state(Cpu* cpu) {

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

    cpu->memory_controller->write(cpu->memory_controller, 0xFF00, 0x3F);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF04, 0xCC);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF05, 0);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF06, 0);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF07, 0);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF10, 0x80);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF11, 0xBF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF12, 0xF3);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF14, 0xBF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF16, 0x3F);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF17, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF19, 0xBF);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF1A, 0x7F);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF1B, 0xFF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF1C, 0x9F);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF1E, 0xBF);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF20, 0xFF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF21, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF22, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF23, 0xBF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF24, 0x77);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF25, 0xF3);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF26, 0xF1);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF40, 0x91);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF42, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF43, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF45, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF47, 0xFC);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF48, 0xFF);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF49, 0xFF);

    cpu->memory_controller->write(cpu->memory_controller, 0xFF4A, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFF4B, 0x00);
    cpu->memory_controller->write(cpu->memory_controller, 0xFFFF, 0x00);
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