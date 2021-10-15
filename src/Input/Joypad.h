#pragma once 

#include "Memory/Memory_Controller.h"

typedef enum Button {
    Button_Right = 1 << 0,
    Button_Left = 1 << 1,
    Button_Up = 1 << 2,
    Button_Down = 1 << 3,
    Button_A = 1 << 4,
    Button_B = 1 << 5,
    Button_Select = 1 << 6,
    Button_Start = 1 << 7
} Button;

void key_down(MemoryBankController* mc, Button button);
void key_up(MemoryBankController* mc, Button button);   