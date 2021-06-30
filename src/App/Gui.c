#include "Gui.h"

#include <stdio.h>

void init_gui(Gb_Gui* gui) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }

    gui->window = SDL_CreateWindow("Gameboy Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        5*160, 
        5*144, 
        SDL_WINDOW_RESIZABLE);
    

    if(!gui->window) {
        printf("Failed to create SDL Window: %s\n", SDL_GetError());
        exit(1);
    }

    gui->renderer = SDL_CreateRenderer(
        gui->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!gui->renderer) {
        printf("SDL ERROR: Unable to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    gui->screen = SDL_CreateTexture(gui->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 160, 144);
}

void gb_render(Gb_Gui* gui, GameBoy* gameboy) {

    SDL_RenderClear(gui->renderer);
    render_ppu(gui, gameboy);
    SDL_RenderPresent(gui->renderer);
}

void render_ppu(Gb_Gui* gui, GameBoy* gameboy) {

    SDL_UpdateTexture(gui->screen, NULL, (void*) &(gameboy->ppu.screen.pixels[0]), 4 * 160);
    SDL_RenderCopy(gui->renderer, gui->screen, NULL, NULL);
}