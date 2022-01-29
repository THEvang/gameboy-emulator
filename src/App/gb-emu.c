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

    Emulator emulator = gb_init_emulator(rom);

    RenderState render_state = emulator.render_init();
    render_main(&emulator, render_state, &emulator.gameboy_state);

    emulator.input_handler_cleanup();
    emulator.render_cleanup(render_state);

    return 0;
}