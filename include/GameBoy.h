#pragma once

#include <memory>

#include <MemoryBankController.h>
#include <Cpu.h>

class GameBoy {
public:

    

private:

    Cpu m_cpu;
    std::unique_ptr<MemoryBankController> m_memory_bank_controller;

};



