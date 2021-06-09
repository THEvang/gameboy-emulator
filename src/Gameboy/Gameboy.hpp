#pragma once

#include "Memory/Memory_Controller.hpp"
#include "Memory/Memory.hpp"

#include "Cpu/Cpu.hpp"
#include "Cpu/Timer.hpp"
#include "Cpu/Interrupt_Handler.hpp"
#include "Graphics/PPU.hpp"

#include "Input/Keyboard.hpp"
#include "Input/Joypad_Controller.hpp"


class GameBoy {
public:

    explicit GameBoy(const std::vector<uint8_t>& rom);
    void run();

    Cpu* cpu();
    PPU* ppu();
    Interrupt_Handler* interrupt_handler();
    Joypad_Controller* joypad_controller();
    MemoryBankController* memory_controller();
    Timer* timer();

private:

    Memory m_cartridge_memory;
    MemoryBankController m_memory_bank_controller;
    Cpu m_cpu;
    Timer m_timer;
    Interrupt_Handler m_interrupt_handler;
    PPU m_ppu;
    Joypad_Controller m_joypad_controller;
};