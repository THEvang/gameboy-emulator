#pragma once

#include "Emulator.h"

void sdl2_input_handler_init();
int sdl2_input_handler(Input* i);
void sdl2_input_handler_cleanup();