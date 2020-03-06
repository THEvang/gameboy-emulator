#pragma once
#include <cinttypes>
class Timer {
public:

    bool increment_div(const int current_cycles);
    bool increment_tima(const int current_cycles, uint8_t timer_control);

private: 
    int last_div_increment = 0;
    int last_tima_increment = 0;
};