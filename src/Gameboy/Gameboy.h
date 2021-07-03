#pragma once

#include "Memory/Memory_Controller.h"
#include "Cpu/Cpu.h"
#include "Input/Joypad.h"
#include "Cpu/Timer.h"
#include "Graphics/PPU.h"
#include "Sound/Sound.h"

typedef struct GameBoy {

    MemoryBankController* memory_bank_controller;
    Cpu cpu;
    Timer timer;
    PPU ppu;
    Joypad joypad;
    Sound_Channels sound_channels;
} GameBoy;

void gb_run(GameBoy* gb);