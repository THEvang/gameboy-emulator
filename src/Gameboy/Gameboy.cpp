#include <GameBoy.h>
#include <iostream>
#include <MBC1.h>
#include <Memory.h>

void GameBoy::run(const std::vector<uint8_t>& rom) {
    
    Memory rom_memory(rom);
    Memory internal_memory(std::vector<uint8_t>(0xFFFF,0));
    MBC1 mbc1(internal_memory, rom_memory);

    Cpu cpu(&mbc1);
    while(!cpu.should_stop)
    {
        try {
            
            auto [cycles, delta_pc, operation] = fetch(cpu);
            cpu.m_program_counter += delta_pc;
            //handle_interrupts(cpu);
            operation(cpu);
            //timer(cpu);

        }   
        catch (std::exception& err)  {
            std::cout << err.what();
            return;
        }

        if(cpu.m_memory_controller->read(0xFF02) == 0x81) {
            std::cout << (char) cpu.m_memory_controller->read(0xFF01) << "\n";
            cpu.m_memory_controller->write(0xFF02, 0);
        }
    }
}