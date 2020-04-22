#pragma once
#include "memory_controllers/MemoryBankController.h"

enum class Tile_Data_Sign {
    Unsigned,
    Signed
};

class LCD_Control {
public:

    explicit LCD_Control(MemoryBankController* memory_controller);

    bool lcd_display_enabled() const;
    bool window_display_enabled() const;
    bool background_display_enabled() const;
    bool sprite_display_eanbled() const;

    int window_tile_select() const;
    bool background_tile_map_select() const;
    int sprite_size() const;

    bool tile_data_signed() const;
    uint16_t tile_data_start_address() const;
    uint16_t tile_map_start_address() const;
    uint16_t window_tile_map_start_address() const;

private:


    const uint16_t control_address = 0xFF40;
    MemoryBankController* m_memory_controller;
};