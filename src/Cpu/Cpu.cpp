#include "Cpu/Cpu.hpp"

#include "Memory/Memory_Controller.hpp"

Cpu::Cpu(MemoryBankController* memory_controller)
    : m_memory_controller(memory_controller)
{
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