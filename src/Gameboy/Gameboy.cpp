#include <stdio.h>

#include "Gameboy.hpp"
#include "Cpu/Opcodes.hpp"
#include "Cpu/Interpreter.hpp"

GameBoy::GameBoy(uint8_t* rom_data, size_t rom_size)
    : cartridge_memory(rom_data)
    , memory_bank_controller(cartridge_memory) 
    , timer(&memory_bank_controller)
    , interrupt_handler(&memory_bank_controller)
    , ppu(&memory_bank_controller)
    , joypad_controller(&interrupt_handler)
    {
        cpu.memory_controller = &memory_bank_controller;
        set_initial_state(&cpu);
    }

void GameBoy::run() {

    const auto opcode = memory_bank_controller.read(cpu.program_counter);

    auto instruction = fetch(static_cast<Opcode>(opcode));

    auto cycles = 4;
    if(!cpu.is_halted) {
        auto operand = instruction.read_operand(cpu);
        cycles = instruction.execute(cpu, operand);
    } else {
        cpu.is_halted = interrupt_handler.should_exit_halt();
    }

    timer.increment(cycles);
    ppu.step(cycles);
        
    if(cpu.interrupts_enabled) {
        const auto interrupt_cycles = interrupt_handler.interrupts(cpu);
        timer.increment(interrupt_cycles);
    }

    if(cpu.should_enable_interrupts) {
        cpu.interrupts_enabled = true;
        cpu.should_enable_interrupts = false;
    } else if(cpu.should_disable_interrupts) {
        cpu.interrupts_enabled = false;
        cpu.should_disable_interrupts = false;
    }
}