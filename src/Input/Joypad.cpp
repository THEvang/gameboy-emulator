#include "Input/Joypad.hpp"
#include "Cpu/Interrupt_Handler.hpp"
#include "Utilities/BitOperations.h"

void key_down(Joypad* pad, MemoryBankController* mc, Button button) {
    switch(button) {
        case Button_Right:
            clear_bit(&(pad->direction_keys), 0);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_Left:
            clear_bit(&(pad->direction_keys), 1);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_Up:
            clear_bit(&(pad->direction_keys), 2);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_Down:
            clear_bit(&(pad->direction_keys), 3);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_A:
            clear_bit(&(pad->button_keys), 0);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_B:
            clear_bit(&(pad->button_keys), 1);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_Select:
            clear_bit(&(pad->button_keys), 2);
            request_interrupt(mc, Interrupts_Joypad);
            break;
        case Button_Start:
            clear_bit(&(pad->button_keys), 3);
            request_interrupt(mc, Interrupts_Joypad);
            break;
    }
}

void key_up(Joypad* pad, Button button) {
    switch(button) {
        case Button_Right:
            set_bit(&(pad->direction_keys), 0);
            break;
        case Button_Left:
            set_bit(&(pad->direction_keys), 1);
            break;
        case Button_Up:
            set_bit(&(pad->direction_keys), 2);
            break;
        case Button_Down:
            set_bit(&(pad->direction_keys), 3);
            break;
        case Button_A:
            set_bit(&(pad->button_keys), 0);
            break;
        case Button_B:
            set_bit(&(pad->button_keys), 1);
            break;
        case Button_Select:
            set_bit(&(pad->button_keys), 2);
            break;
        case Button_Start:
            set_bit(&(pad->button_keys), 3);
            break;
    }
}

void input(Joypad* pad, MemoryBankController* mc, Key_Press key_press, Button button) {
    switch(key_press) {
        case Key_Down:
            key_down(pad, mc, button);
            break;
        case Key_Up:
            key_up(pad, button);
            break;
    }
}