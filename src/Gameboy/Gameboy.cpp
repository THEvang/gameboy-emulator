#include <stdio.h>

#include "Gameboy.hpp"
#include "Cpu/Opcodes.h"
#include "Cpu/Interpreter.hpp"
#include "Cpu/Interrupts.h"

GameBoy::GameBoy(MemoryBankController* mc)
    : memory_bank_controller(mc) 
    , ppu(memory_bank_controller)
    {
        joypad.direction_keys = 0b1111;
        joypad.button_keys = 0b1111;
        memory_bank_controller->joypad = &joypad;

        cpu.memory_controller = memory_bank_controller;
        set_initial_state(&cpu);

        timer.prev_delay = false;
        timer.tima_has_overflowed = false;
        timer.div_value = 0xABCC;
}

void GameBoy::run() {

    const auto opcode = gb_read(memory_bank_controller, cpu.program_counter);

    auto instruction = fetch(static_cast<Opcode>(opcode));

    auto cycles = 4;
    if(!cpu.is_halted) {
        auto operand = instruction.read_operand(&cpu);
        cycles = instruction.execute(cpu, operand);
    } else {
        cpu.is_halted = should_exit_halt(memory_bank_controller);
    }

    gb_timer_increment(&timer, memory_bank_controller, cycles);
    ppu.step(cycles);
        
    if(cpu.interrupts_enabled) {
        const auto interrupt_cycles = handle_interrupts(&cpu);
        gb_timer_increment(&timer, memory_bank_controller, interrupt_cycles);
    }

    if(cpu.should_enable_interrupts) {
        cpu.interrupts_enabled = true;
        cpu.should_enable_interrupts = false;
    } else if(cpu.should_disable_interrupts) {
        cpu.interrupts_enabled = false;
        cpu.should_disable_interrupts = false;
    }
}