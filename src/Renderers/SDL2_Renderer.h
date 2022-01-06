#pragma once

#include "Gameboy/Gameboy.h"
#include "Emulator.h"

RenderState sdl2_render_init();
void sdl2_render(GameBoyState*, RenderState);
void sdl2_render_cleanup(RenderState);