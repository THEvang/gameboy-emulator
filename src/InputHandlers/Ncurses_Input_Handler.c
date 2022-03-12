#include "Ncurses_Input_Handler.h"
#include <ncurses.h>

void ncurses_input_handler_init() {}

int ncurses_input_handler(Input* i) {

    switch(getch()) {
        case 'x':
            i->type = KeyDown;
            i->button = Button_Start;
            return 1;
    }
    return 0;
}

void ncurses_input_handler_cleanup() {}