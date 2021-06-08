#pragma once

#include <cstdint>
#include <variant>
#include <functional>
#include <BitOperations.hpp>

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

struct Cpu {

    explicit Cpu(MemoryBankController* memory_controller);

    enum class Flag {
        Carry = 4,
        Half_Carry,
        Sub,
        Zero
    };

    static int to_index(Cpu::Flag f);

    uint16_t get(std::pair<Cpu_Register, Cpu_Register> r_pair) const;

    bool test_flag(const Flag& flag) const;

    void set_flag(const Cpu::Flag& flag);

    void clear_flag(const Cpu::Flag& flag);

    uint16_t m_stack_ptr = 0xFFFE;
    uint16_t m_program_counter = 0x0100;

    bool m_interrupts_enabled = false;
    bool m_should_enable_interrupts = false;
    bool m_should_disable_interrupts = false;
    bool should_stop = false;

    MemoryBankController* m_memory_controller;

    bool m_is_halted = false;
    uint8_t registers[8];
};

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