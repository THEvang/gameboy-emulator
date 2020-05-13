#include <GameBoy.h>
#include <iostream>
#include "memory_controllers/MBC1.h"

GameBoy::GameBoy(const std::vector<uint8_t>& rom) {
    

    Memory rom_memory(rom);
    Memory internal_memory(std::vector<uint8_t>(0xFFFF,0));
    
    m_memory_bank_controller = std::make_unique<MBC1>(internal_memory, rom_memory);

    m_cpu = std::make_unique<Cpu>(m_memory_bank_controller.get());
    m_timer = std::make_unique<Timer>(m_memory_bank_controller.get());
    m_interrupt_handler = std::make_unique<Interrupt_Handler>(m_memory_bank_controller.get());
    m_ppu = std::make_unique<PPU>(m_memory_bank_controller.get());
}

void GameBoy::run() {

    try {
        
        auto [cycles, delta_pc, operation] = fetch(*m_cpu);
        
        if(!m_cpu->m_is_halted) {
            m_cpu->m_program_counter += delta_pc;
            operation(*m_cpu);
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

    if(m_cpu->m_memory_controller->read(0xFF02) == 0x81) {
        std::cout << static_cast<char>(m_cpu->m_memory_controller->read(0xFF01));
        m_cpu->m_memory_controller->write(0xFF02, 0);
    }
}

Cpu* GameBoy::cpu() {
    return m_cpu.get();
}

PPU* GameBoy::ppu() {
    return m_ppu.get();
}