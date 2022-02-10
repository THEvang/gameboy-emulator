#pragma once

#include "Gameboy/Gameboy.h"
#include "Emulator.h"

Renderer sdl2_render_init();
void sdl2_render(GameBoyState*, Renderer);
void sdl2_render_cleanup(Renderer);