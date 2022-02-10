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

typedef void* Renderer;

typedef struct EmulatorState {

    GameBoyState gameboy_state;

    void (*input_handler_init) ();
    int (*input_handler) (Input* i);
    void (*input_handler_cleanup) ();

    Renderer renderer;
    void (*render) (GameBoyState*, Renderer);
    void (*render_cleanup) (Renderer);
} Emulator;

void gb_init_emulator(GameboyRom* rom, CartridgeHeader* header, Emulator* emulator);
void gb_run_emulator(Emulator* emulator);