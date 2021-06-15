#pragma once

#include <SDL2/SDL.h>
#include "Gameboy/Gameboy.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Gb_Gui {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Gb_Gui;

void init_gui(Gb_Gui*);
void gb_render(Gb_Gui*, GameBoy*);
void render_ppu(Gb_Gui*, GameBoy*);


#ifdef __cplusplus
}
#endif