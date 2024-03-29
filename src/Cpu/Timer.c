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

    mc->div_register += 4;
    mc->memory[DIV] = (uint8_t) (mc->div_register >> 8);

    if(timer->tima_has_overflowed) { 
        gb_timer_reset_tima(mc);
        gb_request_interrupt(mc, Interrupts_Timer);
        timer->tima_has_overflowed = false;
    }

    if(gb_timer_should_increment_tima(timer, mc)) {

        uint8_t tima_value = mc->read(mc, TIMA);
        if(overflows_8bit(tima_value, 1)) {
            timer->tima_has_overflowed = true;
        }
        
        tima_value++;
        mc->memory[TIMA] = tima_value;
    }

}

bool gb_timer_should_increment_tima(Timer* timer, MemoryBankController* mc) {

    const uint8_t timer_control = mc->read(mc, TAC);
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

    bool value = test_bit_16bit(mc->div_register, n) && test_bit_8bit(timer_control, 2);
    if(!value && timer->prev_delay) {
        timer->prev_delay = value;
        return true;
    }

    timer->prev_delay = value;
    return false;
}

void gb_timer_reset_tima(MemoryBankController* mc) {
    const uint8_t tima_reset_value = mc->read(mc, TMA);
    mc->write(mc, TIMA, tima_reset_value);
}