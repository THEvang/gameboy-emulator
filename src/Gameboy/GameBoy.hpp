#pragma once

#include <memory>

#include "Memory/Memory_Controller.hpp"
#include "Memory/Memory.hpp"

#include "Cpu/Cpu.hpp"
#include "Timer.hpp"
#include "Cpu/Interrupt_Handler.hpp"
#include "Graphics/PPU.hpp"

#include "Input/Keyboard.hpp"
#include "Input/Joypad_Controller.hpp"


class GameBoy {
public:

    explicit GameBoy(const std::vector<uint8_t>& rom);
    void run();

    Cpu* cpu() const;
    PPU* ppu() const;
    Interrupt_Handler* interrupt_handler() const;
    Joypad_Controller* joypad_controller() const;
    MemoryBankController* memory_controller() const;
    Timer* timer() const;

private:

    std::unique_ptr<Joypad_Controller> m_joypad_controller;
    std::unique_ptr<MemoryBankController> m_memory_bank_controller;
    std::unique_ptr<Cpu> m_cpu;
    std::unique_ptr<Timer> m_timer;
    std::unique_ptr<Interrupt_Handler> m_interrupt_handler;
    std::unique_ptr<PPU> m_ppu;
};