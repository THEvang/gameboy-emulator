#include "Cpu/Adressing_Modes.h"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

//Addressing Modes
void implied(Cpu* cpu) {
    cpu->program_counter++;
}

uint8_t immediate_byte(Cpu* cpu) {
    cpu->program_counter += 2;
    return gb_read(cpu->memory_controller, cpu->program_counter-1);
}

uint16_t immediate_word(Cpu* cpu) {
    cpu->program_counter += 3;
    const uint16_t pc = cpu->program_counter;

    return combine_bytes(gb_read(cpu->memory_controller, pc - 1), gb_read(cpu->memory_controller, pc - 2));
}

uint8_t hl_addressing(Cpu* cpu) {
    cpu->program_counter++;
    const uint16_t address = combine_bytes(cpu->registers[Register_H], cpu->registers[Register_L]);
    return gb_read(cpu->memory_controller,address);
}