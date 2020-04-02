#pragma once
#include <cinttypes>
#include <memory_controllers/MemoryBankController.h>
class Timer {
public:

    Timer(MemoryBankController* memory_controller);
    void increment(uint8_t cycles);

    bool increment_div();
    bool increment_tima(uint8_t timer_control);

    static const uint16_t div_address = 0xFF04;    
    static const uint16_t tima_address = 0xFF05;
    static const uint16_t tma_address = 0xFF06;
    static const uint16_t tac_address = 0xFF07;

private: 

    int m_div_cycles = 0;
    int m_tima_cycles = 0;
    const int m_cpu_speed = 4.194304e6;
    const int m_div_speed = 16384;

    MemoryBankController* m_memory_controller;
};