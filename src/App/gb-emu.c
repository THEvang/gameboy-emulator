#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "Gui.h"
#include "Utilities/File.h"
#include "Gameboy/Gameboy.h"
#include "Cpu/Cpu.h"
#include "Gameboy/Rom_Info.h"

void render_main(GameBoy* gameboy) {

    clock_t start = clock(); 
    clock_t stop = clock();

    Gb_Gui gui;
    init_gui(&gui);

    bool done = false;
    while (!done) {

        
        gb_run(gameboy);
        double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
        if( duration >= 16e-3) {
            start = clock();

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

            gb_render(&gui, gameboy);
        }

        // if (gameboy->memory_bank_controller->memory[0xFF02] == 0x81) {
        //     printf("%c", gameboy->memory_bank_controller->memory[0xFF01]);
        //     fflush(stdout);
        //     gameboy->memory_bank_controller->memory[0xFF02] = 0;
        // }

        stop = clock();
    }
}

void gb_print_usage() {
    printf("Gameboy Emulator\n");
    printf("gb-emu <rom_file>\n");
    printf("-i Inspect rom without running the emulator\n");
}

int get_n_rom_banks(uint8_t* rom) {
    
    switch (rom[0x0148]) {
            case 0x00:
                return 2;
            case 0x01:
                return 4;
            case 0x02:
                return 8;
            case 0x03:
                return 16;
            case 0x04:
                return 32;
            case 0x05:
                return 64;
            case 0x06:
                return 128;
            case 0x07:
                return 256;
            case 0x08:
                return 512;
            case 0x52:
                return 72;
            case 0x53:
                return 80;
            case 0x54:
                return 96;
            default:
                return 0;
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

int main(int argc, char* argv[])
{
    if (argc < 2) {
        gb_print_usage();
        exit(1);
    }

    char* rom_path = argv[argc-1];

    gb_Rom rom;
    load_rom(&rom, rom_path);

    if (!rom.data) {
        printf("Unable to find Rom: %s\n", rom_path);
        exit(1);
    }

    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            gb_print_rom_info(&rom);
            exit(0);
        }
    }

    MemoryBankController mc;
    mc.rom = rom.data;

    mc.rom_bank_number = 1;
    mc.rom_bank_mask = get_rom_bank_mask(mc.rom);
    mc.n_rom_banks = get_n_rom_banks(mc.rom);

    mc.ram_enabled = false;
    mc.ram_bank_mask = get_ram_bank_mask(mc.rom);
    mc.ram_bank_number = 0;
    mc.banking_mode = Banking_Mode_ROM;

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
    gameboy.timer.tima_speed = 1024;
    gameboy.memory_bank_controller->div_register = 0xABCC;

    render_main(&gameboy);
    return 0;
}