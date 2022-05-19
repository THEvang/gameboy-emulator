#pragma once

#include "Gameboy/Gameboy.h"

typedef enum EventType {
    Quit,
    KeyUp,
    KeyDown
} EventType;

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

typedef struct Input {
    EventType type;
    Button button;
} Input;

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, GameBoyState* emulator);
