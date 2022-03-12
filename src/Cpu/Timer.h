#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"
#include "Registers.h"

typedef struct Timer {
    bool prev_delay;
    bool tima_has_overflowed;
    int tima_speed;
} Timer;

void gb_timer_increment(Timer* timer, MemoryBankController* mc, int cycles);
void gb_timer_tick(Timer* timer, MemoryBankController* mc);
bool gb_timer_should_increment_tima(Timer* timer, MemoryBankController* mc);
void gb_timer_reset_tima(MemoryBankController* mc);