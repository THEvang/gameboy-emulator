#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "Emulator.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, GameBoyState* gameboy_state) {

    gameboy_state->memory_bank_controller.rom = rom->data;
    gb_memory_set_initial_state(&gameboy_state->memory_bank_controller, header);
    
    gameboy_state->ppu = (PPU) {{0},  {0xFFFFFFFF, 0xA9A9A9FF, 0x545454FF, 0x000000FF}, 0};

    gameboy_state->timer.prev_delay = false;
    gameboy_state->timer.tima_has_overflowed = false;
    gameboy_state->timer.tima_speed = 1024;
    gameboy_state->memory_bank_controller.div_register = 0xABCC;

    gb_cpu_set_initial_state(&gameboy_state->cpu);
}
