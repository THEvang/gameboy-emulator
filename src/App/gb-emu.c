#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "Utilities/File.h"
#include "Gameboy/Gameboy.h"
#include "Cpu/Cpu.h"
#include "Gameboy/Rom_Info.h"
#include "Input/Joypad.h"
#include "Emulator.h"

#include "Renderers/SDL2_Renderer.h"
#include "InputHandlers/SDL2_Input_Handler.h"

void render_main(Emulator* emu, RenderState render_state, GameBoyState* gameboy) {

    clock_t start = clock(); 
    clock_t stop = clock();

    while (true) {
      
        gb_run(gameboy);
        double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
        if( duration >= 16e-3 && gameboy->memory_bank_controller->memory[0xFF44] > 144) {
            start = clock();

            Input i;
            if(emu->input_handler(&i)) {
                switch(i.type) {
                    case Quit:
                        return;
                    case KeyUp:
                        key_up(gameboy->memory_bank_controller, i.button);
                        break;
                    case KeyDown:
                        key_down(gameboy->memory_bank_controller, i.button);
                        break;
                }
            }

            emu->render(gameboy, render_state);
        }

        // if (gameboy->memory_bank_controller->memory[0xFF02] == 0x81) {
        //     printf("%c", gameboy->memory_bank_controller->memory[0xFF01]);
        //     fflush(stdout);
        //     gameboy->memory_bank_controller->memory[0xFF02] = 0;
        // }

        stop = clock();
    }
}



uint8_t get_rom_bank_mask(uint8_t* rom) {

    switch (rom[0x0148]) {
        case 0x00:
            return 0x1;
        case 0x01:
            return 0x3;
        case 0x02:
            return 0x7;
        case 0x03:
            return 0xF;
        case 0x04:
            return 0x1F;
        case 0x05:
            return 0x3F;
        case 0x06:
            return 0x7F;
        case 0x07:
            return 0xFF;
        case 0x08:
            printf("8MByte - 512 Banks\n");
            break;
        case 0x52:
            printf("1.1MByte - 72 Banks\n");
            break;
        case 0x53:
            printf("1.2MByte - 80 Banks\n");
            break;
        case 0x54:
            printf("1.5Mbyte - 96 Banks\n");
            break;
        default:
            return 0x00;
            break;
    }
}

uint8_t get_ram_bank_mask(uint8_t* rom) {
    switch (rom[0x0149]) {
        case 0x00:
        case 0x01:
        case 0x02:
            return 0x00;
        case 0x03:
            return 0x03;
        case 0x04:
            return 0x0F;
        case 0x05:
            return 0x07;
        default:
            return 0x00;
    }
}

void gb_usage(void) {

    printf("Usage: gb-emu [options] rom\n");
    printf("  Options:\n");
    printf("    -i,\t Inspect rom without running the emulator\n");
    printf("    -h,\t Display this help message\n");
}

int main(int argc, char* argv[]) {

    const char* options = "ihv";
    int opt;
    bool print_info = false;
    while( (opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'h':
            case '?':
                gb_usage();
                exit(1);
            case 'i':
                print_info = true;
                break;
        }
    }

    if (optind >= argc) {
        gb_usage();
        exit(1);
    }

    char* rom_path = argv[optind];

    gb_Rom rom;
    load_rom(&rom, rom_path);

    if (!rom.data) {
        printf("Unable to find Rom: %s\n", rom_path);
        exit(1);
    }

    if(print_info) {
        gb_print_rom_info(&rom);
        exit(0);
    }

    MemoryBankController mc;
    mc.rom = rom.data;

    mc.rom_bank_number = 1;
    mc.rom_bank_mask = get_rom_bank_mask(mc.rom);

    mc.ram_enabled = false;
    mc.ram_bank_mask = get_ram_bank_mask(mc.rom);
    mc.ram_bank_number = 0;
    mc.banking_mode = Banking_Mode_ROM;
    mc.buttons = 0xFF;

    const Memory_Bank_Type mb_type = get_memory_bank_type(&rom);
    
    set_io(&mc, mb_type);
    GameBoyState gameboy;
    gameboy.memory_bank_controller = &mc;
    
    gameboy.cpu.memory_controller = gameboy.memory_bank_controller;
    set_initial_state(&(gameboy.cpu));

    gameboy.ppu.scanline_counter = 0;

    gameboy.timer.prev_delay = false;
    gameboy.timer.tima_has_overflowed = false;
    gameboy.timer.tima_speed = 1024;
    gameboy.memory_bank_controller->div_register = 0xABCC;

    Emulator emu;
    
    emu.input_handler_init = sdl2_input_handler_init;
    emu.input_handler = sdl2_input_handler;
    emu.input_handler_cleanup = sdl2_input_handler_cleanup;

    emu.render_init = sdl2_render_init;
    emu.render = sdl2_render;
    emu.render_cleanup = sdl2_render_cleanup;

    RenderState render_state = emu.render_init();
    render_main(&emu, render_state, &gameboy);

    emu.input_handler_cleanup();
    emu.render_cleanup(render_state);

    return 0;
}