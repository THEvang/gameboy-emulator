#pragma once

#include "memory_controllers/MemoryBankController.h"
#include "cpu/Cpu.h"

class GameBoy {
public:

    void run(const std::vector<uint8_t>& rom);

private:

    // Cpu m_cpu;
//    std::unique_ptr<MemoryBankController> m_memory_bank_controller;
};