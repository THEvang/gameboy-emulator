#pragma once

#include "Input/Joypad.h"
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

typedef void* RenderState;

typedef struct EmulatorState {

    void (*init_input_handler) ();
    int (*input_handler) (Input* i);

    RenderState (*init_renderer) ();
    void (*renderer) (GameBoyState*, RenderState);
} Emulator;