#include "GameBoy.hpp"
#include "Cpu/Opcodes.hpp"
#include <iostream>
#include "Cpu/Interpreter.hpp"

GameBoy::GameBoy(const std::vector<uint8_t>& rom) {

    Memory cartridge_memory(rom);

    m_memory_bank_controller = std::make_unique<MemoryBankController>(cartridge_memory);
    m_cpu = std::make_unique<Cpu>(m_memory_bank_controller.get());
    m_timer = std::make_unique<Timer>(m_memory_bank_controller.get());
    m_interrupt_handler = std::make_unique<Interrupt_Handler>(m_memory_bank_controller.get());
    m_ppu = std::make_unique<PPU>(m_memory_bank_controller.get());
    m_joypad_controller = std::make_unique<Joypad_Controller>(m_interrupt_handler.get());
}

void GameBoy::run() {

    try {
        
        const auto opcode = m_cpu->m_memory_controller->read(m_cpu->m_program_counter);

        auto instruction = fetch(static_cast<Opcode>(opcode));

        auto cycles = 4;
        if(!m_cpu->m_is_halted) {
            auto operand = instruction.read_operand(*m_cpu);
            cycles = instruction.execute(*m_cpu, operand);
        } else {
            m_cpu->m_is_halted = m_interrupt_handler->should_exit_halt();
        }

        m_timer->increment(cycles);
        m_ppu->step(cycles);
            
        if(m_cpu->m_interrupts_enabled) {
            const auto interrupt_cycles = m_interrupt_handler->interrupts(*m_cpu);
            m_timer->increment(interrupt_cycles);
        }

        if(m_cpu->m_should_enable_interrupts) {
            m_cpu->m_interrupts_enabled = true;
            m_cpu->m_should_enable_interrupts = false;
        } else if(m_cpu->m_should_disable_interrupts) {
            m_cpu->m_interrupts_enabled = false;
            m_cpu->m_should_disable_interrupts = false;
        }
    }
    catch (std::exception& err)  {
        std::cerr << err.what();
        exit(0);
    }
}

Cpu* GameBoy::cpu() const {
    return m_cpu.get();
}

PPU* GameBoy::ppu() const {
    return m_ppu.get();
}

Interrupt_Handler* GameBoy::interrupt_handler() const { 
    return m_interrupt_handler.get();
}

Joypad_Controller* GameBoy::joypad_controller() const { 
    return m_joypad_controller.get();
}

MemoryBankController* GameBoy::memory_controller() const {
    return m_memory_bank_controller.get();
}

Timer* GameBoy::timer() const {
    return m_timer.get();
}