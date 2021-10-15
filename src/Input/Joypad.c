#include "Input/Joypad.h"
#include "Cpu/Interrupts.h"
#include "Utilities/BitOperations.h"

void key_down(MemoryBankController* mc, Button button) {
    mc->buttons &= ~button;
    gb_request_interrupt(mc, Interrupts_Joypad);
}

void key_up(MemoryBankController* mc, Button button) {
    mc->buttons |= button;
}