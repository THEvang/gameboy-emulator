#include "Gui/Renderers.h"

#include <iostream>

#include "imgui/imgui.h"
#include "Cpu/Opcodes.h"
#include "Disassembler/Disassembler.h"
#include "Memory/Cartridge.h"

void render_disassembly(GameBoy const& gameboy) {

    ImGui::Begin("Disassembly");
    ImGui::BeginChild("Disassembly_List");
        const auto opcode = gameboy.memory_controller()->read(gameboy.cpu()->m_program_counter);
        const auto instruction = disassemble(static_cast<Opcode>(opcode));
        ImGui::Text("%d: %s, %d", 
            gameboy.cpu()->m_program_counter,
            instruction.name.c_str(),
            instruction.cycles);
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

void render_cpu(GameBoy const& gameboy) {
    
    const auto cpu = gameboy.cpu();

    ImGui::Begin("Cpu!");
    ImGui::Text("Current Opcode: %i.", cpu->m_memory_controller->read(cpu->m_program_counter));
    ImGui::Text("Register A: %i.", cpu->m_reg_a);
    ImGui::SameLine();
    ImGui::Text("Register F: %i.", cpu->m_reg_f);

    ImGui::Text("Register B: %i.", cpu->m_reg_b);
    ImGui::SameLine();
    ImGui::Text("Register C: %i.", cpu->m_reg_c);

    ImGui::Text("Register D: %i.", cpu->m_reg_d);
    ImGui::SameLine();
    ImGui::Text("Register E: %i.", cpu->m_reg_e);

    ImGui::Text("Register H: %i.", cpu->m_reg_h);
    ImGui::SameLine();
    ImGui::Text("Register L: %i.", cpu->m_reg_l);

    bool zero_flag = is_set(cpu->m_reg_f, 7);
    ImGui::Checkbox("Zero Flag: ", &zero_flag);
    ImGui::SameLine();

    bool subtract_flag = is_set(cpu->m_reg_f, 6);
    ImGui::Checkbox("Subtract Flag: ", &subtract_flag);
    ImGui::SameLine();

    bool half_carry = is_set(cpu->m_reg_f, 5);
    ImGui::Checkbox("Half Carry Flag", &half_carry);
    ImGui::SameLine();

    bool carry_flag = is_set(cpu->m_reg_f, 4);
    ImGui::Checkbox("Carry flag: ", &carry_flag);
    ImGui::SameLine();

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