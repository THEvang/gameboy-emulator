#pragma once

#include "Memory/Memory_Controller.h"

#include "Cpu/Cpu.hpp"
#include "Cpu/Timer.hpp"
#include "Cpu/Interrupt_Handler.hpp"
#include "Graphics/PPU.hpp"
#include "Input/Joypad.hpp"


struct GameBoy {

    GameBoy(MemoryBankController* mc);
    void run();

    MemoryBankController* memory_bank_controller;
    Cpu cpu;
    Timer timer;
    Interrupt_Handler interrupt_handler;
    PPU ppu;
    Joypad joypad;
};