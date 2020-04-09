#include <GameBoy.h>
#include <iostream>
#include "memory_controllers/MBC1.h"
#include "memory_controllers/Memory.h"
#include "Timer.h"
#include "cpu/Interrupt_Handler.h"

void GameBoy::run(const std::vector<uint8_t>& rom) {
    
    Memory rom_memory(rom);
    Memory internal_memory(std::vector<uint8_t>(0xFFFF,0));
    MBC1 mbc1(internal_memory, rom_memory);

    Cpu cpu(&mbc1);
    Timer timer(&internal_memory);
    Interrupt_Handler interrupt_handler(&mbc1);
    while(!cpu.should_stop)
    {
        try {
            
            auto [cycles, delta_pc, operation] = fetch(cpu);
            
            if(!cpu.m_is_halted) {
                cpu.m_program_counter += delta_pc;
                operation(cpu);
            } else {
                cycles = 4;
                cpu.m_is_halted = interrupt_handler.should_exit_halt();
            }

            timer.increment(cycles);
            
            if(cpu.m_interrupts_enabled) {
                const auto interrupt_cycles = interrupt_handler.interrupts(cpu);
                timer.increment(interrupt_cycles);
            }

            if(cpu.m_should_enable_interrupts) {
                cpu.m_interrupts_enabled = true;
                cpu.m_should_enable_interrupts = false;
            } else if(cpu.m_should_disable_interrupts) {
                cpu.m_interrupts_enabled = false;
                cpu.m_should_disable_interrupts = false;
            }

        }   
        catch (std::exception& err)  {
            std::cout << err.what();
            return;
        }

        if(cpu.m_memory_controller->read(0xFF02) == 0x81) {
            std::cout << static_cast<char>(cpu.m_memory_controller->read(0xFF01));
            cpu.m_memory_controller->write(0xFF02, 0);
        }
    }
}