#pragma once

#include "Memory/Memory_Controller.h"
#include "Memory/Memory.h"

#include "Cpu/Cpu.h"
#include "Timer.h"
#include "Cpu/Interrupt_Handler.h"
#include "Graphics/PPU.h"
#include "Input/Input.h"

#include <memory>

#include <memory>

class GameBoy {
public:

    explicit GameBoy(const std::vector<uint8_t>& rom);
    void run();

    Cpu* cpu();
    PPU* ppu();

    Interrupt_Handler* interrupt_handler() { return m_interrupt_handler.get();}
    Joypad_Controller* joypad_controller() { return m_joypad_controller.get();}

private:

    std::unique_ptr<Joypad_Controller> m_joypad_controller;
    std::unique_ptr<MemoryBankController> m_memory_bank_controller;
    std::unique_ptr<Cpu> m_cpu;
    std::unique_ptr<Timer> m_timer;
    std::unique_ptr<Interrupt_Handler> m_interrupt_handler;
    std::unique_ptr<PPU> m_ppu;
};