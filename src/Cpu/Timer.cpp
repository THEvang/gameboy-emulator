#include <Timer.h>
#include <BitOperations.h>

Timer::Timer(Memory* memory) 
    : m_memory(memory)
{}

void Timer::increment(uint8_t cycles) {

    m_div_cycles += cycles;
    if(should_increment_div()) {
        increment_div();
    }
    
    if(tima_enabled()) {
        m_tima_cycles += cycles;
        if(should_increment_tima()) {

            auto tima_value = m_memory->read(tima_address);

            if(overflows_8bit(tima_value, 1)) {
                
                reset_tima();

                constexpr auto if_address = 0xFF0F;
                auto if_register = m_memory->read(if_address);

                set_bit(if_register, 2);
                m_memory->write(0xFF0F, if_register);
                
            } else {
                tima_value++;
                m_memory->write(tima_address, tima_value);
                m_tima_cycles -= tima_ratio();
            }
        }
    }
}

bool Timer::should_increment_div() {
    return m_div_cycles >= div_ratio();
}

int Timer::div_ratio() {
    return m_cpu_speed / m_div_speed;
}

void Timer::increment_div() {
    auto current_div_value = m_memory->read(div_address);
    current_div_value++;
    m_memory->write(div_address, current_div_value);
    m_div_cycles -= div_ratio();
}

bool Timer::should_increment_tima() {
    return m_tima_cycles >= tima_ratio();
}

int Timer::tima_ratio() {
    
    const auto timer_control = m_memory->read(tac_address);
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

    return m_cpu_speed / clock_value;
}

bool Timer::tima_enabled() {
    const auto timer_control = m_memory->read(tac_address);
    return is_set(timer_control, 2);
}

void Timer::reset_tima() {
    const auto tima_reset_value = m_memory->read(tma_address);
    m_memory->write(tima_address, tima_reset_value);
}