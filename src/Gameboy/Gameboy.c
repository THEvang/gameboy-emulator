#include "Gameboy.h"
#include "Cpu/Opcodes.h"
#include "Cpu/Interpreter.h"
#include "Cpu/Interrupts.h"

void gb_run(GameBoy* gb) {

    int cycles = 4;

    if(!gb->cpu.is_halted) {
        const Opcode opcode = (Opcode) gb_read(gb->memory_bank_controller, gb->cpu.program_counter);
        cycles = execute(opcode, &(gb->cpu));
    } else {
        gb->cpu.is_halted = should_exit_halt(gb->memory_bank_controller);
    }

    gb_timer_increment(&(gb->timer), gb->memory_bank_controller, cycles);
    gb_ppu_step(&(gb->ppu), cycles);
        
    if(gb->cpu.interrupts_enabled) {
        const int interrupt_cycles = handle_interrupts(&(gb->cpu));
        gb_timer_increment(&(gb->timer), gb->memory_bank_controller, interrupt_cycles);
    }

    if(gb->cpu.should_enable_interrupts) {
        gb->cpu.interrupts_enabled = true;
        gb->cpu.should_enable_interrupts = false;
    } else if(gb->cpu.should_disable_interrupts) {
        gb->cpu.interrupts_enabled = false;
        gb->cpu.should_disable_interrupts = false;
    }
}