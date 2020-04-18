#include <cinttypes>
#include <cpu/Cpu.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "BitOperations.h"
#include "Gui.h"
#include <File.h>

#include <GameBoy.h>

void render_cpu(Cpu& cpu, std::vector<char> blarg)
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

    std::string s;
    for (const auto e : blarg) {
        s += e;
    }

    ImGui::Text("Serial Output: %s", s.c_str()); //(char)cpu.m_memory_controller->read(0xFF01));

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

    GameBoy gameboy;
    gameboy.run(*rom);

    return 0;

    // Gui gui;
    // bool done = false;
    // while (!done)
    // {
    //     // Poll and handle events (inputs, window resize, etc.)
    //     // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    //     // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    //     // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    //     // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event))
    //     {
    //         ImGui_ImplSDL2_ProcessEvent(&event);
    //         if (event.type == SDL_QUIT)
    //             done = true;
    //         if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(gui.window))
    //             done = true;
    //         if(event.type == SDL_KEYDOWN) {
    //             switch(event.key.keysym.sym) {
    //                 case SDLK_RETURN:
    //                     step(cpu);
    //                     break;
    //             }
    //         }
    //     }

    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplSDL2_NewFrame(gui.window);
    //     ImGui::NewFrame();

    //     try {
    //         step(cpu);
    //         if(cpu.m_memory_controller->read(0xFF02) == 0x81) {
    //             blarg.push_back(cpu.m_memory_controller->read(0xFF01));
    //         }
    //         }
    //         catch (std::exception& err)  {
    //             std::cout << err.what();
    //             return 1;
    //         }

    //     render_disassembly(cpu);

    //     render_cpu(cpu, blarg);

    //     gui.render();

    // }

    // return 0;
}