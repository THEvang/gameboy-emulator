#pragma once 

#include "Gameboy/Gameboy.hpp"

void render_disassembly(GameBoy& gameboy);
void render_ppu(GameBoy& gameboy);
void render_cpu(GameBoy& gameboy);
void render_cartridge_data(GameBoy& gameboy);
void render_menu();