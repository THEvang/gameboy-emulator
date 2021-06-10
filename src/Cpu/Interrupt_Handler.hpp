#pragma once 

#include <stdint.h>
#include "Memory/Memory_Controller.h"

struct Cpu;

typedef enum Interrupts {
    Interrupts_V_Blank = 0,
    Interrupts_LCD_STAT,
    Interrupts_Timer,
    Interrupts_Serial,
    Interrupts_Joypad
} Interrupts;

const uint16_t g_interrupt_request_address = 0xFF0F;
const uint16_t g_interrupt_enabled_address = 0xFFFF;


struct Interrupt_Handler {

    int interrupts(Cpu& cpu);

    bool should_exit_halt();
    bool timer_interrupt_enabled() const;

    bool is_requested(Interrupts interrupt) const;
    bool is_enabled(Interrupts interrupt) const;
    uint16_t get_vector(Interrupts interrupt) const;

    void call(Cpu& cpu, uint8_t interrupt_vector);  
    

    MemoryBankController* memory_bank_controller;
};

void request_interrupt(MemoryBankController* mc, Interrupts interrupt);
void clear_interrupt(MemoryBankController* mc, Interrupts interrupt);