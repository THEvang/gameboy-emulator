
#pragma once

#include "Emulator.h"

void ncurses_input_handler_init();
int ncurses_input_handler(Input* i);
void ncurses_input_handler_cleanup();