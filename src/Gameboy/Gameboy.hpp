#pragma once

#include "Memory/Memory_Controller.hpp"

#include "Cpu/Cpu.hpp"
#include "Cpu/Timer.hpp"
#include "Cpu/Interrupt_Handler.hpp"
#include "Graphics/PPU.hpp"

#include "Input/Keyboard.hpp"
#include "Input/Joypad_Controller.hpp"


struct GameBoy {

    GameBoy(MemoryBankController* mc);
    void run();

    MemoryBankController* memory_bank_controller;
    Cpu cpu;
    Timer timer;
    Interrupt_Handler interrupt_handler;
    PPU ppu;
    Joypad_Controller joypad_controller;
};