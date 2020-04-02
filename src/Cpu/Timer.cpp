#include <Timer.h>
#include <BitOperations.h>

Timer::Timer(MemoryBankController* memory_controller) 
    : m_memory_controller(memory_controller)
{}

void Timer::increment(uint8_t cycles) {

    m_div_cycles += cycles;
    if(increment_div()) {
        auto div_value = m_memory_controller->read(div_address);
        div_value++;
        m_memory_controller->write(div_address, div_value);
    };
    
    const auto time_control = m_memory_controller->read(tac_address);
    if(is_set(time_control, 2)) {
        m_tima_cycles += cycles;
        if(increment_tima(time_control)) {

            auto tima_value = m_memory_controller->read(tima_address);

            if(overflows_8bit(tima_value, 1)) {
                
                const auto tima_reset_value = m_memory_controller->read(tma_address);
                m_memory_controller->write(tima_address, tima_reset_value);

                auto if_register = m_memory_controller->read(0xFF0F);
                auto ie_register = m_memory_controller->read(0xFFFF);
                if(is_set(ie_register, 2)) {
                    set_bit(if_register, 2);
                    m_memory_controller->write(0xFF0F, if_register);
                }
                
            } else {
                tima_value++;
                m_memory_controller->write(tima_address, tima_value);
            }
        }
    }
}

bool Timer::increment_div() {

    const auto ratio =  m_cpu_speed / m_div_speed;

    if(m_div_cycles >= ratio) {
        m_div_cycles -= ratio;
        return true;
    }

    return false;
}

bool Timer::increment_tima(uint8_t timer_control) {

    const auto clock_select = timer_control & 0x03;
    auto clock_value = 0;

    switch(clock_select) {
        case 0b00:
            clock_value = 4096;
            break;
        case 0b01:
            clock_value = 262144;
            break;
        case 0b10:
            clock_value = 65536;
            break;
        case 0b11:
            clock_value = 16384;
            break;
        default:
            clock_value = 4096;
            break;
    }

    const auto ratio = m_cpu_speed / clock_value;
    if (m_tima_cycles >= ratio) {

        m_tima_cycles -= ratio;
        return true;
    }

    return false;
}