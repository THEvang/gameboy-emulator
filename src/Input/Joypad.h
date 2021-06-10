#pragma once 

#include <stdint.h>
#include "Memory/Memory_Controller.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Button_Types {
    Direction_Key,
    Button_Key
} Button_Types;

typedef enum Button {
    Button_Start,
    Button_Select,
    Button_A,
    Button_B,
    Button_Up,
    Button_Down,
    Button_Right,
    Button_Left
} Button;

typedef enum Key_Press {
    Key_Down,
    Key_Up
} Key_Press;

typedef struct Joypad {
    uint8_t direction_keys;
    uint8_t button_keys;
} Joypad;

void input(Joypad* pad, MemoryBankController* mc, Key_Press key_press, Button button);
void key_down(Joypad* pad, MemoryBankController* mc, Button button);
void key_up(Joypad* pad, Button button);

#ifdef __cplusplus
}
#endif