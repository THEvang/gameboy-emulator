#pragma once

#include <stdint.h>
#include <stdbool.h>

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
    Flag_Carry = 1 << 4,
    Flag_Half_Carry = 1 << 5,
    Flag_Sub = 1 << 6,
    Flag_Zero = 1 << 7,
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
    uint8_t registers[8];
} Cpu;

void gb_cpu_set_initial_state(Cpu* cpu);

bool test_flag(uint8_t flags, Cpu_Flag flag);
void set_flag(uint8_t* flags, Cpu_Flag flag);
void clear_flag(uint8_t* flags, Cpu_Flag flag);

uint16_t read_register_pair(Cpu, Cpu_Register, Cpu_Register);