#pragma once 

#include "GameBoy.h"

void render_disassembly(GameBoy const& gameboy);
void render_ppu(GameBoy const& gameboy);
void render_cpu(GameBoy const& gameboy);
void render_cartridge_data(GameBoy const& gameboy);