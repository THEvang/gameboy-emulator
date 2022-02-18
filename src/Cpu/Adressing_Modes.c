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

uint8_t immediate_byte(Cpu* cpu, MemoryBankController* mc) {

    if (cpu->halt_bug_triggered) {
        cpu->halt_bug_triggered = false;
        cpu->program_counter--;
    }

    cpu->program_counter += 2;
    return mc->read(mc, cpu->program_counter - 1);
}

uint16_t immediate_word(Cpu* cpu, MemoryBankController* mc) {

    if (cpu->halt_bug_triggered) {
        cpu->halt_bug_triggered = false;
        cpu->program_counter--;
    }

    cpu->program_counter += 3;
    const uint16_t pc = cpu->program_counter;

    return combine_bytes(mc->read(mc, pc - 1), mc->read(mc, pc - 2));
}

uint8_t hl_addressing(Cpu* cpu, MemoryBankController* mc) {

    if (cpu->halt_bug_triggered) {
        cpu->program_counter--;
        cpu->halt_bug_triggered = false;
    }

    cpu->program_counter++;
    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    return mc->read(mc, address);
}