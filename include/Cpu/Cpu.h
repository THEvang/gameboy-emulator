#pragma once

#include <cstdint>
#include "Memory/Memory_Controller.h"
#include <functional>

struct Cpu {

    explicit Cpu(MemoryBankController* memory_controller);

    uint8_t m_reg_a = 0x01;
    uint8_t m_reg_b = 0x00;
    uint8_t m_reg_c = 0x13;
    uint8_t m_reg_d = 0x00;
    uint8_t m_reg_e = 0xD8;
    uint8_t m_reg_f = 0xB0;
    uint8_t m_reg_h = 0x01;
    uint8_t m_reg_l = 0x4D;

    uint16_t m_stack_ptr = 0xFFFE;
    uint16_t m_program_counter = 0x0100;

    bool m_interrupts_enabled = false;
    bool m_should_enable_interrupts = false;
    bool m_should_disable_interrupts = false;
    bool should_stop = false;

    int m_cycles = 0;

    MemoryBankController* m_memory_controller;

    static const int zero_flag = 7;
    static const int sub_flag = 6;
    static const int half_carry_flag = 5;
    static const int carry_flag = 4;

    bool m_is_halted = false;
};

struct FetchResult {
    int cycles = 0;
    int delta_pc = 0;
    std::function<void(Cpu&)> operation;
};

FetchResult fetch(Cpu& cpu);
FetchResult fetch_cb(Cpu& cpu);
void timer(Cpu& cpu);

uint8_t ADD(uint8_t value, uint8_t& flags);