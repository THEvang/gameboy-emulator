#pragma once

#include "Gameboy/Gameboy.h"
#include "Emulator.h"

RenderState terminal_render_init();
void terminal_render(GameBoyState*, RenderState);
void terminal_render_cleanup(RenderState);