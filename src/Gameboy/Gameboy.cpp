#include "GameBoy.h"
#include "Cpu/Opcodes.h"
#include <iostream>
#include "Cpu/Interpreter.h"

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

        auto [delta_pc, operation] = fetch(static_cast<Opcode>(opcode));
        
        auto cycles = 4;

        if(!m_cpu->m_is_halted) {
            m_cpu->m_program_counter += static_cast<uint16_t>(delta_pc);
            cycles = operation(*m_cpu);
        } else {
            cycles = 4;
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
        std::cout << err.what();
        return;
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