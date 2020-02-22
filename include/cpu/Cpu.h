#pragma once

#include <cstdint>
#include <MemoryBankController.h>

struct Cpu {

    Cpu(MemoryBankController* memory_controller);

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

    bool m_enabled_interrupts = false;

    int m_cycles;

    MemoryBankController* m_memory_controller;
};

void step(Cpu& cpu);
