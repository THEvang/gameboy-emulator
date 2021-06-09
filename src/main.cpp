#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <time.h>

#include "Gui/Gui.hpp"
#include "Gui/Renderers.hpp"
#include "Utilities/File.hpp"
#include "Gameboy/Gameboy.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Input/Keyboard.hpp"

void render_main(GameBoy* gameboy) {

    Keyboard_Emitter keyboard_emitter;
    keyboard_emitter.add_observer(gameboy->joypad_controller());

    SDL_SetEventFilter(keyboard_filter, static_cast<void*>(keyboard_emitter.get_queue()));

    clock_t start = clock(); 
    clock_t stop = clock();
    try {
        Gui gui;

        bool done = false;
        while (!done) {
            SDL_Event event;
            while (static_cast<bool>(SDL_PollEvent(&event)))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                switch (event.type)
                {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(gui.window())) {
                        done = true;
                    }
                    break;
                default:
                    break;
                }
            }

            keyboard_emitter.emitt();

            gameboy->run();
            double duration =  (double) (stop - start) / CLOCKS_PER_SEC;
            if( duration >= 16e-3) {
                start = clock();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame(gui.window());
                ImGui::NewFrame();
                render_cpu(*gameboy);
                render_ppu(*gameboy);
                render_cartridge_data(*gameboy);
                //render_disassembly(*gameboy);
                render_menu();
                gui.render();
            }
            stop = clock();
        }
    } catch (const std::exception& err) {
        printf("%s\n", err.what());
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Error: No input rom\n");
        exit(1);
    }

    char* rom_path = argv[1];

    gb_Rom rom;
    load_rom(&rom, rom_path);

    if (!rom.data) {
        printf("Unable to find Rom: %s\n", rom_path);
        exit(1);
    }

    GameBoy gameboy(rom.data, rom.size);
    render_main(&gameboy);
    return 0;
}