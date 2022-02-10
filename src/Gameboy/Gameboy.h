#pragma once

#include "Memory/Memory_Controller.h"
#include "Cpu/Cpu.h"
#include "Cpu/Timer.h"
#include "Graphics/PPU.h"

typedef struct GameBoyState {
    MemoryBankController memory_bank_controller;
    Cpu cpu;
    Timer timer;
    PPU ppu;
} GameBoyState;

void gb_run(GameBoyState* gb);