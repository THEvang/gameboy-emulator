#include "Memory/Memory.h"

Memory::Memory(const std::vector<uint8_t>& memory) 
    : m_memory(memory)
{
}

Memory::Memory(const int size) 
    : m_memory(size, 0)
{}

uint8_t Memory::read(const uint16_t address) const {
    return m_memory[address];
}

void Memory::write(const uint16_t address, const uint8_t value) {
    m_memory[address] = value;
}