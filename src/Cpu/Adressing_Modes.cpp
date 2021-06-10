#include "Cpu/Adressing_Modes.hpp"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

//Addressing Modes
Operand implied(Cpu& cpu) {
    cpu.program_counter++;

    Operand op;
    op.byte = 0;
    return op;   
}

Operand immediate(Cpu& cpu) {
    cpu.program_counter += 2;
    return {read(cpu.memory_controller,cpu.program_counter-1)};
}

Operand immediate_extended(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;

    Operand op;
    op.word = combine_bytes(read(cpu.memory_controller,pc-1), read(cpu.memory_controller,pc-2));
    return op;
}

Operand hl_addressing(Cpu& cpu) {
    cpu.program_counter++;
    const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);

    Operand op;
    op.byte = read(cpu.memory_controller,address);
}

Operand extended_address(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;
    const auto address = combine_bytes(read(cpu.memory_controller,pc-1), read(cpu.memory_controller,pc-2));

    Operand op;
    op.byte = read(cpu.memory_controller,address);
    return op;
}

Operand none(Cpu&) {

    Operand op;
    op.byte = 0;
    return op;
}