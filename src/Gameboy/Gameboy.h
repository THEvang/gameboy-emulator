#pragma once

#include "Memory/Memory_Controller.h"
#include "Cpu/Cpu.h"
#include "Input/Joypad.h"
#include "Cpu/Timer.h"
#include "Graphics/PPU.h"

typedef struct GameBoy {

    MemoryBankController* memory_bank_controller;
    Cpu cpu;
    Timer timer;
    PPU ppu;
    Joypad joypad;
} GameBoy;

void gb_run(GameBoy* gb);