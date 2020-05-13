#include <cinttypes>
#include <cpu/Cpu.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>

#include "BitOperations.h"
#include "gui/Gui.h"
#include <File.h>
#include <thread>
#include <GameBoy.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/gl.h>

void render_ppu(GameBoy& gameboy) {

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(glGetError() != GL_NO_ERROR) {
        std::cerr << "Failed to bind texture\n";
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);  //Always set the base and max mipmap levels of a texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

    constexpr auto target = GL_TEXTURE_2D;
    constexpr auto level = 0;
    constexpr auto internal_format = GL_RGBA;
    constexpr GLsizei width = 160;
    constexpr GLsizei height = 144;
    constexpr auto border = 0;
    constexpr auto format = GL_RGBA;
    constexpr auto type = GL_UNSIGNED_INT_8_8_8_8;
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(target, level, internal_format, 
        width, height, border, 
        format, type, 
        (GLvoid*) gameboy.ppu()->screen().data());

    ImGui::Begin("PPU");
    ImGui::Image((void*)(intptr_t) texture, ImVec2(width*3, height*3)); 
    ImGui::End();
}

void render_cpu(Cpu& cpu)
{
    ImGui::Begin("Cpu!");
    ImGui::Text("Current Opcode: %i.", cpu.m_memory_controller->read(cpu.m_program_counter));
    ImGui::Text("Register A: %i.", cpu.m_reg_a);
    ImGui::SameLine();
    ImGui::Text("Register F: %i.", cpu.m_reg_f);

    ImGui::Text("Register B: %i.", cpu.m_reg_b);
    ImGui::SameLine();
    ImGui::Text("Register C: %i.", cpu.m_reg_c);

    ImGui::Text("Register D: %i.", cpu.m_reg_d);
    ImGui::SameLine();
    ImGui::Text("Register E: %i.", cpu.m_reg_e);

    ImGui::Text("Register H: %i.", cpu.m_reg_h);
    ImGui::SameLine();
    ImGui::Text("Register L: %i.", cpu.m_reg_l);

    bool zero_flag = is_set(cpu.m_reg_f, 7);
    ImGui::Checkbox("Zero Flag: ", &zero_flag);
    ImGui::SameLine();

    bool subtract_flag = is_set(cpu.m_reg_f, 6);
    ImGui::Checkbox("Subtract Flag: ", &subtract_flag);
    ImGui::SameLine();

    bool half_carry = is_set(cpu.m_reg_f, 5);
    ImGui::Checkbox("Half Carry Flag", &half_carry);
    ImGui::SameLine();

    bool carry_flag = is_set(cpu.m_reg_f, 4);
    ImGui::Checkbox("Carry flag: ", &carry_flag);
    ImGui::SameLine();

    ImGui::End();
}

void render_disassembly(Cpu& cpu)
{
    ImGui::Begin("Disassembled!");

    ImGui::BeginChild("Scrolling Text");
    for (int n = 0; n < 50; n++) {
        ImGui::Text("Some Text: %i", n);
    }
    ImGui::EndChild();

    ImGui::End();
}

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
            render_cpu(*(gameboy->cpu()));
            render_ppu(*gameboy);
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