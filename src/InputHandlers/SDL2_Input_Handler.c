#include <SDL2/SDL.h>
#include "SDL2_Input_Handler.h"

void sdl2_input_handler_init() {}
void sdl2_input_handler_cleanup() {}

int sdl2_input_handler(Input* i) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        
        case SDL_QUIT:
            i->type = Quit;
            return 1;
        
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                i->type = Quit;
                return 1;
            }
            break;
        
        case SDL_KEYDOWN:
            i->type = KeyDown;
            switch(event.key.keysym.sym) {
                case SDLK_z:
                    i->button = Button_A;
                    return 1;
                case SDLK_x:
                    i->button = Button_B;
                    return 1;
                case SDLK_RETURN:
                    i->button = Button_Start;
                    return 1;
                case SDLK_BACKSPACE:
                    i->button = Button_Select;
                    return 1;
                case SDLK_w:
                    i->button = Button_Up;
                    return 1;
                case SDLK_s:
                    i->button = Button_Down;
                    return 1;
                case SDLK_d:
                    i->button = Button_Right;
                    return 1;
                case SDLK_a:
                    i->button = Button_Left;
                    return 1;
                default:
                    break;
            }
        break;

        case SDL_KEYUP:
            i->type = KeyUp;
            switch(event.key.keysym.sym) {
                case SDLK_z:
                    i->button = Button_A;
                    return 1;
                case SDLK_x:
                    i->button = Button_B;
                    return 1;
                case SDLK_RETURN:
                    i->button = Button_Start;
                    return 1;
                case SDLK_BACKSPACE:
                    i->button = Button_Select;
                    return 1;
                case SDLK_w:
                    i->button = Button_Up;
                    return 1;
                case SDLK_s:
                    i->button = Button_Down;
                    return 1;
                case SDLK_d:
                    i->button = Button_Right;
                    return 1;
                case SDLK_a:
                    i->button = Button_Left;
                    return 1;
                default:
                    break;
            }
        break;

        default:
            break;
        }
    }

    return 0;
}