#pragma once

#include "Memory/Memory_Controller.h"
#include "Memory/Memory.h"

#include "cpu/Cpu.h"
#include "Timer.h"
#include "cpu/Interrupt_Handler.h"
#include "graphics/PPU.h"

#include <memory>

class GameBoy {
public:

    explicit GameBoy(const std::vector<uint8_t>& rom);
    void run();

    Cpu* cpu();
    PPU* ppu();
    Interrupt_Handler* interrupt_handler() { return m_interrupt_handler.get();}
private:

    std::unique_ptr<MemoryBankController> m_memory_bank_controller;
    std::unique_ptr<Cpu> m_cpu;
    std::unique_ptr<Timer> m_timer;
    std::unique_ptr<Interrupt_Handler> m_interrupt_handler;
    std::unique_ptr<PPU> m_ppu;
};