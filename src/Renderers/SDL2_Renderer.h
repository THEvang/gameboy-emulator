#include <SDL2/SDL.h>
#include "Gameboy/Gameboy.h"

typedef struct SDL2State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen;
} SDL2State;

void sdl2_init_gui(SDL2State*);
void sdl2_gb_render(GameBoyState*, void* user_data);
void sdl2_render_ppu(GameBoyState*, SDL2State*);