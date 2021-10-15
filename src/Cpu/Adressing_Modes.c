#include "Cpu/Adressing_Modes.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

//Addressing Modes
void implied(Cpu* cpu) {

    if (cpu->halt_bug_triggered) {
        cpu->halt_bug_triggered = false;
        cpu->program_counter--;
    }

    cpu->program_counter++;
}

uint8_t immediate_byte(Cpu* cpu) {

    if (cpu->halt_bug_triggered) {
        cpu->halt_bug_triggered = false;
        cpu->program_counter--;
    }

    cpu->program_counter += 2;
    return cpu->memory_controller->read(cpu->memory_controller, cpu->program_counter - 1);
}

uint16_t immediate_word(Cpu* cpu) {

    if (cpu->halt_bug_triggered) {
        cpu->halt_bug_triggered = false;
        cpu->program_counter--;
    }

    cpu->program_counter += 3;
    const uint16_t pc = cpu->program_counter;

    return combine_bytes(cpu->memory_controller->read(cpu->memory_controller, pc - 1), cpu->memory_controller->read(cpu->memory_controller, pc - 2));
}

uint8_t hl_addressing(Cpu* cpu) {

    if (cpu->halt_bug_triggered) {
        cpu->program_counter--;
        cpu->halt_bug_triggered = false;
    }

    cpu->program_counter++;
    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    return cpu->memory_controller->read(cpu->memory_controller, address);
}