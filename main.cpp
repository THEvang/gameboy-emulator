#include <iostream>
#include <cpu/Cpu.h>
#include <fstream>
#include <cinttypes>
#include <vector>
#include <iterator>
#include <fstream>

#include <File.h>
#include <MBC1.h>
#include <Memory.h>
#include <cpu/Operations.h>

int main() {


    const auto rom = load_rom("../tests/gb-test-roms/cpu_instr/cpu_instr.gb");
    std::vector<uint8_t> raw_internal(0xFFFF, 0);
    
    Memory rom_memory(rom);
    Memory internal_memory(raw_internal);
    MBC1 mbc1(internal_memory, rom_memory);

    Cpu cpu;
    cpu.m_memory_controller = &mbc1;

    try {
        while(true) {
            step(cpu);
            std::cout << "Blarg has written: " <<  (int) cpu.m_memory_controller->read(0xFF01) << "\n";
        }
    }   
    catch (std::exception& err)  {
        std::cout << err.what();
        return 1;
    }

    return 0;
}