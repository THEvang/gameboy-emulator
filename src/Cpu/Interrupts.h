#pragma once 

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"
#include "Cpu/Cpu.h"

typedef enum Interrupts {
    Interrupts_V_Blank = 0,
    Interrupts_LCD_STAT,
    Interrupts_Timer,
    Interrupts_Serial,
    Interrupts_Joypad
} Interrupts;

static const uint16_t g_interrupt_request_address = 0xFF0F;
static const uint16_t g_interrupt_enabled_address = 0xFFFF;

int handle_interrupts(Cpu* cpu);
void call_interrupt_vector(Cpu* cpu, uint16_t interrupt_vector);  
uint16_t to_vector(Interrupts interrupt);
bool is_enabled(MemoryBankController* mc, Interrupts interrupt);
bool is_requested(MemoryBankController* mc, Interrupts interrupt);
bool should_exit_halt(MemoryBankController* mc);
void request_interrupt(MemoryBankController* mc, Interrupts interrupt);
void clear_interrupt(MemoryBankController* mc, Interrupts interrupt);

#ifdef __cplusplus
}
#endif