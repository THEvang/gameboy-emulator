#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <time.h>

#include "Gui/Gui.h"
#include "Utilities/File.h"
#include "Gameboy/Gameboy.h"
#include "Cpu/Cpu.h"

void render_main(GameBoy* gameboy) {

    clock_t start = clock(); 
    clock_t stop = clock();

    Gb_Gui gui;
    init_gui(&gui);

    bool done = false;
    while (!done) {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            
            case SDL_QUIT:
                done = true;
                break;
            
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    done = true;
                }
                break;
            
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_z:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_A);
                        break;
                    case SDLK_x:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_B);
                        break;
                    case SDLK_RETURN:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Start);
                        break;
                    case SDLK_BACKSPACE:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Select);
                        break;
                    case SDLK_w:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Up);
                        break;
                    case SDLK_s:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Down);
                        break;
                    case SDLK_d:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Right);
                        break;
                    case SDLK_a:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Down, Button_Left);
                        break;
                }
            break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_z:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_A);
                        break;
                    case SDLK_x:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_B);
                        break;
                    case SDLK_RETURN:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Start);
                        break;
                    case SDLK_BACKSPACE:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Select);
                        break;
                    case SDLK_w:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Up);
                        break;
                    case SDLK_s:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Down);
                        break;
                    case SDLK_d:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Right);
                        break;
                    case SDLK_a:
                        input(&(gameboy->joypad), gameboy->memory_bank_controller, Key_Up, Button_Left);
                        break;
                }
            break;

            default:
                break;
            }
        }

        gb_run(gameboy);
        double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
        if( duration >= 16e-3) {
            start = clock();
            gb_render(&gui, gameboy);
        }

        if (gameboy->memory_bank_controller->memory[0xFF02] == 0x81) {
            printf("%c", gameboy->memory_bank_controller->memory[0xFF01]);
            fflush(stdout);
            gameboy->memory_bank_controller->memory[0xFF02] = 0;
        }

        stop = clock();
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Error: No input rom\n");
        exit(1);
    }

    char* rom_path = argv[1];

    gb_Rom rom;
    load_rom(&rom, rom_path);

    if (!rom.data) {
        printf("Unable to find Rom: %s\n", rom_path);
        exit(1);
    }

    for(int i = 0x0134; i <= 0x0143; i++) {
        printf("%c", rom.data[i]);
    }
    printf("\n");

    
    if (rom.data[0x0146] == 0x03) {
        printf("Super Gameboy support\n");
    }

    switch(rom.data[0x0147]) {
        case 0x00:
            printf("ROM ONLY\n");
            break;
        case 0x01:
            printf("MBC 1\n");
            break;
        case 0x02:
            printf("MBC 1 + RAM\n");
            break;
        case 0x03:
            printf("MBC 1 + RAM + Battery\n");
            break;
        case 0x05:
            printf("MBC 2\n");
            break;
    }

    printf("ROM SIZE: ");
    switch (rom.data[0x0148]) {
        case 0x00:
            printf("32kb - 2 Banks\n");
            break;
        case 0x01:
            printf("64kb - 4 Banks\n");
            break;
        case 0x02:
            printf("128kb - 8 Banks\n");
            break;
        case 0x03:
            printf("256kb - 16 Banks\n");
            break;
        case 0x04:
            printf("512kb - 32 Banks\n");
            break;
    }

    printf("RAM SIZE:");
    switch (rom.data[0x0149]) {
        case 0x00:
            printf("0 - No Ram\n");
            break;
        case 0x01:
            printf("2kb\n");
            break;
        case 0x02:
            printf("8kb\n");
            break;
    }

    MemoryBankController mc;
    mc.ram_enabled = false;
    mc.rom_bank_number = 1;
    mc.ram_bank_number = 0;
    mc.banking_mode = Banking_Mode_ROM;
    mc.rom = rom.data;

    GameBoy gameboy;
    gameboy.memory_bank_controller = &mc;
    gameboy.joypad.direction_keys = 0x0F;
    gameboy.joypad.button_keys = 0x0F;
    gameboy.memory_bank_controller->joypad = &(gameboy.joypad);

    gameboy.cpu.memory_controller = gameboy.memory_bank_controller;
    set_initial_state(&(gameboy.cpu));

    gameboy.ppu.scanline_counter = 0;

    gameboy.timer.prev_delay = false;
    gameboy.timer.tima_has_overflowed = false;
    gameboy.timer.div_value = 0xABCC;

    render_main(&gameboy);
    return 0;
}