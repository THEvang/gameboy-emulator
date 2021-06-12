#include <stdio.h>

#include "Gui/Renderers.hpp"
#include "imgui/imgui.h"
#include "Cpu/Opcodes.h"
#include "Disassembler/Disassembler.hpp"
#include "Memory/Cartridge.h"
#include "SDL2/SDL.h"

void render_ppu(GameBoy& gameboy) {

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(glGetError() != GL_NO_ERROR) {
        printf("Failed to bind texture\n");
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
        (GLvoid*) &(gameboy.ppu.screen.pixels));

    ImGui::Begin("PPU");
    ImGui::Image((void*)(intptr_t) texture, ImVec2(width*3, height*3)); 
    ImGui::End();
}