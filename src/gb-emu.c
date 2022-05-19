#include <stdio.h>
#include <time.h>

#include "Gameboy/Cartridge.h"
#include "Emulator.h"
#include <SDL2/SDL.h>
#include "Cpu/Interrupts.h"

typedef struct SDL2State {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen;
} SDL2State;

int 
sdl2_initialize(SDL2State* s) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL ERROR: %s\n", SDL_GetError());
        return 1;
    }

    s->window = SDL_CreateWindow("Gameboy Emulator", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        5*160, 
        5*144, 
        0);
    

    if(!s->window) {
        printf("Failed to create SDL Window: %s\n", SDL_GetError());
        return 1;
    }

    s->renderer = SDL_CreateRenderer(
        s->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

  SDL_SetRenderDrawColor(s->renderer, 255, 255, 255, 255);

    if(!s->renderer) {
        printf("SDL ERROR: Unable to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTexture(s->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 160, 144);
    if(!texture) {
        printf("Failed to create SDL Texture: %s\n", SDL_GetError());
    }
    s->screen = texture;
	
    return 0;    
}

void 
sdl2_render(GameBoyState* gameboy, SDL2State* s) {

    SDL_RenderClear(s->renderer);
    SDL_UpdateTexture(s->screen, NULL, (void*) &(gameboy->ppu.screen_buffer[0]), 4 * 160);
    SDL_RenderCopy(s->renderer, s->screen, NULL, NULL);
    SDL_RenderPresent(s->renderer);
}

void gb_key_down(MemoryBankController* mc, Button button) {
    mc->buttons &= ~button;
    gb_request_interrupt(mc, Interrupts_Joypad);
}

void gb_key_up(MemoryBankController* mc, Button button) {
    mc->buttons |= button;
}

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, GameBoyState* gameboy_state) {

    gameboy_state->memory_bank_controller.rom = rom->data;
    gb_memory_set_initial_state(&gameboy_state->memory_bank_controller, header);
    
    gameboy_state->ppu = (PPU) {{0},  {0xFFFFFFFF, 0xA9A9A9FF, 0x545454FF, 0x000000FF}, 0};

    gameboy_state->timer.prev_delay = false;
    gameboy_state->timer.tima_has_overflowed = false;
    gameboy_state->timer.tima_speed = 1024;
    gameboy_state->memory_bank_controller.div_register = 0xABCC;

    gb_cpu_set_initial_state(&gameboy_state->cpu);
}

int
sdl2_handle_input(Input* i) {

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

void gb_run_emulator(GameBoyState* gameboy_state, SDL2State* s) {

    clock_t start = clock(); 
    clock_t stop = clock();

    while (true) {
      
        gb_run(gameboy_state);
        double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
        if( duration >= 16e-3 && gameboy_state->memory_bank_controller.memory[0xFF44] > 144) {
            start = clock();

            Input i;
            if(sdl2_handle_input(&i)) {
                switch(i.type) {
                    case Quit:
                        return;
                    case KeyUp:
                        gb_key_up(&gameboy_state->memory_bank_controller, i.button);
                        break;
                    case KeyDown:
                        gb_key_down(&gameboy_state->memory_bank_controller, i.button);
                        break;
                }
            }

            sdl2_render(gameboy_state, s);
        }

        stop = clock();
    }
}

int 
main(int argc, char* argv[]) {

    if (argc != 2) {
    	printf("Usage: gb-emu rom\n");
        return 1;
    }

    char* rom_path = argv[1];

    GameboyRom rom;
    if(gb_load_rom(&rom, rom_path)) {
        printf("ERROR\tFailed loading rom\t%s\n", rom_path);
        return 1;
    }

    SDL2State s;
    sdl2_initialize(&s);

    CartridgeHeader header;
    gb_parse_header(&rom, &header);

    GameBoyState gameboy_state;
    gb_init_emulator(&rom, &header, &gameboy_state);
    gb_run_emulator(&gameboy_state, &s);

    
    SDL_DestroyRenderer(s.renderer);
    SDL_DestroyTexture(s.screen);
    SDL_DestroyWindow(s.window);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    
    return 0;
}
