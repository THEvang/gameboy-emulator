#pragma once

#include "Input/Joypad.h"
#include "App/Gui.h"
#include "Gameboy/Gameboy.h"

typedef enum EventType {
    Quit,
    KeyUp,
    KeyDown
} EventType;

typedef struct Input {
    EventType type;
    Button button;
} Input;

typedef struct EmulatorState {
    int (*input_handler) (Input* i);
    void (*renderer) (GameBoyState*, void* user_data);
} Emulator;