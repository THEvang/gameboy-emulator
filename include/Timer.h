#pragma once
#include <cstdint>
#include <memory_controllers/MemoryBankController.h>

class Timer {
public:

    Timer(MemoryBankController* memory);
    void increment(uint8_t cycles);


    static const uint16_t div_address = 0xFF04;    
    static const uint16_t tima_address = 0xFF05;
    static const uint16_t tma_address = 0xFF06;
    static const uint16_t tac_address = 0xFF07;

private: 

    bool should_increment_div();
    int div_ratio();
    void increment_div();

    bool should_increment_tima();
    int tima_ratio();
    bool tima_enabled();
    void reset_tima();
    
    void increment_tima();

    int m_div_cycles = 0;
    int m_tima_cycles = 0;
    const int m_cpu_speed = 4.194304e6;
    const int m_div_speed = 16384;

    MemoryBankController* m_memory;
};