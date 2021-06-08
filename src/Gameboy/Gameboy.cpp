#include <stdio.h>

#include "Gameboy.hpp"
#include "Cpu/Opcodes.hpp"
#include "Cpu/Interpreter.hpp"

GameBoy::GameBoy(const std::vector<uint8_t>& rom)
    : m_cartridge_memory(rom)
    , m_memory_bank_controller(m_cartridge_memory) 
    , m_cpu(&m_memory_bank_controller)
    , m_timer(&m_memory_bank_controller)
    , m_interrupt_handler(&m_memory_bank_controller)
    , m_ppu(&m_memory_bank_controller)
    , m_joypad_controller(&m_interrupt_handler)
    {}

void GameBoy::run() {

    try {
        
        const auto opcode = m_cpu.m_memory_controller->read(m_cpu.m_program_counter);

        auto instruction = fetch(static_cast<Opcode>(opcode));

        auto cycles = 4;
        if(!m_cpu.m_is_halted) {
            auto operand = instruction.read_operand(m_cpu);
            cycles = instruction.execute(m_cpu, operand);
        } else {
            m_cpu.m_is_halted = m_interrupt_handler.should_exit_halt();
        }

        m_timer.increment(cycles);
        m_ppu.step(cycles);
            
        if(m_cpu.m_interrupts_enabled) {
            const auto interrupt_cycles = m_interrupt_handler.interrupts(m_cpu);
            m_timer.increment(interrupt_cycles);
        }

        if(m_cpu.m_should_enable_interrupts) {
            m_cpu.m_interrupts_enabled = true;
            m_cpu.m_should_enable_interrupts = false;
        } else if(m_cpu.m_should_disable_interrupts) {
            m_cpu.m_interrupts_enabled = false;
            m_cpu.m_should_disable_interrupts = false;
        }
    }
    catch (std::exception& err)  {
        printf("%s\n", err.what());
        exit(1);
    }
}

Cpu* GameBoy::cpu() {
    return &m_cpu;
}

PPU* GameBoy::ppu() {
    return &m_ppu;
}

Interrupt_Handler* GameBoy::interrupt_handler() { 
    return &m_interrupt_handler;
}

Joypad_Controller* GameBoy::joypad_controller() { 
    return &m_joypad_controller;
}

MemoryBankController* GameBoy::memory_controller() {
    return &m_memory_bank_controller;
}

Timer* GameBoy::timer() {
    return &m_timer;
}