#pragma once
#include "memory_controllers/MemoryBankController.h"

enum class Tile_Data_Sign {
    Unsigned,
    Signed
};

class LCD_Control {
public:

    explicit LCD_Control(MemoryBankController* memory_controller);

    bool lcd_display_enabled();
    bool window_display_enabled();
    bool background_display_enabled();
    bool sprite_display_eanbled();

    int window_tile_select();
    bool background_tile_map_select();
    int sprite_size();

    bool tile_data_signed();
    uint16_t tile_data_start_address();
    uint16_t tile_map_start_address();
    uint16_t window_tile_map_start_address();

private:


    const uint16_t control_address = 0xFF40;
    MemoryBankController* m_memory_controller;
};