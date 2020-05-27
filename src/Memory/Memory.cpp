#include "Memory/Memory.h"

Memory::Memory(const std::vector<uint8_t>& memory) 
    : m_memory(memory)
{
}

Memory::Memory(const int size) 
    : m_memory(size, 0)
{}

uint8_t Memory::read(uint16_t address) const noexcept {
    return m_memory[address];
}

void Memory::write(uint16_t address, uint8_t value) {
    m_memory[address] = value;
}