#include "Timer.h"
#include "Utilities/BitOperations.h"
#include "Cpu/Interrupts.h"

void gb_timer_increment(Timer* timer, MemoryBankController* mc, int cycles) {

    while(cycles > 0) {
        gb_timer_tick(timer, mc);
        cycles -= 4;
    }
}

void gb_timer_tick(Timer* timer, MemoryBankController* mc) {

    timer->div_value += 4;
    mc->memory[g_div_address] = (uint8_t) (timer->div_value >> 8u); 
    
    if(timer->tima_has_overflowed) { 
        gb_timer_reset_tima(mc);
        //if(m_interrupt_handler.timer_interrupt_enabled()) {
            request_interrupt(mc, Interrupts_Timer);
        //}
        timer->tima_has_overflowed = false;
    }

    if(gb_timer_should_increment_tima(timer, mc)) {

        uint8_t tima_value = gb_read(mc, g_tima_address);
        if(overflows_8bit(tima_value, 1)) {
            timer->tima_has_overflowed = true;
        }
        
        tima_value++;
        mc->memory[g_tima_address] = tima_value;
    }

}

bool gb_timer_should_increment_tima(Timer* timer, MemoryBankController* mc) {

    const uint8_t timer_control = gb_read(mc, g_tac_address);
    const uint8_t clock_select = (uint8_t) (timer_control & 0x03u);
    int n = 0;

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

    bool value = test_bit_16bit(timer->div_value, n) && test_bit_8bit(timer_control, 2);
    if(!value && timer->prev_delay) {
        timer->prev_delay = value;
        return true;
    }

    timer->prev_delay = value;
    return false;
}

void gb_timer_reset_tima(MemoryBankController* mc) {
    const uint8_t tima_reset_value = gb_read(mc, g_tma_address);
    gb_write(mc, g_tima_address, tima_reset_value);
}