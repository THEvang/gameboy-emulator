#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Memory/Memory_Controller.h"

typedef enum Cpu_Register {
    Register_A,
    Register_B,
    Register_C,
    Register_D,
    Register_E,
    Register_F,
    Register_H,
    Register_L,
} Cpu_Register;

typedef enum Cpu_Flag {
    Flag_Carry = 4,
    Flag_Half_Carry,
    Flag_Sub,
    Flag_Zero
} Cpu_Flag;

typedef struct Cpu {
    uint16_t stack_ptr;
    uint16_t program_counter;

    bool interrupts_enabled;
    bool should_enable_interrupts;
    bool should_disable_interrupts;
    bool should_stop;

    bool is_halted;
    bool halt_bug_triggered;

    MemoryBankController* memory_controller;
    uint8_t registers[8];
} Cpu;

void set_initial_state(Cpu* cpu);

bool test_flag(uint8_t flags, Cpu_Flag flag);
void set_flag(uint8_t* flags, Cpu_Flag flag);
void clear_flag(uint8_t* flags, Cpu_Flag flag);

uint16_t read_register_pair(Cpu, Cpu_Register, Cpu_Register);