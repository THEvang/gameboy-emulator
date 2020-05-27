#include "Timer.h"
#include "BitOperations.h"
#include "Memory/Memory_Controller.h"

Timer::Timer(MemoryBankController* memory) 
    : m_memory(memory)
    , m_interrupt_handler(memory)
{}


void Timer::increment(int cycles) {

    while(cycles > 0) {
        tick();
        cycles -= 4;
    }
}

void Timer::tick() {

    // if(m_memory->read(div_address) == 0) {
    //     m_div_value = 0;
    // }
    
    m_div_value = static_cast<uint16_t>(m_div_value + 4);
    m_memory->raw()[div_address] = static_cast<uint8_t>(m_div_value >> 8u); 
    
    if(m_tima_has_overflowed) { 
        reset_tima();
        //if(m_interrupt_handler.timer_interrupt_enabled()) {
            m_interrupt_handler.request_timer_interrupt();
        //}
        m_tima_has_overflowed = false;
    }

    if(should_increment_tima()) {

        auto tima_value = m_memory->read(tima_address);
        if(overflows_8bit(tima_value, 1)) {
            m_tima_has_overflowed = true;
        }
        
        tima_value++;
        m_memory->raw()[tima_address] = tima_value;
    }

}

bool Timer::should_increment_tima() {

    const auto timer_control = m_memory->read(tac_address);
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

    auto value = is_set(m_div_value, n) && is_set(timer_control, 2);
    if(!value && m_prev_delay) {
        m_prev_delay = value;
        return true;
    }

    m_prev_delay = value;
    return false;
}

void Timer::reset_tima() {
    const auto tima_reset_value = m_memory->read(tma_address);
    m_memory->write(tima_address, tima_reset_value);
}