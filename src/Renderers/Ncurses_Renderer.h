#pragma once

#include "Gameboy/Gameboy.h"
#include "Emulator.h"

Renderer terminal_render_init();
void terminal_render(GameBoyState*, Renderer);
void terminal_render_cleanup(Renderer);