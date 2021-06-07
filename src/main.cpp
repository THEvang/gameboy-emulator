#define SDL_MAIN_HANDLED

#include <stdio.h>

#include <chrono>

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

    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
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
            std::chrono::duration<double, std::milli> dur = stop - start;
            if(dur.count() > 32) {
                start = std::chrono::high_resolution_clock::now();
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
            stop = std::chrono::high_resolution_clock::now();
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

    const auto rom_path = argv[1];
    const auto rom = load_rom(rom_path);
    if (rom.empty()) {
        printf("Unable to find Rom: %s\n", rom_path);
        exit(1);
    }

    GameBoy gameboy(rom);
    render_main(&gameboy);
    return 0;
}