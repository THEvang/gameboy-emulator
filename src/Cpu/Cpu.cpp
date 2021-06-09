#include "Cpu/Cpu.hpp"
#include "Utilities/BitOperations.hpp"
#include "Memory/Memory_Controller.hpp"

uint16_t read_register_pair(Cpu cpu, Cpu_Register r1, Cpu_Register r2) {
    return combine_bytes(cpu.registers[r1], cpu.registers[r2]);
}

Cpu::Cpu(MemoryBankController* memory_controller)
    : memory_controller(memory_controller)
{
    registers[Register_A] = 0x01;
    registers[Register_B] = 0x00;
    registers[Register_C] = 0x13;
    registers[Register_D] = 0x00;
    registers[Register_E] = 0xD8;
    registers[Register_F] = 0xB0;
    registers[Register_H] = 0x01;
    registers[Register_L] = 0x4D;

    memory_controller->write(0xFF05, 0);
    memory_controller->write(0xFF06, 0);
    memory_controller->write(0xFF07, 0);

    memory_controller->write(0xFF10, 0x80);
    memory_controller->write(0xFF11, 0xBF);
    memory_controller->write(0xFF12, 0xF3);

    memory_controller->write(0xFF14, 0xBF);
    memory_controller->write(0xFF16, 0x3F);
    memory_controller->write(0xFF17, 0x00);
    memory_controller->write(0xFF19, 0xBF);

    memory_controller->write(0xFF1A, 0x7F);
    memory_controller->write(0xFF1B, 0xFF);
    memory_controller->write(0xFF1C, 0x9F);
    memory_controller->write(0xFF1E, 0xBF);

    memory_controller->write(0xFF20, 0xFF);
    memory_controller->write(0xFF21, 0x00);
    memory_controller->write(0xFF22, 0x00);
    memory_controller->write(0xFF23, 0xBF);
    memory_controller->write(0xFF24, 0x77);
    memory_controller->write(0xFF25, 0xF3);
    memory_controller->write(0xFF26, 0xF1);

    memory_controller->write(0xFF40, 0x91);
    memory_controller->write(0xFF42, 0x00);
    memory_controller->write(0xFF43, 0x00);
    memory_controller->write(0xFF45, 0x00);
    memory_controller->write(0xFF47, 0xFC);
    memory_controller->write(0xFF48, 0xFF);
    memory_controller->write(0xFF49, 0xFF);

    memory_controller->write(0xFF4A, 0x00);
    memory_controller->write(0xFF4B, 0x00);
    memory_controller->write(0xFFFF, 0x00);
}

bool test_flag(uint8_t flags, Cpu_Flag flag) {
    return test_bit_8bit(flags, flag);
}

void set_flag(uint8_t* flags, Cpu_Flag flag) {
    set_bit(*flags, flag);
}

void clear_flag(uint8_t* flags, Cpu_Flag flag) {
    clear_bit(*flags, flag);
}

//Addressing Modes
Operand immediate(Cpu& cpu) {
    cpu.program_counter += 2;
    return {cpu.memory_controller->read(cpu.program_counter-1)};
}

Operand immediate_extended(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;
    return combine_bytes(cpu.memory_controller->read(pc-1), cpu.memory_controller->read(pc-2));
}

Operand hl_addressing(Cpu& cpu) {
    cpu.program_counter++;
    const auto address = combine_bytes(cpu.registers[Register_H], cpu.registers[Register_L]);
    return cpu.memory_controller->read(address);
}

// Operand relative_address(Cpu& cpu) {
//     cpu.program_counter += 2;
//     const auto pc = cpu.program_counter;
//     return pc + static_cast<int8_t>(cpu.memory_controller->read(pc-1));
// }

Operand extended_address(Cpu& cpu) {
    cpu.program_counter += 3;
    const auto pc = cpu.program_counter;
    const auto address = combine_bytes(cpu.memory_controller->read(pc-1), cpu.memory_controller->read(pc-2));
    return cpu.memory_controller->read(address);
}

Operand implied(Cpu& cpu) {
    cpu.program_counter++;
    return {static_cast<uint8_t>(0)};   
}

Operand none(Cpu&) {
    return {static_cast<uint8_t>(0)};
}