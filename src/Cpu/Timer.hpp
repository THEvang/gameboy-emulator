#pragma once

#include <cstdint>

class MemoryBankController;

class Timer {
public:

    Timer(MemoryBankController* memory);
    void increment(int cycles);

    static const uint16_t div_address = 0xFF04;
    static const uint16_t tima_address = 0xFF05;
    static const uint16_t tma_address = 0xFF06;
    static const uint16_t tac_address = 0xFF07;

private: 

    bool should_increment_tima();
    void reset_tima();
    void tick();

    uint16_t m_div_value = 0xABCC;

    MemoryBankController* m_memory;

    bool m_prev_delay = false;
    bool m_tima_has_overflowed = false;
};