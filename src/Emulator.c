#include <stdio.h>
#include <time.h>

#include "Emulator.h"
#include "Memory/Memory_Banks.h"
#include "Renderers/SDL2_Renderer.h"
#include "InputHandlers/SDL2_Input_Handler.h"

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, Emulator* emulator) {

    emulator->gameboy_state.memory_bank_controller.rom = rom->data;

    emulator->gameboy_state.memory_bank_controller.banking_register_1 = 1;
    emulator->gameboy_state.memory_bank_controller.banking_register_2 = 0;
    emulator->gameboy_state.memory_bank_controller.rom_bank_mask = header->rom_banks - 1;
    emulator->gameboy_state.memory_bank_controller.ram_bank_mask = header->rom_banks == 1 ? header->rom_banks :
        header->rom_banks -1;

    emulator->gameboy_state.memory_bank_controller.ram_enabled = false;
    emulator->gameboy_state.memory_bank_controller.banking_mode = Banking_Mode_ROM;
    emulator->gameboy_state.memory_bank_controller.buttons = 0xFF;
    emulator->gameboy_state.cpu.memory_controller = &emulator->gameboy_state.memory_bank_controller;

    const Cartridge_Type mb_type = header->type;
    set_io(&emulator->gameboy_state.memory_bank_controller, mb_type);
    
    emulator->gameboy_state.ppu.scanline_counter = 0;

    emulator->gameboy_state.timer.prev_delay = false;
    emulator->gameboy_state.timer.tima_has_overflowed = false;
    emulator->gameboy_state.timer.tima_speed = 1024;
    emulator->gameboy_state.memory_bank_controller.div_register = 0xABCC;

    set_initial_state(&emulator->gameboy_state.cpu);
    
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
                        key_up(&emulator->gameboy_state.memory_bank_controller, i.button);
                        break;
                    case KeyDown:
                        key_down(&emulator->gameboy_state.memory_bank_controller, i.button);
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