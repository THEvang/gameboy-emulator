#pragma once

#include "memory_controllers/MemoryBankController.h"
#include "cpu/Cpu.h"
#include "memory_controllers/Memory.h"
#include "Timer.h"
#include "cpu/Interrupt_Handler.h"
#include "graphics/PPU.h"

class GameBoy {
public:

    explicit GameBoy(const std::vector<uint8_t>& rom);
    void run();

    Cpu* cpu();
    PPU* ppu();
private:

    std::unique_ptr<MemoryBankController> m_memory_bank_controller;
    std::unique_ptr<Cpu> m_cpu;
    std::unique_ptr<Timer> m_timer;
    std::unique_ptr<Interrupt_Handler> m_interrupt_handler;
    std::unique_ptr<PPU> m_ppu;
};