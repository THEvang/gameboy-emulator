#pragma once

#include <SDL2/SDL.h>
#include "Gameboy/Gameboy.hpp"

struct Gb_Gui {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void init_gui(Gb_Gui*);
void gb_render(Gb_Gui*, GameBoy*);
void render_ppu(Gb_Gui*, GameBoy*);