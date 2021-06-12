#pragma once

#include "Memory/Memory_Controller.h"
#include "Cpu/Cpu.h"
#include "Input/Joypad.h"
#include "Cpu/Timer.h"
#include "Graphics/PPU.hpp"

struct GameBoy {

    GameBoy(MemoryBankController* mc);
    void run();

    MemoryBankController* memory_bank_controller;
    Cpu cpu;
    Timer timer;
    PPU ppu;
    Joypad joypad;
};