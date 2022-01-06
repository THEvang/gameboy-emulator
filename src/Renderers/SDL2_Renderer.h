#pragma once

#include "Gameboy/Gameboy.h"
#include "Emulator.h"

RenderState sdl2_init_gui();
void sdl2_gb_render(GameBoyState*, RenderState);