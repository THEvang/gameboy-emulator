#include <stdio.h>

#include "Gameboy.hpp"
#include "Cpu/Opcodes.hpp"
#include "Cpu/Interpreter.hpp"
#include "Cpu/Interrupts.h"

GameBoy::GameBoy(MemoryBankController* mc)
    : memory_bank_controller(mc) 
    , timer(memory_bank_controller)
    , ppu(memory_bank_controller)
    {
        joypad.direction_keys = 0b1111;
        joypad.button_keys = 0b1111;
        cpu.memory_controller = memory_bank_controller;

        set_initial_state(&cpu);
    }

void GameBoy::run() {

    const auto opcode = read(memory_bank_controller, cpu.program_counter);

    auto instruction = fetch(static_cast<Opcode>(opcode));

    auto cycles = 4;
    if(!cpu.is_halted) {
        auto operand = instruction.read_operand(cpu);
        cycles = instruction.execute(cpu, operand);
    } else {
        cpu.is_halted = should_exit_halt(memory_bank_controller);
    }

    timer.increment(cycles);
    ppu.step(cycles);
        
    if(cpu.interrupts_enabled) {
        const auto interrupt_cycles = handle_interrupts(&cpu);
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