#include <SDL2/SDL.h>
#include "SDL2_Renderer.h"

typedef struct SDL2State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen;
} SDL2State;

void sdl2_render_ppu(GameBoyState* gameboy, SDL2State* gui) {

    SDL_UpdateTexture(gui->screen, NULL, (void*) &(gameboy->ppu.screen.pixels[0]), 4 * 160);
    SDL_RenderCopy(gui->renderer, gui->screen, NULL, NULL);
}

void* sdl2_init_gui() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL ERROR: %s\n", SDL_GetError());
        return NULL;
    }

    SDL2State* s = malloc(sizeof(SDL2State));
    s->window = SDL_CreateWindow("Gameboy Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        5*160, 
        5*144, 
        SDL_WINDOW_RESIZABLE);
    

    if(!s->window) {
        printf("Failed to create SDL Window: %s\n", SDL_GetError());
        return NULL;
    }

    s->renderer = SDL_CreateRenderer(
        s->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!s->renderer) {
        printf("SDL ERROR: Unable to create renderer: %s\n", SDL_GetError());
        return NULL;
    }

    s->screen = SDL_CreateTexture(s->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 160, 144);
    return s;
}

void sdl2_gb_render(GameBoyState* gameboy, void* user_data) {

    SDL2State* gui = (SDL2State*) user_data;

    SDL_RenderClear(gui->renderer);
    sdl2_render_ppu(gameboy, gui);
    SDL_RenderPresent(gui->renderer);
}