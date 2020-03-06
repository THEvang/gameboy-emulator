#include <Timer.h>

#include <BitOperations.h>

bool Timer::increment_div(const int current_cycles) {

    const auto cpu_speed = 4.194304e6;
    const auto div_speed = 16384;
    const auto ratio = cpu_speed / div_speed;

    if( (current_cycles - last_div_increment) >= ratio) {
        
        last_div_increment = current_cycles - current_cycles % static_cast<int>(ratio);
        return true;
    } else {
        return false;
    }
}

bool Timer::increment_tima(const int current_cycles, uint8_t timer_control) {

    const auto cpu_speed = 4.194304e6;


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

    const auto ratio = cpu_speed / clock_value;
    if ((current_cycles - last_tima_increment) >= ratio) {

        last_tima_increment = current_cycles - (current_cycles % static_cast<int>(ratio));
        if(!is_set(timer_control, 2)) {
            return false;
        }
        return true;
    }
    return false;
}