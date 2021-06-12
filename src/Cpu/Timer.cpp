#include "Timer.hpp"
#include "Utilities/BitOperations.h"
#include "Memory/Memory_Controller.h"
#include "Cpu/Interrupts.h"

Timer::Timer(MemoryBankController* memory) 
    : m_memory(memory)
{}


void Timer::increment(int cycles) {

    while(cycles > 0) {
        tick();
        cycles -= 4;
    }
}

void Timer::tick() {

    // if(m_memory->gb_read(div_address) == 0) {
    //     m_div_value = 0;
    // }
    
    m_div_value = static_cast<uint16_t>(m_div_value + 4);
    m_memory->memory[div_address] = static_cast<uint8_t>(m_div_value >> 8u); 
    
    if(m_tima_has_overflowed) { 
        reset_tima();
        //if(m_interrupt_handler.timer_interrupt_enabled()) {
            request_interrupt(m_memory, Interrupts_Timer);
        //}
        m_tima_has_overflowed = false;
    }

    if(should_increment_tima()) {

        auto tima_value = gb_read(m_memory, tima_address);
        if(overflows_8bit(tima_value, 1)) {
            m_tima_has_overflowed = true;
        }
        
        tima_value++;
        m_memory->memory[tima_address] = tima_value;
    }

}

bool Timer::should_increment_tima() {

    const auto timer_control = gb_read(m_memory, tac_address);
    const auto clock_select = static_cast<uint8_t>(timer_control & 0x03u);
    auto n = 0;

    switch(clock_select) {
        case 0:
            n = 9;
            break;
        case 1:
            n = 3;
            break;
        case 2:
            n = 5;
            break;
        case 3:
            n = 7;
            break;
        default:
            n = 9;
            break;
    }

    auto value = test_bit_16bit(m_div_value, n) && test_bit_8bit(timer_control, 2);
    if(!value && m_prev_delay) {
        m_prev_delay = value;
        return true;
    }

    m_prev_delay = value;
    return false;
}

void Timer::reset_tima() {
    const auto tima_reset_value = gb_read(m_memory, tma_address);
    gb_write(m_memory, tima_address, tima_reset_value);
}