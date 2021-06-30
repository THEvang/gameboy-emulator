#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"

static const uint16_t g_div_address = 0xFF04;
static const uint16_t g_tima_address = 0xFF05;
static const uint16_t g_tma_address = 0xFF06;
static const uint16_t g_tac_address = 0xFF07;

typedef struct Timer {
    bool prev_delay;
    bool tima_has_overflowed;
    uint16_t div_value;
    int tima_speed;
} Timer;

void gb_timer_increment(Timer* timer, MemoryBankController* mc, int cycles);
void gb_timer_tick(Timer* timer, MemoryBankController* mc);
bool gb_timer_should_increment_tima(Timer* timer, MemoryBankController* mc);
void gb_timer_reset_tima(MemoryBankController* mc);