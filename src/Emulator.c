#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "Emulator.h"
#include "Renderers/SDL2_Renderer.h"
#include "InputHandlers/SDL2_Input_Handler.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

void gb_key_down(MemoryBankController* mc, Button button) {
    mc->buttons &= ~button;
    gb_request_interrupt(mc, Interrupts_Joypad);
}

void gb_key_up(MemoryBankController* mc, Button button) {
    mc->buttons |= button;
}

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, Emulator* emulator) {

    emulator->gameboy_state.memory_bank_controller.rom = rom->data;
    gb_memory_set_initial_state(&emulator->gameboy_state.memory_bank_controller, header);
    
    emulator->gameboy_state.ppu = (PPU) {{0},  {0xFFFFFFFF, 0xA9A9A9FF, 0x545454FF, 0x000000FF}, 0};

    emulator->gameboy_state.timer.prev_delay = false;
    emulator->gameboy_state.timer.tima_has_overflowed = false;
    emulator->gameboy_state.timer.tima_speed = 1024;
    emulator->gameboy_state.memory_bank_controller.div_register = 0xABCC;

    gb_cpu_set_initial_state(&emulator->gameboy_state.cpu);
    
    sdl2_input_handler_init();
    emulator->input_handler = sdl2_input_handler;
    emulator->input_handler_cleanup = sdl2_input_handler_cleanup;

    emulator->renderer = sdl2_render_init();
    emulator->render = sdl2_render;
    emulator->render_cleanup = sdl2_render_cleanup;
}

void gb_run_emulator(Emulator* emulator) {

    clock_t start = clock(); 
    clock_t stop = clock();

    while (true) {
      
        gb_run(&emulator->gameboy_state);
        double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
        if( duration >= 16e-3 && emulator->gameboy_state.memory_bank_controller.memory[0xFF44] > 144) {
            start = clock();

            Input i;
            if(emulator->input_handler(&i)) {
                switch(i.type) {
                    case Quit:
                        return;
                    case KeyUp:
                        gb_key_up(&emulator->gameboy_state.memory_bank_controller, i.button);
                        break;
                    case KeyDown:
                        gb_key_down(&emulator->gameboy_state.memory_bank_controller, i.button);
                        break;
                }
            }

            emulator->render(&emulator->gameboy_state, emulator->renderer);
        }

        // if (gameboy->memory_bank_controller->memory[0xFF02] == 0x81) {
        //     printf("%c", gameboy->memory_bank_controller->memory[0xFF01]);
        //     fflush(stdout);
        //     gameboy->memory_bank_controller->memory[0xFF02] = 0;
        // }

        stop = clock();
    }
}