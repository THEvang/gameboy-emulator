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

    GameBoyState gameboy_state;

    void (*input_handler_init) ();
    int (*input_handler) (Input* i);
    void (*input_handler_cleanup) ();

    RenderState (*render_init) ();
    void (*render) (GameBoyState*, RenderState);
    void (*render_cleanup) (RenderState);
} Emulator;

void gb_init_emulator(gb_Rom* rom, CartridgeHeader* header, Emulator* emulator);
void gb_run_emulator(Emulator* emulator, RenderState render_state);