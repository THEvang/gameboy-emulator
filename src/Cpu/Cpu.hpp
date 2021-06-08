#pragma once

#include <stdint.h>
#include <variant>

class MemoryBankController;

enum Cpu_Register {
    Register_A,
    Register_B,
    Register_C,
    Register_D,
    Register_E,
    Register_F,
    Register_H,
    Register_L,
};

enum Cpu_Flag {
    Flag_Carry = 4,
    Flag_Half_Carry,
    Flag_Sub,
    Flag_Zero
};


struct Cpu {

    explicit Cpu(MemoryBankController* memory_controller);

    bool test_flag(Cpu_Flag flag) const;

    void set_flag(Cpu_Flag flag);

    void clear_flag(Cpu_Flag flag);

    uint16_t stack_ptr = 0xFFFE;
    uint16_t program_counter = 0x0100;

    bool interrupts_enabled = false;
    bool should_enable_interrupts = false;
    bool should_disable_interrupts = false;
    bool should_stop = false;

    MemoryBankController* memory_controller;

    bool is_halted = false;
    uint8_t registers[8];
};

uint16_t read_register_pair(Cpu, Cpu_Register, Cpu_Register);

using Operand = std::variant<uint8_t, uint16_t, int8_t>;

//Addressing Modes
Operand immediate(Cpu&);
Operand immediate_extended(Cpu&);
Operand hl_addressing(Cpu&);
Operand relative_address(Cpu&);
Operand extended_address(Cpu&);
Operand implied(Cpu&);
Operand indexed_address(Cpu&);
Operand extended_addressing(Cpu&);
Operand none(Cpu&);