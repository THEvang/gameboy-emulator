#include "Cpu/Adressing_Modes.hpp"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"

//Addressing Modes
Operand immediate(Cpu& cpu) {
    cpu.program_counter += 2;
    return {read(cpu.memory_controller,cpu.program_counter-1)};
}

Operand immediate_extended(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;
    return combine_bytes(read(cpu.memory_controller,pc-1), read(cpu.memory_controller,pc-2));
}

Operand hl_addressing(Cpu& cpu) {
    cpu.program_counter++;
    const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
    return read(cpu.memory_controller,address);
}

// Operand relative_address(Cpu& cpu) {
//     cpu.program_counter += 2;
//     const auto pc = cpu.program_counter;
//     return pc + static_cast<int8_t>(read(cpu.memory_controller,pc-1));
// }

Operand extended_address(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;
    const auto address = combine_bytes(read(cpu.memory_controller,pc-1), read(cpu.memory_controller,pc-2));
    return read(cpu.memory_controller,address);
}

Operand implied(Cpu& cpu) {
    cpu.program_counter++;
    return {static_cast<uint8_t>(0)};   
}

Operand none(Cpu&) {
    return {static_cast<uint8_t>(0)};
}