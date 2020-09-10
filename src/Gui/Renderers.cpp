#include <iostream>

#include "Gui/Renderers.hpp"
#include "imgui/imgui.h"
#include "Cpu/Opcodes.hpp"
#include "Disassembler/Disassembler.hpp"
#include "Memory/Cartridge.hpp"
#include "Disassembler/Ring_Buffer.hpp"
#include "BitOperations.hpp"

void render_disassembly(GameBoy const& gameboy) {

    static Ring_Buffer<Instruction_Info, 20> history;
    const auto opcode = gameboy.memory_controller()->read(gameboy.cpu()->m_program_counter);
    const auto instruction = disassemble(static_cast<Opcode>(opcode));
    history.write(instruction);

    const auto sorted_history = history.get_sorted();
    ImGui::Begin("Disassembly");
    ImGui::BeginChild("Disassembly_List");
    for(const auto& element : sorted_history) {

        ImGui::Text("%d: %s, %d", 
            static_cast<int>(element.opcode),
            element.name.c_str(),
            element.cycles);
    }

    ImGui::EndChild();
    ImGui::End();
}

void render_ppu(GameBoy const& gameboy) {

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

std::string to_name(Cpu::Register reg) {
    switch(reg) {
        case Cpu::Register::A:
            return {"A"};
        case Cpu::Register::B:
            return {"B"};
        case Cpu::Register::C:
            return {"C"};
        case Cpu::Register::D:
            return {"D"};
        case Cpu::Register::E:
            return {"E"};
        case Cpu::Register::H:
            return {"H"};
        case Cpu::Register::L:
            return {"L"};
    }
}

std::string to_name(Cpu::Flag flag) {
    switch(flag) {
        case Cpu::Flag::Carry:
            return {"Carry"};
        case Cpu::Flag::Half_Carry:
            return {"Half Carry"};
        case Cpu::Flag::Zero:
            return {"Zero"};
        case Cpu::Flag::Sub:
            return {"Sub"};
    }
}

void render_cpu(GameBoy const& gameboy) {
    
    const auto cpu = gameboy.cpu();

    ImGui::Begin("Cpu!");
    ImGui::Text("Current Opcode: %i.", cpu->m_memory_controller->read(cpu->m_program_counter));

    for(auto reg_index = 0; reg_index < 7; reg_index++) {
        const auto reg = static_cast<Cpu::Register>(reg_index);
        const auto register_name = to_name(reg);
        ImGui::Text("Register %s: %i.", register_name.c_str(), cpu->get(reg));
    }

    for(auto flag_index = 4; flag_index < 7; flag_index++) {
        const auto flag = static_cast<Cpu::Flag>(flag_index);
        const auto flag_name = to_name(flag);
        auto flag_status = cpu->test_flag(flag);
        ImGui::Text("%s Flag: ", flag_name.c_str());
        ImGui::SameLine();
        ImGui::Checkbox("", &flag_status);
    }
    ImGui::End();
}

void render_cartridge_data(GameBoy const& gameboy) {
    
    ImGui::Begin("Cartridge Header");
    const auto mbc_identifier = gameboy.memory_controller()->read(0x0147);
    const auto mbc_type = get_bank_type(mbc_identifier);
    std::string mbc_render {};

    switch(mbc_type) {
        case Bank_Type::Rom_Only:
            mbc_render = "Rom only";
        break;
        case Bank_Type::MBC_1:
            mbc_render = "MBC 1";
        break;

        case Bank_Type::MBC_2:
            mbc_render = "MBC 2";
        break;

        case Bank_Type::MBC_3:
            mbc_render = "MBC 3";
        break;

        case Bank_Type::MBC_5:
            mbc_render = "MBC 5";
        break;

        case Bank_Type::MBC_6:
            mbc_render = "MBC 6";
        break;

        case Bank_Type::MBC_7:
            mbc_render = "MBC 7";
        break;

        default:
            mbc_render = "Unknown";
        break;
    }

    ImGui::Text(mbc_render.c_str());

    auto ram = has_ram(mbc_identifier);
    ImGui::Checkbox("Ram: ", &ram);

    ImGui::End();
}

void render_menu() {

    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {

            if(ImGui::MenuItem("Open...", "Ctrl+O")) {

            }
            ImGui::EndMenu();
        }
      ImGui::EndMainMenuBar();
    }
}