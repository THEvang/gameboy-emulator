#pragma once
#include "memory_controllers/MemoryBankController.h"

class LCD_Control {
public:

    explicit LCD_Control(MemoryBankController* memory_controller);

    bool lcd_display_enabled();
    bool window_display_enabled();
    bool background_display_enabled();
    bool sprite_display_eanbled();

    int window_tile_select();
    int background_tile_map_select();
    int sprite_size();

private:

    static const int coincidence_bit = 2;

    const uint16_t control_address = 0xFF40;
    MemoryBankController* m_memory_controller;
};