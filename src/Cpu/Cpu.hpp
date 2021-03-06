#pragma once

#include <cstdint>
#include <variant>
#include <functional>
#include <array>
#include <BitOperations.hpp>

class MemoryBankController;

struct Cpu {

    explicit Cpu(MemoryBankController* memory_controller);

    enum class Register {
        A,
        B,
        C,
        D,
        E,
        F,
        H,
        L,
    };

    enum class Flag {
        Carry = 4,
        Half_Carry,
        Sub,
        Zero
    };

    static int to_index(Cpu::Flag f);

    void set(Register r, uint8_t value);

    uint8_t get(Register r) const;

    uint8_t& get(Register r);

    uint16_t get(std::pair<Register, Register> r_pair) const;

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
private:
    std::array<uint8_t, 8> m_registers;
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