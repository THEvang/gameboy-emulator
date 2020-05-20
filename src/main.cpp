#include <cinttypes>
#include <chrono>
#include <iostream>

#include "Gui/Gui.h"
#include "Gui/Renderers.h"
#include <File.h>
#include <GameBoy.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


void render_main(GameBoy* gameboy) {

    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    try {
        Gui gui;

        bool done = false;
        while (!done) {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
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
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            gameboy->joypad_controller()->press_button(Buttons::Left);
                        break;
                        
                        case SDLK_RIGHT:
                            gameboy->joypad_controller()->press_button(Buttons::Right);
                        break;
                        
                        case SDLK_DOWN:
                            gameboy->joypad_controller()->press_button(Buttons::Down);
                        break;

                        case SDLK_SPACE:
                            gameboy->joypad_controller()->press_button(Buttons::Select);
                        break;

                        case SDLK_RETURN:
                            gameboy->joypad_controller()->press_button(Buttons::Start);
                        break;

                        case SDLK_x:
                            gameboy->joypad_controller()->press_button(Buttons::A);
                        break;

                        case SDLK_z:
                            gameboy->joypad_controller()->press_button(Buttons::B);
                        break;
                    }
                break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            gameboy->joypad_controller()->release_button(Buttons::Left);
                        break;
                        
                        case SDLK_RIGHT:
                            gameboy->joypad_controller()->release_button(Buttons::Right);
                        break;
                        
                        case SDLK_DOWN:
                            gameboy->joypad_controller()->release_button(Buttons::Down);
                        break;

                        case SDLK_SPACE:
                            gameboy->joypad_controller()->release_button(Buttons::Select);
                        break;

                        case SDLK_RETURN:
                            gameboy->joypad_controller()->release_button(Buttons::Start);
                        break;

                        case SDLK_x:
                            gameboy->joypad_controller()->release_button(Buttons::A);
                        break;

                        case SDLK_z:
                            gameboy->joypad_controller()->release_button(Buttons::B);
                        break;
                    }
                    break;
                default:
                    break;
                }
            }

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
                render_disassembly(*gameboy);
                render_menu();
                gui.render();
            }
            stop = std::chrono::high_resolution_clock::now();
        }
    } catch (const std::exception& err) {
        std::cerr << err.what();
        return;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Please provide rom\n";
        return 1;
    }

    const auto rom_path = argv[1];
    const auto rom = load_rom(rom_path);
    if (!rom) {
        std::cerr << "Unable to find Rom: " << rom_path << "\n";
        return 1;
    }

    GameBoy gameboy(*rom);
    render_main(&gameboy);
    return 0;
}