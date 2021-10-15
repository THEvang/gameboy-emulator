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

int gb_handle_interrupts(Cpu* cpu);
void gb_call_interrupt_vector(Cpu* cpu, uint16_t interrupt_vector);  
uint16_t gb_to_vector(Interrupts interrupt);
bool gb_is_enabled(MemoryBankController* mc, Interrupts interrupt);
bool gb_is_requested(MemoryBankController* mc, Interrupts interrupt);
bool gb_should_exit_halt(MemoryBankController* mc);
void gb_request_interrupt(MemoryBankController* mc, Interrupts interrupt);
void gb_clear_interrupt(MemoryBankController* mc, Interrupts interrupt);
