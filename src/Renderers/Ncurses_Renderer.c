#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#include "Ncurses_Renderer.h"

typedef struct NcursesState {
    WINDOW* w;
} NcursesState;

Renderer terminal_render_init() {

    NcursesState* s = malloc(sizeof(NcursesState));

    s->w = initscr();
    noecho();
    nodelay(s->w, TRUE);
	keypad(s->w, TRUE);
    cbreak();

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_CYAN, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_MAGENTA);
    wresize(s->w, 144, 160);
    return s;
}

void terminal_render(GameBoyState* gb, Renderer s) {

    (void) s;

    refresh();

    for(int i = 0; i < 144; i++) {
        for(int j = 0; j < 160; j++) {
            switch(gb->ppu.screen_buffer[j + i * 160]) {
                case 0xFFFFFFFF:
                    attron(COLOR_PAIR(3));
                break;
                case 0x545454FF:
                    attron(COLOR_PAIR(2));
                break;
                case 0xA9A9A9FF:
                    attron(COLOR_PAIR(1));
                break;
                case 0x000000FF:
                    attron(COLOR_PAIR(4));
                break;
            }
            mvprintw(i, j, " ");
        }
    }
}


void terminal_render_cleanup(Renderer s) {
    (void) s;
    endwin();
}