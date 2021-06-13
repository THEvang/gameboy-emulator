#include "Gui/Gui.hpp"

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
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    

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
}

void gb_render(Gb_Gui* gui, GameBoy* gameboy) {

    // Start the Dear ImGui frame
    render_ppu(gui, gameboy);
    SDL_RenderPresent(gui->renderer);
}

void render_ppu(Gb_Gui* gui, GameBoy* gameboy) {

    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*) &(gameboy->ppu.screen.pixels[0]),
    160, 144,
    32, 4*160,
    0xFF000000,
    0x00FF0000,
    0x0000FF00,
    0x000000FF);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gui->renderer, surf);

    SDL_RenderCopy(gui->renderer, texture, NULL, NULL);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}