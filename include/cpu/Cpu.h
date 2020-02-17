#pragma once
#pragma once 

#include <cstdint>
#include <MemoryBankController.h>

struct Cpu {

    uint8_t m_reg_a;
    uint8_t m_reg_b;
    uint8_t m_reg_c;
    uint8_t m_reg_d;
    uint8_t m_reg_e;
    uint8_t m_reg_f;
    uint8_t m_reg_h;
    uint8_t m_reg_l;

    uint16_t m_stack_ptr;
    uint16_t m_program_counter;

    int m_cycles;

    MemoryBankController* m_memory_controller;
};

void step(Cpu& cpu);
