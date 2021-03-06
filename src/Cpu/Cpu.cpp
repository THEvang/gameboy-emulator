#include "Cpu/Cpu.hpp"
#include "BitOperations.hpp"
#include "Memory/Memory_Controller.hpp"

Cpu::Cpu(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
{
    m_registers[static_cast<int>(Register::A)] = 0x01;
    m_registers[static_cast<int>(Register::B)] = 0x00;
    m_registers[static_cast<int>(Register::C)] = 0x13;
    m_registers[static_cast<int>(Register::D)] = 0x00;
    m_registers[static_cast<int>(Register::E)] = 0xD8;
    m_registers[static_cast<int>(Register::F)] = 0xB0;
    m_registers[static_cast<int>(Register::H)] = 0x01;
    m_registers[static_cast<int>(Register::L)] = 0x4D;

    m_memory_controller->write(0xFF05, 0);
    m_memory_controller->write(0xFF06, 0);
    m_memory_controller->write(0xFF07, 0);

    m_memory_controller->write(0xFF10, 0x80);
    m_memory_controller->write(0xFF11, 0xBF);
    m_memory_controller->write(0xFF12, 0xF3);

    m_memory_controller->write(0xFF14, 0xBF);
    m_memory_controller->write(0xFF16, 0x3F);
    m_memory_controller->write(0xFF17, 0x00);
    m_memory_controller->write(0xFF19, 0xBF);

    m_memory_controller->write(0xFF1A, 0x7F);
    m_memory_controller->write(0xFF1B, 0xFF);
    m_memory_controller->write(0xFF1C, 0x9F);
    m_memory_controller->write(0xFF1E, 0xBF);

    m_memory_controller->write(0xFF20, 0xFF);
    m_memory_controller->write(0xFF21, 0x00);
    m_memory_controller->write(0xFF22, 0x00);
    m_memory_controller->write(0xFF23, 0xBF);
    m_memory_controller->write(0xFF24, 0x77);
    m_memory_controller->write(0xFF25, 0xF3);
    m_memory_controller->write(0xFF26, 0xF1);

    m_memory_controller->write(0xFF40, 0x91);
    m_memory_controller->write(0xFF42, 0x00);
    m_memory_controller->write(0xFF43, 0x00);
    m_memory_controller->write(0xFF45, 0x00);
    m_memory_controller->write(0xFF47, 0xFC);
    m_memory_controller->write(0xFF48, 0xFF);
    m_memory_controller->write(0xFF49, 0xFF);

    m_memory_controller->write(0xFF4A, 0x00);
    m_memory_controller->write(0xFF4B, 0x00);
    m_memory_controller->write(0xFFFF, 0x00);
}

int Cpu::to_index(Cpu::Flag f) {
    return static_cast<int>(f);
}

void Cpu::set(Register r, uint8_t value) {
    m_registers[static_cast<size_t>(r)] = value;
}

uint8_t Cpu::get(Register r) const {
    return m_registers[static_cast<size_t>(r)];
}

uint8_t& Cpu::get(Register r) {
    return m_registers[static_cast<size_t>(r)];
}

uint16_t Cpu::get(std::pair<Register, Register> r_pair) const {
    return combine_bytes(get(r_pair.first), get(r_pair.second));
}

bool Cpu::test_flag(const Flag& flag) const {
    return is_set(get(Register::F), static_cast<int>(flag));
}

void Cpu::set_flag(const Cpu::Flag& flag) {
    set_bit(m_registers[static_cast<int>(Cpu::Register::F)], static_cast<int>(flag));
}

void Cpu::clear_flag(const Cpu::Flag& flag) {
    clear_bit(m_registers[static_cast<int>(Cpu::Register::F)], static_cast<int>(flag));
}


//Addressing Modes
Operand immediate(Cpu& cpu) {
    cpu.m_program_counter += 2;
    return {cpu.m_memory_controller->read(cpu.m_program_counter-1)};
}

Operand immediate_extended(Cpu& cpu) {
    cpu.m_program_counter += 3;
    const auto pc = cpu.m_program_counter;
    return combine_bytes(cpu.m_memory_controller->read(pc-1), cpu.m_memory_controller->read(pc-2));
}

Operand hl_addressing(Cpu& cpu) {
    cpu.m_program_counter++;
    const auto address = combine_bytes(cpu.get(Cpu::Register::H), cpu.get(Cpu::Register::L));
    return cpu.m_memory_controller->read(address);
}

// Operand relative_address(Cpu& cpu) {
//     cpu.m_program_counter += 2;
//     const auto pc = cpu.m_program_counter;
//     return pc + static_cast<int8_t>(cpu.m_memory_controller->read(pc-1));
// }

Operand extended_address(Cpu& cpu) {
    cpu.m_program_counter += 3;
    const auto pc = cpu.m_program_counter;
    const auto address = combine_bytes(cpu.m_memory_controller->read(pc-1), cpu.m_memory_controller->read(pc-2));
    return cpu.m_memory_controller->read(address);
}

Operand implied(Cpu& cpu) {
    cpu.m_program_counter++;
    return {static_cast<uint8_t>(0)};   
}

Operand none(Cpu&) {
    return {static_cast<uint8_t>(0)};
}